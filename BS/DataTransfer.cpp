#include "DataTransfer.h"
#include "./proto/bcTx.pb.h"

void *threadZMQRecv(void *arg);
CDataTransfer::CDataTransfer() :m_pResponder(NULL),
m_pRequester(NULL),
m_ZMQRecvPt(0),
m_notifFun(0),
m_nRecvLength(0)
{
	
	bzero(m_sSendSource, sizeof(m_sSendSource));
	bzero(m_nRecvBuff, sizeof(m_nRecvBuff)); 
}


CDataTransfer::~CDataTransfer()
{
}


// 初始化ZMQ
int CDataTransfer::StartZmq(int nRequestPort, int nRespondPort, char *pSoftName,zmqNotif notifFun)
{
	bzero(m_sSoftName, sizeof(m_sSoftName));
	strcat(m_sSoftName, pSoftName);

	char addr[100] = { 0 };
	bzero(addr, sizeof(addr));

	m_context = zmq_init(2);
	//m_context = zmq_ctx_new();

	//接收
	m_pRequester = zmq_socket(m_context, ZMQ_PULL);
	sprintf(addr, "tcp://*:%d", nRequestPort);
	zmq_bind(m_pRequester, addr);

	//发送
	m_pResponder = zmq_socket(m_context, ZMQ_PUSH);
	sprintf(addr, "tcp://*:%d", nRespondPort);
	zmq_bind(m_pResponder, addr);
	

	//创建接收线程
	pthread_create(&m_ZMQRecvPt, NULL, threadZMQRecv, this);

	m_notifFun = notifFun;
	return 0;
}

void *threadZMQRecv(void *arg)
{
	pthread_detach(pthread_self());

	//int state, oldstate;

	//state = PTHREAD_CANCEL_DEFERRED;
	//pthread_setcancelstate(state, &oldstate);

	CDataTransfer *me = (CDataTransfer *)arg;
	while (true)
	{
		if (me->RecvData() != TRUE)
		{
			break;
		}
		pthread_testcancel();

	}
	return NULL;
}
// 接收数据
int CDataTransfer::RecvData()
{
	zmq_pollitem_t items[] = { { m_pRequester, 0, ZMQ_POLLIN, -1 } };
	while (TRUE)
	{
		int rt = zmq_poll(items, 1, 1);
		if (items[0].revents&ZMQ_POLLIN)
		{
			printf("zmq recv\n");

			bzero(m_sSendSource, sizeof(m_sSendSource));
			bzero(m_nRecvBuff, sizeof(m_nRecvBuff));
			m_nRecvLength = 0;

			zmq_msg_t request;
			zmq_msg_init(&request);
			zmq_msg_recv(&request, m_pRequester, 0);

			int nTotalLen = zmq_msg_size(&request);

			//获取发送方来源（软件名称）
			memcpy(m_sSendSource, zmq_msg_data(&request), sizeof(m_sSendSource));

			//获取长度
			char cTemp[2];
			memcpy(cTemp,
				zmq_msg_data(&request) + FSF_LEGHTH,
				sizeof(cTemp));
						
			m_nRecvLength = cTemp[0];
			m_nRecvLength *= 256;
			m_nRecvLength += cTemp[1];

			//获取数据内容
			memcpy(m_nRecvBuff,
				zmq_msg_data(&request) + FSF_LEGHTH + SJCD_LEGHT, 
				PROCESS_FRAME_DATA_LENGTH);

			zmq_msg_close(&request);

			//protoc解析数据内容
			int nLength = strlen(m_nRecvBuff);
			if (nLength != m_nRecvLength)
			{
				continue;
			}

			BsTxMsg bstxMsg;
			if (bstxMsg.ParseFromString(m_nRecvBuff))
			{
				tagBstxMsg tagBstx;

				tagBstx.dwSerialID = bstxMsg.nserialid();
				tagBstx.nQtscardnumber = bstxMsg.nqtscardnumber();
				tagBstx.nCategory = bstxMsg.nqtdcategory();
				
				//存入数据处理列表
				m_notifFun(m_sSendSource, (void *)&tagBstx);
			}

		}
	}
	return TRUE;
}


// 发送数据
int CDataTransfer::SendData(char *buff,DWORD length)
{

	//添加头
	//发送方 接收方类型	接收方	数据长度	数据
	// 20 1	100	2	X
	char cSendBuffer[1024];
	bzero(cSendBuffer, sizeof(cSendBuffer));
	DWORD nSendbufferLength = 0;
	
	//发送方
	memcpy(cSendBuffer + nSendbufferLength, m_sSoftName, JSF_LEGHTH);
	nSendbufferLength += JSF_LEGHTH;

	//接收方类型 0=业务服务器软件、1=计费软件、2=北斗信息发送软件
	cSendBuffer[nSendbufferLength++] = 1;

	//接收方
	memcpy(cSendBuffer + nSendbufferLength, m_sSendSource, FSF_LEGHTH);
	nSendbufferLength += FSF_LEGHTH;

	//数据的长度
	sprintf(cSendBuffer + nSendbufferLength, "%d", length);
	nSendbufferLength += SJCD_LEGHT;

	//数据
	memcpy(cSendBuffer + nSendbufferLength, buff, length);
	nSendbufferLength += length;

	zmq_msg_t reply;
	zmq_msg_init_size(&reply, nSendbufferLength);
	memcpy(zmq_msg_data(&reply), cSendBuffer, nSendbufferLength);
	zmq_msg_send(&reply, m_pResponder, 0);
	zmq_msg_close(&reply);
	return TRUE;
}


// 关闭ZMQ
int CDataTransfer::CloseZmq()
{
	//终止线程
	void * res;
	pthread_cancel(m_ZMQRecvPt);
	pthread_join(m_ZMQRecvPt, &res);
	printf("stop m_ZMQRecvPt thread\n");

	zmq_close(m_pRequester);
	zmq_close(m_pResponder);
	zmq_ctx_destroy(m_context);
	return 0;
}

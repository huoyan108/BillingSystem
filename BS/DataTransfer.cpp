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


// ��ʼ��ZMQ
int CDataTransfer::StartZmq(int nRequestPort, int nRespondPort, char *pSoftName,zmqNotif notifFun)
{
	bzero(m_sSoftName, sizeof(m_sSoftName));
	strcat(m_sSoftName, pSoftName);

	char addr[100] = { 0 };
	bzero(addr, sizeof(addr));

	m_context = zmq_init(2);
	//m_context = zmq_ctx_new();

	//����
	m_pRequester = zmq_socket(m_context, ZMQ_PULL);
	sprintf(addr, "tcp://*:%d", nRequestPort);
	zmq_bind(m_pRequester, addr);

	//����
	m_pResponder = zmq_socket(m_context, ZMQ_PUSH);
	sprintf(addr, "tcp://*:%d", nRespondPort);
	zmq_bind(m_pResponder, addr);
	

	//���������߳�
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
// ��������
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

			//��ȡ���ͷ���Դ��������ƣ�
			memcpy(m_sSendSource, zmq_msg_data(&request), sizeof(m_sSendSource));

			//��ȡ����
			char cTemp[2];
			memcpy(cTemp,
				zmq_msg_data(&request) + FSF_LEGHTH,
				sizeof(cTemp));
						
			m_nRecvLength = cTemp[0];
			m_nRecvLength *= 256;
			m_nRecvLength += cTemp[1];

			//��ȡ��������
			memcpy(m_nRecvBuff,
				zmq_msg_data(&request) + FSF_LEGHTH + SJCD_LEGHT, 
				PROCESS_FRAME_DATA_LENGTH);

			zmq_msg_close(&request);

			//protoc������������
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
				
				//�������ݴ����б�
				m_notifFun(m_sSendSource, (void *)&tagBstx);
			}

		}
	}
	return TRUE;
}


// ��������
int CDataTransfer::SendData(char *buff,DWORD length)
{

	//���ͷ
	//���ͷ� ���շ�����	���շ�	���ݳ���	����
	// 20 1	100	2	X
	char cSendBuffer[1024];
	bzero(cSendBuffer, sizeof(cSendBuffer));
	DWORD nSendbufferLength = 0;
	
	//���ͷ�
	memcpy(cSendBuffer + nSendbufferLength, m_sSoftName, JSF_LEGHTH);
	nSendbufferLength += JSF_LEGHTH;

	//���շ����� 0=ҵ������������1=�Ʒ������2=������Ϣ�������
	cSendBuffer[nSendbufferLength++] = 1;

	//���շ�
	memcpy(cSendBuffer + nSendbufferLength, m_sSendSource, FSF_LEGHTH);
	nSendbufferLength += FSF_LEGHTH;

	//���ݵĳ���
	sprintf(cSendBuffer + nSendbufferLength, "%d", length);
	nSendbufferLength += SJCD_LEGHT;

	//����
	memcpy(cSendBuffer + nSendbufferLength, buff, length);
	nSendbufferLength += length;

	zmq_msg_t reply;
	zmq_msg_init_size(&reply, nSendbufferLength);
	memcpy(zmq_msg_data(&reply), cSendBuffer, nSendbufferLength);
	zmq_msg_send(&reply, m_pResponder, 0);
	zmq_msg_close(&reply);
	return TRUE;
}


// �ر�ZMQ
int CDataTransfer::CloseZmq()
{
	//��ֹ�߳�
	void * res;
	pthread_cancel(m_ZMQRecvPt);
	pthread_join(m_ZMQRecvPt, &res);
	printf("stop m_ZMQRecvPt thread\n");

	zmq_close(m_pRequester);
	zmq_close(m_pResponder);
	zmq_ctx_destroy(m_context);
	return 0;
}

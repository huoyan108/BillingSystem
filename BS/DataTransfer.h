#pragma once
#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "MsgStructInfo.h"
using namespace std;
#define FALSE -1
#define TRUE 0
typedef int(*zmqNotif) (char *, void *);

class CDataTransfer
{
public:
	CDataTransfer();
	~CDataTransfer();
	char m_sSendSource[FSF_LEGHTH];		//���ͷ�(�������)
	int m_nRecvLength;
	char m_nRecvBuff[PROCESS_FRAME_DATA_LENGTH];
	char m_sSoftName[JSF_LEGHTH];		//���շ�����������ƣ�
	// ��������
	int StartZmq(int nRequestPort, int nRespondPort, char *pSoftName, zmqNotif notifFun);
	
	// �رշ���
	int CloseZmq();

	// ��������
	int RecvData();

	// ��������
	int SendData(char *buff, DWORD length);

	zmqNotif m_notifFun;
protected:



	//������
	void *m_context;
	//zmqҪ��
	void *m_pRequester;
	//zmq��Ӧ
	void *m_pResponder;

	pthread_t m_ZMQRecvPt;

};


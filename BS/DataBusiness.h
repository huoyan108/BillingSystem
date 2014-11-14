#pragma once
#include <list>
#include <string.h>
#include <time.h>

using namespace std;
#include "DataTransfer.h"
#include "PGDatabase.h"
#include "PareData.h"
class CDataBusiness
{
public:
	CDataBusiness();
	~CDataBusiness();
	//���û�ִ�������
	int SetFeedResData(tagBsResMsg &tagResInfo);

	//���������̣߳�����������
	pthread_t m_DataBusinessPt;

	int ProcessBusiess();

protected:
	PGDatabase m_db;

	friend int NotifFun(char * sendName, void *pReq);

	CDataTransfer m_treansfer;

	// ����ҵ������
	int SetBusiessData(tagBstxMsg *pCommReq);

	//�������
	CPareData parseData;

	//���ݴ����б�
	//list<CommReq *> m_dataList;
	//ͨ�ŷ����б�
	list<tagBsResMsg> m_ResdataList;

};


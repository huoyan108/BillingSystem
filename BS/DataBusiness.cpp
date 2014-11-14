#include "DataBusiness.h"
#include "IniOper.h"
#include "UnitsManager.h"
float g_fSingleCost = 1.0;
//������
pthread_mutex_t g_busiessData_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_FeedData_mutex = PTHREAD_MUTEX_INITIALIZER;
extern CUnitsManager *g_pComManager;
void *threadBusiess(void *arg);
//extern CDataTransfer *g_pDatatransfer = NULL;
CDataBusiness * g_pDataBusiness = NULL;

int NotifFun(char * sendName, void *pReq)
{
	g_pDataBusiness->SetBusiessData((tagBstxMsg *)pReq);
	return 1;
}

CDataBusiness::CDataBusiness()
{
	g_pDataBusiness = this;
	pthread_create(&m_DataBusinessPt, NULL, threadBusiess, this);



	CIniOper ini;

	//��ȡ·��
	char cPath[1000];
	bzero(cPath, sizeof(cPath));
	if (ini.GetSoftPath(cPath, sizeof(cPath)) != 0)
	{
		exit(0);
	}
	strcat(cPath, "ini.lua");

	//��ȡ����
	int nRequestPort;
	int nRespondPort;
	char cSoftName[100];
	bzero(cSoftName, sizeof(cSoftName));

	if (ini.load(cPath, &nRequestPort, &nRespondPort, cSoftName) != 0)
	{
		printf("read ini error!\n");
		exit(0);
	}
	
	//������תͨ�ŷ���
	m_treansfer.StartZmq(nRequestPort, nRespondPort, cSoftName,NotifFun);


	//��ȡ���ݿ����Ӳ���
	PGConnInfo conn;
	char dbhost[100];
	char dbport[100];
	char dbname[100];
	char dbuser[100];
	char dbpwd[100];
	if (ini.load(cPath, dbhost,dbport,dbname,dbuser,dbpwd) != 0)
	{
		printf("read ini error!\n");

		exit(0);
	}
	conn.pghost = (char*)dbhost;
	conn.pgport = (char*)dbport;
	conn.dbName = (char*)dbname;
	conn.login = (char*)dbuser;
	conn.passwd = (char*)dbpwd;

	//�������ݿ�
	if (0 != m_db.Connect(conn))
	{
		printf("connect Db error!\n");

		exit(0);
	}
	printf("connect Db OK\n");
}


CDataBusiness::~CDataBusiness()
{
}

void *threadBusiess(void *arg)
{
	pthread_detach(pthread_self());

	//int state, oldstate;

	//state = PTHREAD_CANCEL_DEFERRED;
	//pthread_setcancelstate(state, &oldstate);

	CDataBusiness *me = (CDataBusiness *)arg;
	while (true)
	{
		if (me->ProcessBusiess() != TRUE)
		{
			break;
		}
		pthread_testcancel();
		sleep(1);
	}
	return NULL;
}
//�����Ʒѽ��
int CDataBusiness::ProcessBusiess()
{
	list<tagBsResMsg> resdataList;
	pthread_mutex_lock(&g_FeedData_mutex);
	resdataList.insert(resdataList.begin(), m_ResdataList.begin(), m_ResdataList.end());
	m_ResdataList.clear();
	pthread_mutex_unlock(&g_FeedData_mutex);

	char cSendBuff[1024];
	bzero(cSendBuff, sizeof(cSendBuff));
	DWORD nSendLength = 0;
	while (!resdataList.empty())
	{
		printf("send Feedback\n");

		tagBsResMsg  tagBsResMsg = resdataList.front();

		//�����µ����Ѽ�¼
		if (tagBsResMsg.bIsRecord == true)
		{
			struct tm * timeinfo;
			timeinfo = localtime(&tagBsResMsg.sendtime);
			printf("The Send date/time is: %s", asctime(timeinfo));
			char sSql[256];
			bzero(sSql, sizeof(sSql));

			sprintf(sSql, "insert into qhcharging(qtscharid,qtsentid,qtscardnumber,qtsproductid,qtdamount,qtnchargtime) values (bss_bdfs_id_seq.nextval,%d,%d,'%s',%f,to_date('%s','YYYY-MM-DD H24:MI:SS'))",
				tagBsResMsg.cQtsentid,
				tagBsResMsg.nQtscardnumber,
				tagBsResMsg.cQtsproductid,
				tagBsResMsg.fQtdamount,
				asctime(timeinfo));
			m_db.Exec(sSql);

			//UPDATE ������ SET ������ = ��ֵ WHERE ������ = ĳֵ
			sprintf(sSql, "update bss_bdfs set send_time=to_date('%s','YYYY-MM-DD H24:MI:SS'),send_times=%d,status=%d",
				asctime(timeinfo),
				tagBsResMsg.sendtimes,
				tagBsResMsg.FeedResult);
			m_db.Exec(sSql);
		}
		

		//�������
		parseData.SendToDS_FKXX(tagBsResMsg.dwSerialID,
			tagBsResMsg.FeedResult,
			cSendBuff, 
			nSendLength);
		//����
		m_treansfer.SendData(cSendBuff, nSendLength);
	}
	return TRUE;
}

// ����ҵ������,���мƷ�
int CDataBusiness::SetBusiessData(tagBstxMsg *pCommReq)
{
	//��ȡ��ǰʱ��
	time_t currtime;
	struct tm * timeinfo;

	time(&currtime);
	timeinfo = localtime(&currtime);
	printf("The current date/time is: %s", asctime(timeinfo));

	char cCurrtime[20];
	bzero(cCurrtime, sizeof(cCurrtime));
	strcat(cCurrtime, asctime(timeinfo));

	//���ؽ��
	tagBsResMsg tagResInfo;
	tagResInfo.dwSerialID = pCommReq->dwSerialID;
	tagResInfo.bIsRecord = false;
	tagResInfo.nQtscardnumber = pCommReq->nQtscardnumber;

	char sSql[256];
	bzero(sSql, sizeof(sSql));
	PGRecordset* res = NULL;


	//��ѯ��ҵID,�ܽ��
	sprintf(sSql, "select qtsentId,qtdamount from qhenterprise where  qtsentId in (select qtsentId from qhcardinfo where qtscardnumber=%d)", pCommReq->nQtscardnumber);
	res = m_db.Query(sSql);

	float fQtdamount;
	char cQtsentId[20];
	bzero(cQtsentId, sizeof(cQtsentId));

	char cQtdamount[20];
	bzero(cQtdamount, sizeof(cQtdamount));

	if (res != NULL)
	{
		printf("qtsentId,qtdamount has %d rows", res->GetTupleCount());

		strcat(cQtsentId, res->GetValue(0, 0));
		strcat(cQtdamount, res->GetValue(0, 1));

		fQtdamount = atof(cQtdamount);

		printf("sQtsentId: %s\n", cQtsentId);
		printf("sQtdamount: %s\n", cQtdamount);

		res->Destroy();

		strcat(tagResInfo.cQtsentid, cQtsentId);

	}
	else
	{
		printf("no register.\n");
		tagResInfo.nRes = NOREGISTER;
		SetFeedResData(tagResInfo);
		return -1;
	}

	//��ƷID,��ʼʱ�䡢����ʱ�䡢����(Ŀǰ����)
	sprintf(sSql, "select qtsproductid,to_char(qtnbegintime,'YYYY-MM-DD HH24:MI:SS'),to_char(qtnendtime,'YYYY-MM-DD HH24:MI:SS') from qhentproductmapping,qhproductinfo where qhentproductmapping.qtsproductid=qhproductinfo.qtsproductid and qhproductinfo.qtdcategory=%d and qhentproductmapping.qtsentid = '%s'",
		pCommReq->nCategory, cQtsentId);
	res = m_db.Query(sSql);

	char cQtsproductid[20];
	bzero(cQtsproductid, sizeof(cQtsproductid));

	char cQtnbegintime[20];
	bzero(cQtnbegintime, sizeof(cQtnbegintime));

	char cQtnendtime[20];
	bzero(cQtnendtime, sizeof(cQtnendtime));

	if (res != NULL)
	{
		printf("qtnbegintime,qtnendtime,qtdmessagecount has %d rows", res->GetTupleCount());

		strcat(cQtsproductid, res->GetValue(0, 0));
		strcat(cQtnbegintime, res->GetValue(0, 1));
		strcat(cQtnendtime, res->GetValue(0, 2));

	
		printf("qtnbegintime: %s\n", cQtsproductid);
		printf("sQtnbegintime: %s\n", cQtnbegintime);
		printf("sQtnendtime: %s\n", cQtnendtime);

		res->Destroy();

		if (cQtnendtime==NULL)
		{
			//û��ʱ�����ƾ�������,�Ƚ����
			if (fQtdamount > g_fSingleCost)
			{
				//������
				printf("ok.\n");
				tagResInfo.nRes = PERMISSION;
				strcat(tagResInfo.cQtsproductid, cQtsproductid);
				tagResInfo.fQtdamount = fQtdamount;
				tagResInfo.bIsRecord = true;

				SetFeedResData(tagResInfo);
				return 0;
			}
			else
			{
				//����
				printf("no money.\n");
				tagResInfo.nRes = NOMONEY;
				SetFeedResData(tagResInfo);
				return -1;
			}
		}
		else
		{
			//���»��߰��꣬�ж��Ƿ���ʱ�䷶Χ��
			if (strcmp(cQtnbegintime, cCurrtime)<0 && strcmp(cQtnendtime,cCurrtime)>0)
			{
				printf("ok.\n");
				tagResInfo.nRes = PERMISSION;
				SetFeedResData(tagResInfo);
			}
			else
			{
				//����ʱ��
				printf("teach date.\n");
				tagResInfo.nRes = TEACHDATE;
				SetFeedResData(tagResInfo);
				return -1;
			}
		}
	}
	else
	{
		//û�з����Ʒ
		printf("no category.\n");
		tagResInfo.nRes = NOCATEGORY;
		SetFeedResData(tagResInfo);
		return -1;
	}

	return 0;
}

//���÷���
int CDataBusiness::SetFeedResData(tagBsResMsg &tagResInfo)
{
	pthread_mutex_lock(&g_FeedData_mutex);
	m_ResdataList.push_back(tagResInfo);
	pthread_mutex_unlock(&g_FeedData_mutex);

	return 0;
}
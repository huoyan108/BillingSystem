#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_
#include <time.h>
using namespace std;
#define DWORD unsigned long
#define BYTE unsigned char

/*Ҫ�õ���
*/
#define PROCESS_FRAME_DATA_LENGTH  1024 //���ݴ���֡����

#define FSF_LEGHTH 20  //���ͷ�ռλ����

#define JSF_LEGHTH 20 //���շ�ռλ����

#define SJCD_LEGHT 2 //���ݳ���ռλ����
/*Ҫ�õ���
*/
struct _SEND_DATA_TAG
{
	unsigned int nSeq;

};

#define TIME_CHECK_SELF 5 //�Լ�Ƶ��Ϊ5��

#define PARAME_LENGTH 50 //�ַ��������ĳ���

#define LIST_COUNT_WAIT_FOR_SEND  20  //�����д�ŵ�����


enum DATA_FROM_TYPE
{
	DATA_FROM_TCP = 1, //TCP���ӷ��͵�����
	DATA_FROM_UDP,
	DATA_FROM_BD
};
enum {
	FEEDBACK_SJREQ,    //��������
	FEEDBACK_ICXX,		//IC��Ϣ   
	FEEDBACK_ZJXX,		//�Լ���Ϣ
	FEEDBACK_FKXX		//������Ϣ
};
enum{
	CUNPACK_NULL = 0,
	CUNPACK_DWXX,		//��λ��Ϣ 01
	CUNPACK_TXXX,		//ͨ����Ϣ 02
	CUNPACK_TXHZ,		//ͨ�Ż�ִ 03
	CUNPACK_ICXX,		//IC��Ϣ   04
	CUNPACK_ZJXX,		//�Լ���Ϣ 05
	CUNPACK_FKXX		//������Ϣ 06
};

enum
{
	CUNPACK_TXFS_DS = 1, //ͨ�ŷ���
	CUNPACK_XTZJ_DS, //ϵͳ�Լ�
	CUNPACK_XTYD_DS  //����Ӧ��
};

//������Ϣ
enum
{
	OPERATE_PUSH_SUCCESS = 0, //�ύ�ɹ�
	OPERATE_SEND_SUCCESS = 3, //���ͳɹ�
	OPERATE_PUSH_FAIL = 2  //�ύʧ��
};

//�û���״̬
enum
{
	MACHINE_STATUS_COM_UNOPEN = 1, //����δ��
	MACHINE_STATUS_WORK, //��������
	MACHINE_STATUS_MASK //����״̬
};
enum {
	BDFSREQ,    //��������
	ICJCREQ,		//IC��Ϣ   
	XTZJREQ		//�Լ�
};
//�Լ���Ϣ
typedef struct tagSelfCheckInfo
{
	DWORD LocalID;
	char ICCardState;		// IC��״̬
	char HardState;		// Ӳ��״̬
	char Batterystate;		// ��ص���
	char InState;			// ��վ״̬
	char PowerState[6];	// ����״��
}SelfCheckInfo, *lpSelfCheckInfo;

//������Ϣ
typedef struct tagFeedbackInfo
{
	DWORD dwSerialID; //�������
	DWORD LocalID;
	char FeedResult; //�������
	char Reserve[10];   // ����
	time_t sendtime;	//����ʱ��
	int sendtimes;		//���ʹ���
}FeedbackInfo, *lpFeedbackInfo;

//���ݴ���ṹ��
struct tagFrameData
{
	int nDataStyle;				
	DWORD dwSerialID;		//�������
	char pFrameData[PROCESS_FRAME_DATA_LENGTH];
	DWORD dwFrameDataLen; //���ݳ���
	int send_times;		//���ʹ���
	//DATA_FROM_TYPE eFromType; //������Դ
	//char nComID; //���ں�
	//char cDev[20];
};
//ͨ������/�������ͣ���ת�����ͣ�
typedef struct tagBdReq
{
	DWORD dwSerialID; //�������
	DWORD SourceAddress;		//���ͷ���ַ  ���ͷ�Ϊ0�����շ��е�ַ������ָ�ӻ�����
	DWORD DestAddress;			//���շ���ַ	���շ�Ϊ0�����ͷ��е�ַ��ͨ��
	int  nMsgType;							//0:����    1:���� 2���췢
	DWORD InfoLen;			//���ݳ���(��λ��Bit)  ���ܴ��ֽ�������ΪBCD���ܲ������ֽ�
	char  InfoBuff[211];	//����:Max 120��  BCD:Max 420

	//DWORD LocalID;

	////����ͨ��
	//int  ifSecret;			//�̶�����
	//int  ifQuick;			//00:��ͨ   01:�ؿ�[ע����Э��涨�෴]
	//int  ifCmd;			//[��׼Э��2.1���޴���] ����ʶ��[0:ͨ��  1:����ʶ��]
	//int  ifAnswer;			//[��׼Э��2.1���޴���] �Ƿ�Ӧ��


	//DWORD dwTerminalID; //�ն˺�
	//char nSended; //�Ƿ���

}BdReq, *lpBdReq;

/************************************************************************/
//ָ�ӻ�������                                                     
/************************************************************************/
typedef struct tagCardInfoRead
{
	char cDev[20];				//���ں�
	DWORD LocalID;
	char FrameNum;				//����
	//��0֡�����õ��ı���
	DWORD BroadcastID;			//ͨ��ID
	char MachineCharacter;		//�û�������
	unsigned short ServeFreq;			//����Ƶ��
	unsigned short CommLen;
	char CommuLeave;			//ͨ�ż���
	char EncryptFlag;			//���ܱ�־
	unsigned short SubordinateNum;		//�¼��û�����
	//��N֡�����õ��ı���
	char CurrFrameSubNum;		//��֡�����û���
	DWORD lpSubUserAddrs[100];	//ָ���¼��û���ַ��ָ��
} CardInfoRead, *lpCardInfoRead;



/************************************************************************/
///�û���������                                                     
/************************************************************************/
//ͨ�Ż�ִ
typedef struct tagSendBackInfo
{
	DWORD dwSendID;
	DWORD dwRecvID;
	char nHour;
	char nMinute;
	char nSecond;
}SendBackInfo, *lpSendBackInfo;

//������λ��Ϣ
typedef struct  tagPosInfo
{
	char  ifSecret;	//0:����Կ  1:����Կ
	char  Precision;	//0:һ��(20m)  1:����(100m)
	char  ifUrgent;		//0:��  1:����
	char  ifMultiValue;	//0:��ֵ��  1:��
	DWORD LocalID;	//ָ�����û�����ѯ�û����û���ַ

	char pSecrets[6]; //��Կ

	char  Hour;		// ��λʱ��--ʱ
	char  Minute;	// ��λʱ��--��
	char  Second;	// ��λʱ��--��
	char  CentiSecond;	// ��λʱ��--0.01��
	char  LongDeg;	//���ȣ���
	char  LongMin;	//��
	char  LongSec;	//��
	char  LongDecsec;	//0.1��
	char  LatDeg;	//γ�ȣ���
	char  LatMin;	//��
	char  LatSec;	//��
	char  LatDecsec;	//0.1��

	char nAltSign; //�̷߳���,0����1,��
	DWORD Altitude;	//�߳�
	char nEfSign; //�߳��쳣����
	DWORD Ef;		//�߳��쳣
}PosInfo, *lpPosInfo;

//ͨ����Ϣ������ת���յ���
typedef struct tagCommInfo
{
	DWORD LocalID;	//����ID(���շ�ID�������û�)
	char  ifBCD;	//0:����  1:���� 
	char  ifUrgent; //0:�ؿ�  1����ͨ
	int  ifSecret;	//0:����Կ 1:����Կ
	DWORD SrcAddress;	//���ŷ���ַ
	char  CommHour;	//
	char  CommMin;	//
	char CommSecond; //
	unsigned short CommLenByte;
	DWORD CommLenBit;	//���ĳ���(��λ��bit)  ���ܴ��ֽ�������ΪBCD���ܲ������ֽ�
	char  CommBuff[211];
	int  CRCFlag;	//00:CRCУ����ȷ 01:CRCУ�����
}CommInfo, *lpCommInfo;

/************************************************************************/
///���赽�û���                                                       
/************************************************************************/
//ͨ������
typedef struct tagCommReq
{
	DWORD LocalID;
	DWORD SourceAddress;		//���շ���ַ

	DWORD DestAddress;		//���շ���ַ
	DWORD InfoLen;			//���ݳ���(��λ��Bit)  ���ܴ��ֽ�������ΪBCD���ܲ������ֽ�
	char  InfoBuff[211];	//����:Max 120��  BCD:Max 420
	//����ͨ��
	int  ifSecret;			//�̶�����
	int  ifQuick;			//00:��ͨ   01:�ؿ�[ע����Э��涨�෴]
	int  ifBCD;			//0:����    1:����
	int  ifCmd;			//[��׼Э��2.1���޴���] ����ʶ��[0:ͨ��  1:����ʶ��]
	int  ifAnswer;			//[��׼Э��2.1���޴���] �Ƿ�Ӧ��

	//
	DWORD dwSerialID; //ͨ����ˮ��
	DWORD dwTerminalID; //�ն˺�
	//
	char nSended; //�Ƿ���
}CommReq, *lpCommReq;

typedef struct tagClientCheck
{
	DWORD dwAnswerIndex;
}ClientCheck,*lpClientCheck;

/************************************************************************/
///ϵͳ�ṹ��                                                       
/************************************************************************/
#include <time.h>
typedef struct tagSendDataInfo
{

	tagCommReq stCommReq; //ͨ������ṹ��

	time_t tRecvTime;
	time_t tSendTime;

	char nSended;
	char nRecved;

	DWORD dwIndexInTable; //���е�����
}SendDataInfo, *lpSendDataInfo;

//ϵͳ��ʼ���ṹ��
typedef struct tagSysInial
{
	DWORD dwListenPort_TCP;
	DWORD dwListenPort_UDP;
	char pServerName[50];
	char pDbName[50];
	char pUserName[50];

	DWORD dwListCount; //�û�������������
}SysInial;


#endif

#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_
#include <time.h>
using namespace std;
#define DWORD unsigned long
#define BYTE unsigned char

/*要用到的
*/
#define PROCESS_FRAME_DATA_LENGTH  1024 //数据处理帧长度

#define FSF_LEGHTH 20  //发送方占位长度

#define JSF_LEGHTH 20 //接收方占位长度

#define SJCD_LEGHT 2 //数据长度占位长度
/*要用到的
*/
struct _SEND_DATA_TAG
{
	unsigned int nSeq;

};

#define TIME_CHECK_SELF 5 //自检频度为5秒

#define PARAME_LENGTH 50 //字符串参数的长度

#define LIST_COUNT_WAIT_FOR_SEND  20  //队列中存放的数据


enum DATA_FROM_TYPE
{
	DATA_FROM_TCP = 1, //TCP连接发送的数据
	DATA_FROM_UDP,
	DATA_FROM_BD
};
enum {
	FEEDBACK_SJREQ,    //数据请求
	FEEDBACK_ICXX,		//IC信息   
	FEEDBACK_ZJXX,		//自检信息
	FEEDBACK_FKXX		//反馈信息
};
enum{
	CUNPACK_NULL = 0,
	CUNPACK_DWXX,		//定位信息 01
	CUNPACK_TXXX,		//通信信息 02
	CUNPACK_TXHZ,		//通信回执 03
	CUNPACK_ICXX,		//IC信息   04
	CUNPACK_ZJXX,		//自检信息 05
	CUNPACK_FKXX		//反馈信息 06
};

enum
{
	CUNPACK_TXFS_DS = 1, //通信发送
	CUNPACK_XTZJ_DS, //系统自检
	CUNPACK_XTYD_DS  //心跳应答
};

//反馈信息
enum
{
	OPERATE_PUSH_SUCCESS = 0, //提交成功
	OPERATE_SEND_SUCCESS = 3, //发送成功
	OPERATE_PUSH_FAIL = 2  //提交失败
};

//用户机状态
enum
{
	MACHINE_STATUS_COM_UNOPEN = 1, //串口未打开
	MACHINE_STATUS_WORK, //正常工作
	MACHINE_STATUS_MASK //屏蔽状态
};
enum {
	BDFSREQ,    //数据请求
	ICJCREQ,		//IC信息   
	XTZJREQ		//自检
};
//自检信息
typedef struct tagSelfCheckInfo
{
	DWORD LocalID;
	char ICCardState;		// IC卡状态
	char HardState;		// 硬件状态
	char Batterystate;		// 电池电量
	char InState;			// 入站状态
	char PowerState[6];	// 功率状况
}SelfCheckInfo, *lpSelfCheckInfo;

//反馈信息
typedef struct tagFeedbackInfo
{
	DWORD dwSerialID; //发送序号
	DWORD LocalID;
	char FeedResult; //反馈结果
	char Reserve[10];   // 保留
	time_t sendtime;	//发送时间
	int sendtimes;		//发送次数
}FeedbackInfo, *lpFeedbackInfo;

//数据处理结构体
struct tagFrameData
{
	int nDataStyle;				
	DWORD dwSerialID;		//发送序号
	char pFrameData[PROCESS_FRAME_DATA_LENGTH];
	DWORD dwFrameDataLen; //数据长度
	int send_times;		//发送次数
	//DATA_FROM_TYPE eFromType; //数据来源
	//char nComID; //串口号
	//char cDev[20];
};
//通信请求/北斗发送（中转到发送）
typedef struct tagBdReq
{
	DWORD dwSerialID; //发送序号
	DWORD SourceAddress;		//发送方地址  发送方为0，接收方有地址则任意指挥机发送
	DWORD DestAddress;			//接收方地址	接收方为0，发送方有地址则通播
	int  nMsgType;							//0:汉字    1:代码 2：混发
	DWORD InfoLen;			//数据长度(单位：Bit)  不能传字节数，因为BCD可能不是整字节
	char  InfoBuff[211];	//汉字:Max 120个  BCD:Max 420

	//DWORD LocalID;

	////报文通信
	//int  ifSecret;			//固定填零
	//int  ifQuick;			//00:普通   01:特快[注：和协议规定相反]
	//int  ifCmd;			//[标准协议2.1版无此项] 口令识别[0:通信  1:口令识别]
	//int  ifAnswer;			//[标准协议2.1版无此项] 是否应答


	//DWORD dwTerminalID; //终端号
	//char nSended; //是否发送

}BdReq, *lpBdReq;

/************************************************************************/
//指挥机到分离                                                     
/************************************************************************/
typedef struct tagCardInfoRead
{
	char cDev[20];				//串口号
	DWORD LocalID;
	char FrameNum;				//帪号
	//第0帧数据用到的变量
	DWORD BroadcastID;			//通播ID
	char MachineCharacter;		//用户机特征
	unsigned short ServeFreq;			//服务频度
	unsigned short CommLen;
	char CommuLeave;			//通信级别
	char EncryptFlag;			//加密标志
	unsigned short SubordinateNum;		//下级用户总数
	//第N帧数据用到的变量
	char CurrFrameSubNum;		//本帧下属用户数
	DWORD lpSubUserAddrs[100];	//指向下级用户地址的指针
} CardInfoRead, *lpCardInfoRead;



/************************************************************************/
///用户机到外设                                                     
/************************************************************************/
//通信回执
typedef struct tagSendBackInfo
{
	DWORD dwSendID;
	DWORD dwRecvID;
	char nHour;
	char nMinute;
	char nSecond;
}SendBackInfo, *lpSendBackInfo;

//北斗定位信息
typedef struct  tagPosInfo
{
	char  ifSecret;	//0:无密钥  1:有密钥
	char  Precision;	//0:一档(20m)  1:二档(100m)
	char  ifUrgent;		//0:否  1:紧急
	char  ifMultiValue;	//0:多值解  1:无
	DWORD LocalID;	//指挥型用户所查询用户的用户地址

	char pSecrets[6]; //密钥

	char  Hour;		// 定位时间--时
	char  Minute;	// 定位时间--分
	char  Second;	// 定位时间--秒
	char  CentiSecond;	// 定位时间--0.01秒
	char  LongDeg;	//经度－度
	char  LongMin;	//分
	char  LongSec;	//秒
	char  LongDecsec;	//0.1秒
	char  LatDeg;	//纬度－度
	char  LatMin;	//分
	char  LatSec;	//秒
	char  LatDecsec;	//0.1秒

	char nAltSign; //高程符号,0正，1,负
	DWORD Altitude;	//高程
	char nEfSign; //高程异常符号
	DWORD Ef;		//高程异常
}PosInfo, *lpPosInfo;

//通信信息（从中转接收到）
typedef struct tagCommInfo
{
	DWORD LocalID;	//本机ID(接收方ID，含子用户)
	char  ifBCD;	//0:汉字  1:代码 
	char  ifUrgent; //0:特快  1：普通
	int  ifSecret;	//0:无密钥 1:有密钥
	DWORD SrcAddress;	//发信方地址
	char  CommHour;	//
	char  CommMin;	//
	char CommSecond; //
	unsigned short CommLenByte;
	DWORD CommLenBit;	//电文长度(单位：bit)  不能传字节数，因为BCD可能不是整字节
	char  CommBuff[211];
	int  CRCFlag;	//00:CRC校验正确 01:CRC校验错误
}CommInfo, *lpCommInfo;

/************************************************************************/
///外设到用户机                                                       
/************************************************************************/
//通信请求
typedef struct tagCommReq
{
	DWORD LocalID;
	DWORD SourceAddress;		//接收方地址

	DWORD DestAddress;		//接收方地址
	DWORD InfoLen;			//数据长度(单位：Bit)  不能传字节数，因为BCD可能不是整字节
	char  InfoBuff[211];	//汉字:Max 120个  BCD:Max 420
	//报文通信
	int  ifSecret;			//固定填零
	int  ifQuick;			//00:普通   01:特快[注：和协议规定相反]
	int  ifBCD;			//0:汉字    1:代码
	int  ifCmd;			//[标准协议2.1版无此项] 口令识别[0:通信  1:口令识别]
	int  ifAnswer;			//[标准协议2.1版无此项] 是否应答

	//
	DWORD dwSerialID; //通信流水号
	DWORD dwTerminalID; //终端号
	//
	char nSended; //是否发送
}CommReq, *lpCommReq;

typedef struct tagClientCheck
{
	DWORD dwAnswerIndex;
}ClientCheck,*lpClientCheck;

/************************************************************************/
///系统结构体                                                       
/************************************************************************/
#include <time.h>
typedef struct tagSendDataInfo
{

	tagCommReq stCommReq; //通信申请结构体

	time_t tRecvTime;
	time_t tSendTime;

	char nSended;
	char nRecved;

	DWORD dwIndexInTable; //表中的索引
}SendDataInfo, *lpSendDataInfo;

//系统初始化结构体
typedef struct tagSysInial
{
	DWORD dwListenPort_TCP;
	DWORD dwListenPort_UDP;
	char pServerName[50];
	char pDbName[50];
	char pUserName[50];

	DWORD dwListCount; //用户机队列最大个数
}SysInial;


#endif

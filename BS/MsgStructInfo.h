#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_
#include <string>
using namespace std;

#define DWORD unsigned long
#define BYTE unsigned char
#define WORD unsigned int


#define PROCESS_FRAME_DATA_LENGTH  1024 //数据处理帧长度

#define FSF_LEGHTH 20  //发送方占位长度

#define JSF_LEGHTH 20 //接收方占位长度

#define SJCD_LEGHT 2 //数据长度占位长度

#define TIME_CHECK_SELF 5 //自检频度为5秒

#define PARAME_LENGTH 50 //字符串参数的长度

#define LIST_COUNT_WAIT_FOR_SEND  20  //队列中存放的数据

enum{
	TX_NULL = 0,
	TX_FWJQ,		//服务鉴权 01
	TX_KFQQ,		//扣费请求 02
	TX_JQJG,		//鉴权信息 03
};

typedef struct tagBstxMsg
{
	//请求类型
	WORD nType;

	//鉴权索引
	DWORD nAuthenticationId;
	//企业编号
	string sQtsentid;
	//服务类型
	WORD	 nCategory;
	//接收方
	DWORD nRecvId;

//	DWORD dwSerialID;			//发送序号
//	WORD nQtscardnumber;	//IC卡号
//	WORD		 nCategory;		//产品类型

}BstxMsg;

enum ResEnum{ PERMISSION, NOCATEGORY, NOMONEY, STATEERROR, TEACHDATE, NOREGISTER };
typedef struct tagBsResMsg
{
	
	DWORD nAuthenticationId;   //鉴权索引
	ResEnum nRes;				//验证结果		0:ok,1:state error,2:no money,3:teach date,4:no register,5 no category
	string sQtsentid;
	//WORD nQtscardnumber;		//IC卡号
	//char cQtsproductid[20]; //产品标识
	//float fQtdamount;			//金额
	//char cTimestamp[20];	//扣费时间
}BsresMsg;

 
#endif

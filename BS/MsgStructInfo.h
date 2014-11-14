#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_

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
	CUNPACK_NULL = 0,
	CUNPACK_FWJQ,		//服务鉴权 01
	CUNPACK_KFQQ,		//扣费请求 02
	CUNPACK_JQJG,		//鉴权信息 03
};

typedef struct tagBstxMsg
{
	DWORD dwSerialID;			//发送序号
	WORD nQtscardnumber;	//IC卡号
	WORD		 nCategory;		//产品类型

}BstxMsg;

enum ResEnum{ PERMISSION, STATEERROR, NOMONEY, TEACHDATE, NOREGISTER, NOCATEGORY };
typedef struct tagBsResMsg
{
	DWORD dwSerialID;		//发送序号
	ResEnum nRes;				//验证结果		0:ok,1:state error,2:no money,3:teach date,4:no register,5 no category
	bool bIsRecord;				//是否记录
	char cQtsentid[20];		//企业ID
	WORD nQtscardnumber;		//IC卡号
	char cQtsproductid[20]; //产品标识
	float fQtdamount;			//金额
	//char cTimestamp[20];	//扣费时间
}BsresMsg;

 
#endif

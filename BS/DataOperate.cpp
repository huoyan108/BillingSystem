#include "StdAfx.h"
#include "DataOperate.h"

CDataOperate* CDataOperate::m_pDataOperatePtr = NULL;
CDataOperate::CDataOperate(void)
{
}

CDataOperate::~CDataOperate(void)
{
}

CDataOperate* CDataOperate::GetDataOperatePtr()
{
	if(!m_pDataOperatePtr)
		m_pDataOperatePtr = new CDataOperate;
	return m_pDataOperatePtr;
}

typedef struct tagSInfoTitle
{
	int iInfoID;
	char cTitle[6];
}SInfoTitle;

const int INFOCOUNT_BD = 6;
SInfoTitle InfoTitle_BD[] = 
{
	{CUNPACK_DWXX,		"DWXX"},	
	{CUNPACK_TXXX,		"TXXX"},	
	{CUNPACK_TXHZ,		"TXHZ"},	
	{CUNPACK_ICXX,		"ICXX"},	
	{CUNPACK_ZJXX,		"ZJXX"},	
	{CUNPACK_FKXX,		"FKXX"},
};

BYTE CDataOperate::ExplainData_BD(BYTE* pSrcBuffer,DWORD dwBufferLen,BYTE* pDestBuffer)
{
	BYTE nReportID;
	int i;

	for(i = 0;i<INFOCOUNT_BD;i++)
	{
		if(memcmp(pSrcBuffer+1,InfoTitle_BD[i].cTitle,4) == 0)
		{
			nReportID = InfoTitle_BD[i].iInfoID;
			break;
		}
	}

	if(i >= INFOCOUNT_BD)
		return CUNPACK_NULL;

	int  f_iCurLen;
	DWORD  f_dwTemp;//无符号

	switch(nReportID)
	{
	case CUNPACK_ICXX:
		{
			lpCardInfoRead f_pCardInfoRead;
			f_pCardInfoRead = (lpCardInfoRead)pDestBuffer;

			DWORD f_dwIDCount=0; //下属子用户的数量

			f_iCurLen = 7;
			//本机地址
			f_dwTemp = pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_pCardInfoRead->LocalID = f_dwTemp;
			f_iCurLen++;
			//帪号
			f_pCardInfoRead->FrameNum = pSrcBuffer[f_iCurLen];
			f_iCurLen++;

			if(f_pCardInfoRead->FrameNum == 0) //判断帧号是否为首帧
			{
				//通波ID		
				f_dwTemp = pSrcBuffer[f_iCurLen];
				f_dwTemp *=256;
				f_iCurLen++;
				f_dwTemp += pSrcBuffer[f_iCurLen];
				f_dwTemp *=256;
				f_iCurLen++;
				f_dwTemp += pSrcBuffer[f_iCurLen];
				f_pCardInfoRead->BroadcastID = f_dwTemp;
				f_iCurLen++;
				//用户机特征
				f_pCardInfoRead->MachineCharacter = pSrcBuffer[f_iCurLen];
				f_iCurLen++;
				//服务频度
				f_dwTemp = pSrcBuffer[f_iCurLen];
				f_dwTemp *= 256;
				f_iCurLen++;
				f_dwTemp += pSrcBuffer[f_iCurLen];
				f_pCardInfoRead->ServeFreq = (WORD)f_dwTemp;
				f_iCurLen++;
				//通信级别
				f_pCardInfoRead->CommuLeave = pSrcBuffer[f_iCurLen];
				f_iCurLen++;
				//加密标志
				f_pCardInfoRead->EncryptFlag = pSrcBuffer[f_iCurLen];
				f_iCurLen++;
				//下级用户总数
				f_dwTemp = pSrcBuffer[f_iCurLen];
				f_dwTemp *= 256;
				f_iCurLen++;
				f_dwTemp += pSrcBuffer[f_iCurLen];
				f_pCardInfoRead->SubordinateNum = (WORD)f_dwTemp;
				f_iCurLen++;
			}
			else
			{
				//下级用户ID 数目
				f_pCardInfoRead->CurrFrameSubNum = (dwBufferLen-12)/3;
				//下级用户地址
				for (i = 0 ; i < f_pCardInfoRead->CurrFrameSubNum; i++)   //存储下级用户ID
				{
					f_dwTemp = pSrcBuffer[f_iCurLen];
					f_dwTemp *= 256;
					f_iCurLen++;
					f_dwTemp += pSrcBuffer[f_iCurLen];
					f_dwTemp *= 256;
					f_iCurLen++;
					f_dwTemp += pSrcBuffer[f_iCurLen];
					f_pCardInfoRead->lpSubUserAddrs[i] = f_dwTemp;
					f_iCurLen++;
				}
			}	
		}
		return CUNPACK_ICXX;
	case CUNPACK_ZJXX:
		{
			lpSelfCheckInfo f_pSelfCheckInfo;
			f_pSelfCheckInfo=(lpSelfCheckInfo)pDestBuffer;  
			f_iCurLen = 7;

			//本机用户地址
			f_dwTemp = pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_pSelfCheckInfo->LocalID = f_dwTemp;
			f_iCurLen++;

			//IC卡状态
			f_pSelfCheckInfo->ICCardState = pSrcBuffer[f_iCurLen];
			f_iCurLen++;

			//硬件状态
			f_pSelfCheckInfo->HardState = pSrcBuffer[f_iCurLen];
			f_iCurLen++;

			//电池电量
			f_pSelfCheckInfo->Batterystate = pSrcBuffer[f_iCurLen];
			f_iCurLen++;

			//入站状态
			f_pSelfCheckInfo->InState = pSrcBuffer[f_iCurLen];
			f_iCurLen++;

			//功率信息
			for(i = 0 ; i < 6 ; i ++)
			{
				f_pSelfCheckInfo->PowerState[i] = pSrcBuffer[f_iCurLen];
				f_iCurLen++;
			}
		}
		return CUNPACK_ZJXX;
	case CUNPACK_FKXX:
		{
			lptagBsResMsg f_ptagBsResMsg;			
			f_ptagBsResMsg=(lptagBsResMsg)pDestBuffer;  //定义结构指针(没有分配具体地址)
			f_iCurLen = 7;

			//本机用户地址
			f_dwTemp = pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_ptagBsResMsg->LocalID = f_dwTemp;
			f_iCurLen++;

			//反馈结果
			f_ptagBsResMsg->FeedResult = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//保留信息
			f_ptagBsResMsg->Reserve[0] = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			f_ptagBsResMsg->Reserve[1] = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			f_ptagBsResMsg->Reserve[2] = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			f_ptagBsResMsg->Reserve[3] = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
		}
		return CUNPACK_FKXX;
	}

}

const int INFOCOUNT_TCP = 3;
SInfoTitle InfoTitle_TCP[] = 
{
	{CUNPACK_TXFS_DS,		"TXFS"},	
	{CUNPACK_XTZJ_DS,		"XTZJ"},	
	{CUNPACK_XTYD_DS,       "XTYD"},
};
BYTE CDataOperate::ExplainData_TCP(BYTE* pSrcBuffer,DWORD dwBufferLen,BYTE* pDestBuffer)
{
	BYTE nReportID;
	int i;

	for(i = 0;i<INFOCOUNT_TCP;i++)
	{
		if(memcmp(pSrcBuffer+1,InfoTitle_TCP[i].cTitle,4) == 0)
		{
			nReportID = InfoTitle_TCP[i].iInfoID;
			break;
		}
	}

	if(i >= INFOCOUNT_TCP)
		return CUNPACK_NULL;

	int  f_iCurLen;
	DWORD  f_dwTemp;//无符号

	switch(nReportID)
	{
	case CUNPACK_TXFS_DS:
		{
			CommReq* pReq;
			pReq = (CommReq*)pDestBuffer;

			f_iCurLen = 7;
			//通信流水
			pReq->dwSerialID = pSrcBuffer[f_iCurLen]*256*256*256;
			f_iCurLen++;
			pReq->dwSerialID += pSrcBuffer[f_iCurLen]*256*256;
			f_iCurLen++;
			pReq->dwSerialID += pSrcBuffer[f_iCurLen]*256;
			f_iCurLen++;
			pReq->dwSerialID += pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//指挥机ID
			pReq->LocalID = pSrcBuffer[f_iCurLen]*256*256*256;
			f_iCurLen++;
			pReq->LocalID += pSrcBuffer[f_iCurLen]*256*256;
			f_iCurLen++;
			pReq->LocalID += pSrcBuffer[f_iCurLen]*256;
			f_iCurLen++;
			pReq->LocalID += pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//接收方ID
			pReq->DestAddress = pSrcBuffer[f_iCurLen]*256*256*256;
			f_iCurLen++;
			pReq->DestAddress += pSrcBuffer[f_iCurLen]*256*256;
			f_iCurLen++;
			pReq->DestAddress += pSrcBuffer[f_iCurLen]*256;
			f_iCurLen++;
			pReq->DestAddress += pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//通信编码
			pReq->ifBCD = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//加急
			pReq->ifQuick = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//信息长度
			pReq->InfoLen = pSrcBuffer[f_iCurLen]*256;
			f_iCurLen++;
			pReq->InfoLen += pSrcBuffer[f_iCurLen];
			f_iCurLen++;
			//信息内容
			f_dwTemp = RoundMax(pReq->InfoLen,8); //通信内容字节数

			//信息长度
			if(f_dwTemp > 210)
				f_dwTemp = 210;

			memcpy(pReq->InfoBuff,pSrcBuffer+f_iCurLen,f_dwTemp);
			pReq->InfoBuff[f_dwTemp] = 0;
		}
		return CUNPACK_TXFS_DS;
	case CUNPACK_XTZJ_DS:
		{
		}
		return CUNPACK_XTZJ_DS;
	case CUNPACK_XTYD_DS:
		{
			tagClientCheck* pCheck;
			pCheck = (tagClientCheck*)pDestBuffer;

			f_iCurLen = 7;
			pCheck->dwAnswerIndex = pSrcBuffer[f_iCurLen]*256*256*256;
			f_iCurLen++;
			pCheck->dwAnswerIndex += pSrcBuffer[f_iCurLen]*256*256;
			f_iCurLen++;
			pCheck->dwAnswerIndex += pSrcBuffer[f_iCurLen]*256;
			f_iCurLen++;
			pCheck->dwAnswerIndex += pSrcBuffer[f_iCurLen];
			f_iCurLen++;
		}
		return CUNPACK_XTYD_DS;
	}
}

DWORD CDataOperate::SendToDS_XTJC(DWORD dwIndex,BYTE* pSendBuffer)
{
	int f_iCurLen;

	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"XTJC",4);

	//检测序号
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwIndex));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwIndex));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwIndex));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwIndex));
	f_iCurLen++;

	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	//校验和
	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);
	
	f_iCurLen++;
	return f_iCurLen;
}

DWORD CDataOperate::SendToDS_DWXX(tagPosInfo& stPosInfo,BYTE* pSendBuffer)
{
	int f_iCurLen;

	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"DWXX",4);

	//定位用户机ID
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stPosInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stPosInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stPosInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stPosInfo.LocalID));
	f_iCurLen++;
	//密钥
	pSendBuffer[f_iCurLen] = stPosInfo.ifSecret;
	f_iCurLen++;
	//精度
	pSendBuffer[f_iCurLen] = stPosInfo.Precision;
	f_iCurLen++;
	//加急
	pSendBuffer[f_iCurLen] = stPosInfo.ifUrgent;
	f_iCurLen++;
	//多值解
	pSendBuffer[f_iCurLen] = stPosInfo.ifMultiValue;
	f_iCurLen++;
	//时间
	pSendBuffer[f_iCurLen] = stPosInfo.Hour;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.Minute;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.Second;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.CentiSecond;
	f_iCurLen++;
	//经度
	pSendBuffer[f_iCurLen] = stPosInfo.LongDeg;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LongMin;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LongSec;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LongDecsec;
	f_iCurLen++;
	//纬度
	pSendBuffer[f_iCurLen] = stPosInfo.LatDeg;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LatMin;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LatSec;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stPosInfo.LatDecsec;
	f_iCurLen++;
	//高程符号
	pSendBuffer[f_iCurLen] = stPosInfo.nAltSign;
	f_iCurLen++;
	//高程
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stPosInfo.Altitude));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stPosInfo.Altitude));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stPosInfo.Altitude));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stPosInfo.Altitude));
	f_iCurLen++;
	//高程异常符号
	pSendBuffer[f_iCurLen] = stPosInfo.nEfSign;
	f_iCurLen++;
	//高程异常
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stPosInfo.Ef));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stPosInfo.Ef));
	f_iCurLen++;
	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);
	f_iCurLen++;
	return f_iCurLen;
}

DWORD CDataOperate::SendToDS_TXXX(tagCommInfo& stCommInfo,BYTE* pSendBuffer)
{
	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"TXXX",4);

	DWORD f_iCurLen;

	//用户机地址
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stCommInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stCommInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stCommInfo.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stCommInfo.LocalID));
	f_iCurLen++;
	//发信方地址
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stCommInfo.SrcAddress));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stCommInfo.SrcAddress));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stCommInfo.SrcAddress));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stCommInfo.SrcAddress));
	f_iCurLen++;
	//通信编码
	pSendBuffer[f_iCurLen] = stCommInfo.ifBCD;
	f_iCurLen++;
	//通信类别
	pSendBuffer[f_iCurLen] = stCommInfo.ifUrgent;
	f_iCurLen++;
	//加密标志
	pSendBuffer[f_iCurLen] = stCommInfo.ifSecret;
	f_iCurLen++;
	//时
	pSendBuffer[f_iCurLen] = stCommInfo.CommHour;
	f_iCurLen++;
	//分
	pSendBuffer[f_iCurLen] = stCommInfo.CommMin;
	f_iCurLen++;
	//秒
	pSendBuffer[f_iCurLen] = stCommInfo.CommSecond;
	f_iCurLen++;
	//电文长度
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stCommInfo.CommLenBit));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stCommInfo.CommLenBit));
	f_iCurLen++;
	//电文内容
	memcpy(pSendBuffer+f_iCurLen,stCommInfo.CommBuff,stCommInfo.CommLenByte);
	f_iCurLen += stCommInfo.CommLenByte;

	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);

	f_iCurLen++;
	return f_iCurLen;
}

DWORD CDataOperate::SendToDS_TXHZ(tagSendBackInfo& stSendBack,DWORD dwSerialID,BYTE* pSendBuffer)
{
	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"TXHZ",4);
	
	DWORD f_iCurLen;
	
	//发送方地址
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stSendBack.dwSendID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stSendBack.dwSendID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stSendBack.dwSendID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stSendBack.dwSendID));
	f_iCurLen++;
	//接收方地址
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(stSendBack.dwRecvID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stSendBack.dwRecvID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stSendBack.dwRecvID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stSendBack.dwRecvID));
	f_iCurLen++;
	//通信流水号
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwSerialID));
	f_iCurLen++; 
	//时间
	pSendBuffer[f_iCurLen] = stSendBack.nHour;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stSendBack.nMinute;
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = stSendBack.nSecond;
	f_iCurLen++;

	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);
	f_iCurLen++;
	
	return f_iCurLen;
}

DWORD CDataOperate::SendToDS_ZJXX(DWORD dwMachineID,BYTE nStatus,BYTE* pSendBuffer)
{
	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"ZJXX",4);

	DWORD f_iCurLen;

	//指挥机ID
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwMachineID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwMachineID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwMachineID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwMachineID));
	f_iCurLen++;
	//指挥机状态
	pSendBuffer[f_iCurLen] = nStatus;
	f_iCurLen++;

	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);

	f_iCurLen++;
	return f_iCurLen;
}

DWORD CDataOperate::SendToDS_FKXX(DWORD dwLocalID,DWORD dwDestID,DWORD dwSerialID,BYTE nFeedResult,BYTE* pSendBuffer)
{
	pSendBuffer[0] = '$';
	memcpy(pSendBuffer+1,"BDFK",4);

	DWORD f_iCurLen;
	//指挥机ID
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwLocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwLocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwLocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwLocalID));
	f_iCurLen++;
	//目的ID
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwDestID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwDestID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwDestID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwDestID));
	f_iCurLen++;
	//通信流水
	pSendBuffer[f_iCurLen] = HIBYTE(HIWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(dwSerialID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(dwSerialID));
	f_iCurLen++;
	//反馈标志
	pSendBuffer[f_iCurLen] = nFeedResult;
	f_iCurLen++;

	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer,f_iCurLen);

	f_iCurLen++;
	return f_iCurLen;
}

BYTE CDataOperate::ExplainData_UDP(BYTE* pSrcBuffer,BYTE* pDestBuffer,DWORD& dwExplainLen)
{
	BYTE nReportID = pSrcBuffer[0];

	DWORD dwIndex = 1;
	DWORD dwTemp = 0;
	BYTE nTemp = 0;

	switch(nReportID)
	{
	case 0: //定位信息
		{
			lpPosInfo f_pPosInfo;
			f_pPosInfo = (lpPosInfo)pDestBuffer;

			//申请定位用户ID
			f_pPosInfo->LocalID = pSrcBuffer[dwIndex]*256*256*256;
			dwIndex++;
			f_pPosInfo->LocalID += pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			f_pPosInfo->LocalID += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			f_pPosInfo->LocalID += pSrcBuffer[dwIndex];
			dwIndex++;
			//是否加密
			f_pPosInfo->ifSecret = pSrcBuffer[dwIndex];
			dwIndex++;
			//定位精度
			f_pPosInfo->Precision = pSrcBuffer[dwIndex];
			dwIndex++;
			//是否紧急定位
			f_pPosInfo->ifUrgent = pSrcBuffer[dwIndex];
			dwIndex++;
			//多值解
			f_pPosInfo->ifMultiValue = pSrcBuffer[dwIndex];
			dwIndex++;

			//密钥
			if(f_pPosInfo->ifSecret)
			{
				memcpy(f_pPosInfo->pSecrets,pSrcBuffer+dwIndex,6);
				dwIndex += 6;
			}

			/* 时间 */
			dwTemp = pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex];
			dwIndex++;
			//时
			f_pPosInfo->Hour = (( dwTemp & 0xF80000 ) >> 19);
			//分
			f_pPosInfo->Minute = ((dwTemp & 0x07E000) >> 13);
			//秒
			f_pPosInfo->Second = ((dwTemp & 0x1F80) >> 7);
			//0.01秒
			f_pPosInfo->CentiSecond = (dwTemp & 0x7F);

			/* 经度 */
			dwTemp = pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex];
			dwIndex++;
			//度
			f_pPosInfo->LongDeg = (( dwTemp & 0xFF0000) >> 16);
			//分
			f_pPosInfo->LongMin = ((dwTemp & 0xFC00) >> 10);
			//秒
			f_pPosInfo->LongSec = ((dwTemp & 0x03F0) >> 4);
			//0.1秒
			f_pPosInfo->LongDecsec = (dwTemp & 0x0F);
			/*纬度*/
			dwTemp = pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex];
			dwIndex++;
			//度
			f_pPosInfo->LatDeg = ((dwTemp & 0xFC0000) >> 18);
			//分
			f_pPosInfo->LatMin = ((dwTemp & 0x03F000) >> 12);
			//秒
			f_pPosInfo->LatSec = ((dwTemp & 0x0FC0) >> 6);
			//0.1秒
			f_pPosInfo->LatDecsec = ((dwTemp & 0x3C) >> 2);
			//大地高符号
			f_pPosInfo->nAltSign= ((dwTemp & 0x02) >> 1);
			f_pPosInfo->Altitude = dwTemp & 0x01;
			f_pPosInfo->Altitude = (f_pPosInfo->Altitude<< 13);
			//高程及异常
			dwTemp = pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			dwTemp += pSrcBuffer[dwIndex];
			dwIndex++;
			//大地高
			f_pPosInfo->Altitude |= ((dwTemp & 0xFFF800) >> 11);
			//高程异常符号
			f_pPosInfo->nEfSign = ((dwTemp & 0x0400) >> 10);
			//高程异常数据
			f_pPosInfo->Ef = ((dwTemp & 0x03FC) >> 2);
			

			dwExplainLen = dwIndex;
		}
		return CUNPACK_DWXX;
	case 3: //通信信息
		{
			lpCommInfo pCommInfo;
			pCommInfo = (lpCommInfo)pDestBuffer;

			//电文形式
			pCommInfo->ifBCD = pSrcBuffer[dwIndex];
			dwIndex++;
			//类别
			pCommInfo->ifUrgent = pSrcBuffer[dwIndex];
			dwIndex++;
			//是否加密
			pCommInfo->ifSecret = pSrcBuffer[dwIndex];
			dwIndex++;
			//发方地址
			pCommInfo->SrcAddress = pSrcBuffer[dwIndex]*256*256*256;
			dwIndex++;
			pCommInfo->SrcAddress += pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			pCommInfo->SrcAddress += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			pCommInfo->SrcAddress += pSrcBuffer[dwIndex];
			dwIndex++;
			//收方地址
			pCommInfo->LocalID = pSrcBuffer[dwIndex]*256*256*256;
			dwIndex++;
			pCommInfo->LocalID += pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			pCommInfo->LocalID += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			pCommInfo->LocalID += pSrcBuffer[dwIndex];
			dwIndex++;
			//时间
			pCommInfo->CommHour = pSrcBuffer[dwIndex];
			dwIndex++;
			pCommInfo->CommMin = pSrcBuffer[dwIndex];
			dwIndex++;
			pCommInfo->CommSecond = pSrcBuffer[dwIndex];
			dwIndex++;
			//电文长度
			pCommInfo->CommLenBit = pSrcBuffer[dwIndex]*256;
			dwIndex++;
			pCommInfo->CommLenBit += pSrcBuffer[dwIndex];
			dwIndex++;
			//密钥
			if(pCommInfo->ifSecret)
				dwIndex += 6;

			//电文类型
			if(pSrcBuffer[dwIndex] == 0xA4)
			{
				pCommInfo->ifBCD = 2;
				pCommInfo->CommLenBit -= 8;
				dwIndex++;
			}

			pCommInfo->CommLenByte = RoundMax(pCommInfo->CommLenBit,8);
			
			memcpy(pCommInfo->CommBuff,pSrcBuffer+dwIndex,pCommInfo->CommLenByte);
			dwIndex += pCommInfo->CommLenByte;

			dwExplainLen = dwIndex;
		}
		return CUNPACK_TXXX;
	case 4: //通信回执
		{
			lpSendBackInfo pSendBack;
			pSendBack = (lpSendBackInfo)pDestBuffer;

			//发方地址
			pSendBack->dwSendID = pSrcBuffer[dwIndex]*256*256*256;
			dwIndex++;
			pSendBack->dwSendID += pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			pSendBack->dwSendID += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			pSendBack->dwSendID += pSrcBuffer[dwIndex];
			dwIndex++;
			//收方地址
			pSendBack->dwRecvID = pSrcBuffer[dwIndex]*256*256*256;
			dwIndex++;
			pSendBack->dwRecvID += pSrcBuffer[dwIndex]*256*256;
			dwIndex++;
			pSendBack->dwRecvID += pSrcBuffer[dwIndex]*256;
			dwIndex++;
			pSendBack->dwRecvID += pSrcBuffer[dwIndex];
			dwIndex++;
			//时
			pSendBack->nHour = pSrcBuffer[dwIndex];
			dwIndex++;
			pSendBack->nMinute = pSrcBuffer[dwIndex];
			dwIndex++;
			pSendBack->nSecond = pSrcBuffer[dwIndex];
			dwIndex++;

			dwExplainLen = dwIndex;
		}
		return CUNPACK_TXHZ;
	}
}

DWORD CDataOperate::SendToBd_ICJC(DWORD dwLocalID,BYTE nFramNo,BYTE* pSendBuffer)
{
	memcpy(pSendBuffer,"$ICJC",5);

	DWORD dwIndex = 7;
	pSendBuffer[dwIndex] = LOBYTE(HIWORD(dwLocalID));
	dwIndex++;
	pSendBuffer[dwIndex] = HIBYTE(LOWORD(dwLocalID));
	dwIndex++;
	pSendBuffer[dwIndex] = LOBYTE(LOWORD(dwLocalID));
	dwIndex++;
	//帧号
	pSendBuffer[dwIndex] = nFramNo;
	dwIndex++;
	//长度
	pSendBuffer[5] = HIBYTE(LOWORD(dwIndex+1));
	pSendBuffer[6] = LOBYTE(LOWORD(dwIndex+1));
	//校验
	pSendBuffer[dwIndex] = ComputeCheckSum(pSendBuffer,dwIndex);
	dwIndex++;
	
	return dwIndex;
}

DWORD CDataOperate::SendToBd_XTZJ(DWORD dwLocalID,WORD nSelfFre,BYTE* pSendBuffer)
{
	memcpy(pSendBuffer,"$XTZJ",5);

	DWORD dwIndex = 7;
	//地址
	pSendBuffer[dwIndex] = LOBYTE(HIWORD(dwLocalID));
	dwIndex++;
	pSendBuffer[dwIndex] = HIBYTE(LOWORD(dwLocalID));
	dwIndex++;
	pSendBuffer[dwIndex] = LOBYTE(LOWORD(dwLocalID));
	dwIndex++;
	//频度 
	pSendBuffer[dwIndex] = HIBYTE(nSelfFre);
	dwIndex++;
	pSendBuffer[dwIndex] = LOBYTE(nSelfFre);
	dwIndex++;

	pSendBuffer[5] = HIBYTE(LOWORD(dwIndex+1));
	pSendBuffer[6] = LOBYTE(LOWORD(dwIndex+1));

	pSendBuffer[dwIndex] = ComputeCheckSum(pSendBuffer,dwIndex);
	dwIndex++;
	return dwIndex;
}

DWORD CDataOperate::SendToBd_TXSQ(tagCommReq& stReq,BYTE* pSendBuffer)
{
	memcpy(pSendBuffer,"$TXSQ",5);
	
	DWORD f_iCurLen;
	DWORD f_dwTemp;

	//本机地址
	f_iCurLen = 7;
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stReq.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stReq.LocalID));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stReq.LocalID));
	f_iCurLen++;
	//报文类别
	pSendBuffer[f_iCurLen] = 0x40;
	pSendBuffer[f_iCurLen] |= stReq.ifSecret?0x10:0x00; //0
	pSendBuffer[f_iCurLen] |= stReq.ifQuick?0x00:0x04;
	pSendBuffer[f_iCurLen] |= stReq.ifBCD?0x02:0x00;
	f_iCurLen++;
	//目的地址
	pSendBuffer[f_iCurLen] = LOBYTE(HIWORD(stReq.DestAddress));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(stReq.DestAddress));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(stReq.DestAddress));
	f_iCurLen++;
	//报文长度
	int nReportLen = stReq.InfoLen;
	if(stReq.ifBCD == 2)
		nReportLen += 8;
	pSendBuffer[f_iCurLen] = HIBYTE(LOWORD(nReportLen));
	f_iCurLen++;
	pSendBuffer[f_iCurLen] = LOBYTE(LOWORD(nReportLen));
	f_iCurLen++;
	//是否应答
	pSendBuffer[f_iCurLen] = 0;
	f_iCurLen++;
	//报文内容
	if(stReq.ifBCD == 2) //混发
	{
		pSendBuffer[f_iCurLen] = 0xA4;
		f_iCurLen++;

		f_dwTemp = RoundMax(nReportLen,8); //加入混发标志
	}
	else
	if(stReq.ifBCD == 1 || stReq.ifBCD == 0)
	{
		f_dwTemp = RoundMax(nReportLen,8);
	}

	
	memcpy(pSendBuffer+f_iCurLen,stReq.InfoBuff,f_dwTemp);
	f_iCurLen += f_dwTemp;

	pSendBuffer[5] = HIBYTE(LOWORD(f_iCurLen+1));//长度高字节
	pSendBuffer[6] = LOBYTE(LOWORD(f_iCurLen+1));//长度低字节
	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer, f_iCurLen);
	f_iCurLen++;
	return f_iCurLen;
}

BYTE CDataOperate::ComputeCheckSum(BYTE * Buff,DWORD Len)
{
	BYTE CheckSum=0;
	for(DWORD i=0;i<Len;i++)
		CheckSum^=Buff[i];
	return CheckSum;
}

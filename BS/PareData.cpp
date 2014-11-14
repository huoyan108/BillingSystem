#include "PareData.h"

CPareData::CPareData()
{
}


CPareData::~CPareData()
{
}
typedef struct tagSInfoTitle
{
	int iInfoID;
	char cTitle[6];
}SInfoTitle;

const int INFOCOUNT_JF = 3;
SInfoTitle InfoTitle_JF[] =
{
	{ CUNPACK_FWJQ, "FWJQ" },
	{ CUNPACK_KFQQ, "KFQQ" },
	{ CUNPACK_JQJG, "JQJG" },
};

char CPareData::ComputeCheckSum(char * Buff, DWORD Len)
{
	char CheckSum = 0;
	for (DWORD i = 0; i<Len; i++)
		CheckSum ^= Buff[i];
	return CheckSum;
}

DWORD RoundMax(DWORD Dividend, DWORD Divisor)
{
	if (Dividend % Divisor != 0)
		return Dividend / Divisor + 1;
	else
		return Dividend / Divisor;
}



/*char CPareData::ExplainData_FWJQ(char* pSrcBuffer, DWORD dwBufferLen, char* pDestBuffer)
{
	char nReportID;
	int i;

	for (i = 0; i<INFOCOUNT_JF; i++)
	{
		if (memcmp(pSrcBuffer + 1, InfoTitle_JF[i].cTitle, 4) == 0)
		{
			nReportID = InfoTitle_JF[i].iInfoID;
			break;
		}
	}

	if (i >= INFOCOUNT_JF)
		return CUNPACK_NULL;

	int  f_iCurLen;
	DWORD  f_dwTemp;//无符号

	switch (nReportID)
	{
	case CUNPACK_FWJQ:
	{
		lpCardInfoRead f_pCardInfoRead;
		f_pCardInfoRead = (lpCardInfoRead)pDestBuffer;

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

		if (f_pCardInfoRead->FrameNum == 0) //判断帧号是否为首帧
		{
			//通波ID		
			f_dwTemp = pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
			f_iCurLen++;
			f_dwTemp += pSrcBuffer[f_iCurLen];
			f_dwTemp *= 256;
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
			f_pCardInfoRead->ServeFreq = (unsigned short)f_dwTemp;
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
			f_pCardInfoRead->SubordinateNum = (unsigned short)f_dwTemp;
			f_iCurLen++;
		}
		else
		{
			//下级用户ID 数目
			f_pCardInfoRead->CurrFrameSubNum = (dwBufferLen - 12) / 3;
			//下级用户地址
			for (i = 0; i < f_pCardInfoRead->CurrFrameSubNum; i++)   //存储下级用户ID
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
		f_pSelfCheckInfo = (lpSelfCheckInfo)pDestBuffer;
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
		for (i = 0; i < 6; i++)
		{
			f_pSelfCheckInfo->PowerState[i] = pSrcBuffer[f_iCurLen];
			f_iCurLen++;
		}
	}
		return CUNPACK_ZJXX;
	case CUNPACK_FKXX:
	{
		lpFeedbackInfo f_pFeedbackInfo;
		f_pFeedbackInfo = (lpFeedbackInfo)pDestBuffer;  //定义结构指针(没有分配具体地址)
		f_iCurLen = 7;

		//本机用户地址
		f_dwTemp = pSrcBuffer[f_iCurLen];
		f_dwTemp *= 256;
		f_iCurLen++;
		f_dwTemp += pSrcBuffer[f_iCurLen];
		f_dwTemp *= 256;
		f_iCurLen++;
		f_dwTemp += pSrcBuffer[f_iCurLen];
		f_pFeedbackInfo->LocalID = f_dwTemp;
		f_iCurLen++;

		//反馈结果
		f_pFeedbackInfo->FeedResult = pSrcBuffer[f_iCurLen];
		f_iCurLen++;
		//保留信息
		f_pFeedbackInfo->Reserve[0] = pSrcBuffer[f_iCurLen];
		f_iCurLen++;
		f_pFeedbackInfo->Reserve[1] = pSrcBuffer[f_iCurLen];
		f_iCurLen++;
		f_pFeedbackInfo->Reserve[2] = pSrcBuffer[f_iCurLen];
		f_iCurLen++;
		f_pFeedbackInfo->Reserve[3] = pSrcBuffer[f_iCurLen];
		f_iCurLen++;
	}
		return CUNPACK_FKXX;
	}
	return CUNPACK_NULL;
}*/
char CPareData::ExplainData_XXKF(char* pSrcBuffer, DWORD dwBufferLen, char* pDestBuffer)
{
}
DWORD CPareData::SendToDS_JQJG(DWORD dwSerialID, char nFeedResult, char* pSendBuffer, DWORD &nBufferlength)
{
	pSendBuffer[0] = '$';
	memcpy(pSendBuffer + 1, "BDFK", 4);

	DWORD f_iCurLen;
	f_iCurLen = 7;

	////指挥机ID
	//sprintf(pSendBuffer + f_iCurLen, "%d", swab32(dwLocalID));
	//f_iCurLen += sizeof(DWORD);
	////目的ID
	//sprintf(pSendBuffer + f_iCurLen, "%d", swab32(dwDestID));
	//f_iCurLen += sizeof(DWORD);
	//通信流水
	sprintf(pSendBuffer + f_iCurLen, "%d", swab32(dwSerialID));
	f_iCurLen += sizeof(DWORD);
	//反馈标志
	pSendBuffer[f_iCurLen] = nFeedResult;
	f_iCurLen++;

	//长度
	//sprintf(pSendBuffer + f_iCurLen, "%d", swab16(f_iCurLen + 1));
	//f_iCurLen += 2;

	pSendBuffer[f_iCurLen] = ComputeCheckSum(pSendBuffer, f_iCurLen);

	f_iCurLen++;

	nBufferlength = f_iCurLen;
	return f_iCurLen;
}



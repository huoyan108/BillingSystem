#pragma once
/*
���� �����
����	20140825
˵��	�������ݡ�
*/
#include "MsgStructInfo.h"
#include <string.h>
#include "CNDef.h"
#include <stdio.h>
#include "./proto/bcTx.pb.h"

class CPareData
{
public:
	CPareData();
	~CPareData();

	char ComputeCheckSum(char * Buff, DWORD Len);
	char ExplainData_FWJQ(char* pSrcBuffer, DWORD dwBufferLen, char* pDestBuffer);
	char ExplainData_XXKF(char* pSrcBuffer, DWORD dwBufferLen, char* pDestBuffer);
	DWORD SendToDS_JQJG(DWORD dwSerialID, char nFeedResult, char* pSendBuffer, DWORD &nBufferlength);

};


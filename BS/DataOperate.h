#pragma once

class CDataOperate
{
public:
	CDataOperate(void);
	~CDataOperate(void);
public:
	BYTE ExplainData_BD(BYTE* pSrcBuffer,DWORD dwBufferLen,BYTE* pDestBuffer);
	BYTE ExplainData_UDP(BYTE* pSrcBuffer,BYTE* pDestBuffer,DWORD& dwExplainLen);
	BYTE ExplainData_TCP(BYTE* pSrcBuffer,DWORD dwBufferLen,BYTE* pDestBuffer);
public:
	DWORD SendToDS_XTJC(DWORD dwIndex,BYTE* pSendBuffer);
	DWORD SendToDS_DWXX(tagPosInfo& stPosInfo,BYTE* pSendBuffer);
	DWORD SendToDS_TXXX(tagCommInfo& stCommInfo,BYTE* pSendBuffer);
	DWORD SendToDS_TXHZ(tagSendBackInfo& stSendBack,DWORD dwSerialID,BYTE* pSendBuffer);
	DWORD SendToDS_ZJXX(DWORD dwMachineID,BYTE nStatus,BYTE* pSendBuffer);
	DWORD SendToDS_FKXX(DWORD dwLocalID,DWORD dwDestID,DWORD dwSerialID,BYTE nFeedResult,BYTE* pSendBuffer);
public:
	DWORD SendToBd_ICJC(DWORD dwLocalID,BYTE nFramNo,BYTE* pSendBuffer);
	DWORD SendToBd_XTZJ(DWORD dwLocalID,WORD nSelfFre,BYTE* pSendBuffer);
	DWORD SendToBd_TXSQ(tagCommReq& stReq,BYTE* pSendBuffer);
protected:
	BYTE ComputeCheckSum(BYTE * Buff,DWORD Len);
public:
	static CDataOperate* GetDataOperatePtr();
protected:
	static CDataOperate* m_pDataOperatePtr;

};

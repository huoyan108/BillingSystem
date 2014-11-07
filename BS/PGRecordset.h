/*
 * brief: 查询返回的结果
 * function list:
 * 
 * author: a staff of CETCNAV
 * date: 2014年5月7日
 */
#ifndef GKRECORDSET_H_H
#define GKRECORDSET_H_H

#include "PGRecordset.h"

struct pg_result; 
typedef struct pg_result PGresult;

class PGRecordset{
public:
	// brief 创建
	void Create(PGresult* pResult);

	// brief 清除Recordset
	void Destroy();

	// brief 得到属性个数
	int GetFieldCount();

	// brief 得到元组的个数
	int GetTupleCount(); 

	// brief 得到指定的值
	char* GetValue(int nTuple, int nField); 
private:
	PGresult* m_pRecordset; 
};

#endif
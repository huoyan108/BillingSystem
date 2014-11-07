#include "PGRecordset.h"
#include "libpq-fe.h"


char* PGRecordset::GetValue( int nTuple, int nField ) { 
	PGresult *pResult=(PGresult*)m_pRecordset;
	return PQgetvalue(pResult, nTuple, nField);
}

void PGRecordset::Destroy() {
	PGresult *pResult=(PGresult*)m_pRecordset;
	PQclear(pResult);
}

int PGRecordset::GetFieldCount() {
	PGresult *pResult=(PGresult*)m_pRecordset;
	
	return PQnfields(pResult);
}

int PGRecordset::GetTupleCount() {
	PGresult *pResult=(PGresult*)m_pRecordset;

	return PQntuples(pResult);
}

void PGRecordset::Create( PGresult* pResult ) { 
	m_pRecordset = pResult;
}

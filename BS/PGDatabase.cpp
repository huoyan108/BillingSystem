#include "libpq-fe.h"
#include "PGDatabase.h" 
#include <assert.h>

int PGDatabase::Connect( const PGConnInfo& dbConnInfo ) {
	m_pConnect= PQsetdbLogin(dbConnInfo.pghost, dbConnInfo.pgport,
		"", "", dbConnInfo.dbName, 
		dbConnInfo.login, dbConnInfo.passwd);
	if (PQstatus(m_pConnect) != CONNECTION_OK) {
		fprintf(stderr, "Connection to database failed: %s",
			PQerrorMessage(m_pConnect));
	    PQfinish(m_pConnect);

		return 1;
	}

	return 0;
}

int PGDatabase::DisConnect() {
	PQfinish(m_pConnect); 
	m_pConnect= NULL;

	return 0;
}

//bool PGDatabase::SendQuery( const char* strQuery){ 
//	int retval = PQsendQuery(m_pConnect, strQuery);
//	if (retval == 0) {
//		fprintf(stderr, "Send Query to database failed: %s",
//			PQerrorMessage(m_pConnect));
//	}
//	return retval != 0;
//}

//PGRecordset* PGDatabase::GetRecordset() { 
//	PGresult* pResult= PQgetResult(m_pConnect);
//
//	PGRecordset *pRecord = NULL;
//	if (pResult != NULL) {
//		pRecord = new PGRecordset;
//		pRecord->Create(pResult);
//	}
//
//	return pRecord;
//}

bool PGDatabase::BeginTransaction() {
	if (m_pConnect == NULL) {
		return false;
	}
	PGresult* res = PQexec(m_pConnect, "begin transaction");
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		fprintf(stderr, "BEGIN command failed: %s\n", PQerrorMessage(m_pConnect));
		PQclear(res);
		
		return false;
	}
	PQclear(res);
	return true;
}

bool PGDatabase::Commit() {
	if (m_pConnect == NULL) {
		return false;
	}
	PGresult* res = PQexec(m_pConnect, "commit"); 
	if(PQresultStatus(res) != PGRES_COMMAND_OK){
		fprintf(stderr, "END command failed: %s\n", PQerrorMessage(m_pConnect));
		PQclear(res);

		return false;
	}
	PQclear(res);

	return true;
}

bool PGDatabase::Exec( const char* strSQL ) {
	if (m_pConnect == NULL) {
		return false;
	}
	assert(m_pConnect != NULL); 
	PGresult* res = PQexec(m_pConnect, strSQL);
	if (PQresultStatus(res) != PGRES_COMMAND_OK ) {
		fprintf(stderr,"%s failed!", strSQL);
		fprintf(stderr, " %s\n", PQerrorMessage(m_pConnect));
		PQclear(res);

		return false;
	} 

	PQclear(res);
	return true;
}

PGRecordset* PGDatabase::Query( const char* strSQL ) {
	if (m_pConnect == NULL) {
		return NULL;
	}
	assert(m_pConnect != NULL);
	PGresult* res = PQexec(m_pConnect, strSQL);

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr,"%s exec failed!\n", strSQL);

		PQclear(res);
		return NULL;
	} 

	PGRecordset* pRecordset = new PGRecordset;
	pRecordset->Create(res);

	return pRecordset;
}

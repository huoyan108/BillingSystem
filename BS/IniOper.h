#pragma once
#include <stdio.h>
#include <unistd.h>
#include <vector>
using namespace std;

#ifdef __cplusplus             //���߱��������ⲿ�ִ��밴C���Եĸ�ʽ���б��룬������C++��

extern "C"{

#endif

	/*��*/
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef __cplusplus

}

#endif


struct COM_DEV_TAG
{
	char Dev[20];
	int nSpeed;
	int nBits;
	char nEvent;
	int nStop;
};
class CIniOper
{
public:
	CIniOper();
	~CIniOper();
	int GetSoftPath(char *cPath, int nSize);
	int load(char *filename, int *nRequestPort, int *nRespondPort,char *pSoftName);
	int load(char *filename, char *dbhost, char * dbport, char * dbname, char * dbuser, char * dbpwd);
	int loadComDev(char *filename, vector<COM_DEV_TAG> &devArr);
	int loadComDev1(char *filename, vector<COM_DEV_TAG> &devArr);

protected:
	// ��ȡ�豸����table������
	int GetDevTableValue(lua_State *L, COM_DEV_TAG &devTag,int tablePos);
public:
	// �����豸��Ϣ
	int SaveComDev(char *filename, COM_DEV_TAG &devTag);
	
	int setDevCom(lua_State *L, COM_DEV_TAG &devTag);
	int SetField(lua_State *L, const char *index, const char *sValue);
	int SetField(lua_State *L, const char *index, const int nValue);
	void error(lua_State *L, const char *fmt, ...);
};


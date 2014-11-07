#pragma once
#include <stdio.h>
#include <unistd.h>
#include <vector>
using namespace std;

#ifdef __cplusplus             //告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的

extern "C"{

#endif

	/*…*/
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
	// 获取设备参数table的内容
	int GetDevTableValue(lua_State *L, COM_DEV_TAG &devTag,int tablePos);
public:
	// 保存设备信息
	int SaveComDev(char *filename, COM_DEV_TAG &devTag);
	
	int setDevCom(lua_State *L, COM_DEV_TAG &devTag);
	int SetField(lua_State *L, const char *index, const char *sValue);
	int SetField(lua_State *L, const char *index, const int nValue);
	void error(lua_State *L, const char *fmt, ...);
};


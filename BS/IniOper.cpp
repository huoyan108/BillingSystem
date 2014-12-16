#include "IniOper.h"

#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;
CIniOper::CIniOper()
{
}


CIniOper::~CIniOper()
{
}
void CIniOper::error(lua_State *L, const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
}

int  CIniOper::loadComDev1(char *filename, vector<COM_DEV_TAG> &devArr)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config.file:%s", lua_tostring(L, -1));
		return -1;
	}

	//串口参数数量
	lua_getglobal(L, "count");
	if (!lua_isnumber(L, -1))
	{
		return -1;
	}
	int nCount = 0;
	nCount = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);


	lua_getglobal(L, "devInfoTable");
	if (!lua_istable(L, -1))
	{
		return -1;
	}

	for (int i = 0; i < nCount; i++)
	{
		lua_pushnumber(L, i + 1); //参数

		lua_gettable(L, -2);  //去table查找

		if (!lua_istable(L, -1))	//结果是不是一个子table
		{
			return -1;
		}
		//获取子table内容
		COM_DEV_TAG devTag;
		if (GetDevTableValue(L, devTag, 1) != 0)
		{
			return -1;
		}
		devArr.insert(devArr.begin(), devTag);
		lua_pop(L, 1);	//干掉子table
	}
	lua_pop(L, 1);	//干掉table

	lua_close(L);
	return 0;
}

int  CIniOper::loadComDev(char *filename, vector<COM_DEV_TAG> &devArr)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config.file:%s", lua_tostring(L, -1));
		return -1;
	}
	
	//串口参数数量
	lua_getglobal(L, "count");
	if (!lua_isnumber(L, -1))
	{
		return -1;
	}
	int nCount = 0;
	nCount = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);


	lua_getglobal(L, "devs");
	if (!lua_istable(L, -1))
	{
		return -1;
	}

	//lua_pushnumber(L,1);
	//lua_gettable(L, -2);

	//if (!lua_isstring(L, -1))
	//{
	//	return -1;
	//}
	//COM_DEV_TAG devTag;

	//sprintf(devTag.Dev, "%s", (char *)lua_tostring(L, -1));
	//获取子table
	for (int i = 0; i < nCount; i++)
	{
		lua_pushnumber(L, i + 1); //参数

		lua_gettable(L, -2);  //去table查找

		if (!lua_istable(L, -1))	//结果是不是一个子table
		{
			return -1;
		}
		//获取子table内容
		COM_DEV_TAG devTag;
		if (GetDevTableValue(L, devTag, 1) != 0)
		{
			return -1;
		}
		devArr.insert(devArr.begin(), devTag);
		lua_pop(L, 1);	//干掉子table
	}
	lua_pop(L, 1);	//干掉table

	lua_close(L);
	return 0;
}

// 获取设备参数table的内容
int CIniOper::GetDevTableValue(lua_State *L, COM_DEV_TAG &devTag, int tablePos)
{
	//dev
	lua_pushstring(L, "dev"); //参数
	lua_gettable(L, -2);  //去table查找
	if (!lua_isstring(L, -1))
	{
		return -1;
	}
	sprintf(devTag.Dev, "%s", (char *)lua_tostring(L, -1));
	lua_pop(L, 1);

	lua_pushstring(L, "speed"); //参数
	lua_gettable(L, -2);  //去table查找
	if (!lua_isnumber(L, -1))
	{
		return -1;
	}
	devTag.nSpeed = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "bits"); //参数
	lua_gettable(L, -2);  //去table查找
	if (!lua_isnumber(L, -1))
	{
		return -1;
	}
	devTag.nBits = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "event"); //参数
	lua_gettable(L, -2);  //去table查找
	if (!lua_isstring(L, -1))
	{
		return -1;
	}
	sprintf(&devTag.nEvent, "%s", (char *)lua_tostring(L, -1));
	//devTag.nEvent = (char)lua_tostring(L, -1));
	lua_pop(L, 1);

	lua_pushstring(L, "stop"); //参数
	lua_gettable(L, -2);  //去table查找
	if (!lua_isnumber(L, -1))
	{
		return -1;
	}
	devTag.nStop = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return 0;
}
int  CIniOper::loadCost(char *filename, float *fSingleCost)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		//error(L, "cannot run configuration file: %s",
		//lua_tostring(L, -1));
		return -1;
	}

	lua_getglobal(L, "singlecost");

	if (!lua_isnumber(L, -1))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;
	}

	*fSingleCost = (float)lua_tonumber(L, -1);

	lua_pop(L, 1);

	lua_close(L);
	return 0;
}

int  CIniOper::load(char *filename, int *nRequestPort, int *nRespondPort, char *pSoftName)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		//error(L, "cannot run configuration file: %s",
		//lua_tostring(L, -1));
		return -1;
	}


	lua_getglobal(L, "RequestPort");
	lua_getglobal(L, "RespondPort");
	lua_getglobal(L, "softname");

	if (!lua_isnumber(L, -3))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isnumber(L, -2))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isstring(L, -1))
	{
		//error(L, "`RespondPort' should be a number\n");
		return -1;
	}

	*nRequestPort = (int)lua_tonumber(L, -3);
	*nRespondPort = (int)lua_tonumber(L, -2);
	sprintf(pSoftName, "%s", (char *)lua_tostring(L, -1));
	lua_pop(L, 3);

	lua_close(L);
	return 0;
}

int  CIniOper::load(char *filename, char *dbhost, char * dbport, char * dbname, char * dbuser, char * dbpwd)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		//error(L, "cannot run configuration file: %s",
		//lua_tostring(L, -1));
		return -1;
	}


	lua_getglobal(L, "pghost");
	lua_getglobal(L, "pgport");
	lua_getglobal(L, "dbName");
	lua_getglobal(L, "login");
	lua_getglobal(L, "passwd");

	if (!lua_isstring(L, -5))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isstring(L, -4))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isstring(L, -3))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isstring(L, -2))
	{
		//error(L, "`RequestPort' should be a number\n");
		return -1;

	}
	if (!lua_isstring(L, -1))
	{
		//error(L, "`RespondPort' should be a number\n");
		return -1;
	}
	sprintf(dbpwd, "%s", (char *)lua_tostring(L, -1));
	sprintf(dbuser, "%s", (char *)lua_tostring(L, -2));
	sprintf(dbname, "%s", (char *)lua_tostring(L, -3));
	sprintf(dbport, "%s", (char *)lua_tostring(L, -4));
	sprintf(dbhost, "%s", (char *)lua_tostring(L, -5));

	lua_pop(L, 5);

	lua_close(L);
	return 0;
}

int CIniOper::GetSoftPath(char *cPath,int nSize)
{
	int n;

	n = readlink("/proc/self/exe", cPath, nSize);
	if (n < 0 && n > nSize)
	{
		printf("get software path error ,no file or pathlength is too long");
		return -1;
	}

	int i;
	for (i = n; i >= 0; --i)
	{
		if (cPath[i] == '/')
		{
			cPath[i + 1] = '\0';
			printf("software path:%s\n", cPath);
			return 0;
		}
	}
	return -1;
}


// 保存设备信息
int CIniOper::SaveComDev(char *filename, COM_DEV_TAG &devTag)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
	{
		return -1;
	}
	lua_getglobal(L, "data");
	if (!lua_istable(L, -1))
	{
		return -1;
	}
	SetField(L,"dev", devTag.Dev);
	SetField(L, "speed", devTag.nSpeed);

	SetField(L, "bits", devTag.nBits);

	SetField(L, "event", devTag.nEvent);

	SetField(L, "stop", devTag.nStop);

	lua_setglobal(L, "data");
	lua_getglobal(L, "writeDevconfig");
	 if (lua_pcall(L, 0, 0, 0) != 0)
		{
			error(L, "error running function 'writedevconf':%s",
				lua_tostring(L, -1));
		}
	
	lua_close(L);

	return 0;
}

int CIniOper::SetField(lua_State *L, const char *index, const char *sValue)
{
	lua_pushstring(L, index);
	lua_pushstring(L, sValue);
	lua_settable(L, -3);

	return 0;

}
int CIniOper::SetField(lua_State *L, const char *index, const int nValue)
{
	lua_pushstring(L, index);
	lua_pushnumber(L, nValue);
	lua_settable(L, -3);
	return 0;
}


//int main(int argc, char **argv)
//{
//	CIniOper ini;
//	char cPath[1000];
//
//
//	//bzero(cPath, sizeof(cPath));
//
//	//if (ini.GetSoftPath(cPath, sizeof(cPath)) != 0)
//	//{
//
//	//}
//	//strcat(cPath, "readDevConf.lua");
//	//vector<COM_DEV_TAG> devArr;
//
//	//ini.loadComDev1(cPath, devArr);
//
//	bzero(cPath, sizeof(cPath));
//	if (ini.GetSoftPath(cPath, sizeof(cPath)) != 0)
//	{
//
//	}
//	strcat(cPath, "writeDevConf.lua");
//	COM_DEV_TAG a;
//	for (int i = 0; i < 3; i++)
//	{
//		ini.SaveComDev(cPath,a);
//
//	}
//
//	//strcat(cPath, "test.lua");
//	//lua_State *L = luaL_newstate();
//	//luaL_openlibs(L);
//
//	//if (luaL_loadfile(L, cPath) || lua_pcall(L, 0, 0, 0))
//	//{
//	//	//error(L, "cannot run config.file:%s", lua_tostring(L, -1));
//	//	return -1;
//	//}
//
//	////串口参数数量
//	//lua_getglobal(L, "count");
//	//if (!lua_isnumber(L, -1))
//	//{
//	//	return -1;
//	//}
//	//int nCount = 0;
//	//nCount = (int)lua_tonumber(L, -1);
//	//lua_pop(L, 1);
//
//
//	/*lua_getglobal(L, "devs");
//	if (!lua_istable(L, -1))
//	{
//		return -1;
//	}
//
//	lua_pushnumber(L,1);
//	lua_gettable(L, -2);
//
//	if (!lua_isstring(L, -1))
//	{
//		return -1;
//	}
//	COM_DEV_TAG devTag;
//
//	sprintf(devTag.Dev, "%s", (char *)lua_tostring(L, -1));*/
//	
//	//server={ip=192.168.1.1,port=1111}
//	/*lua_getglobal(L, "devs");
//	if (!lua_istable(L, -1))
//	{
//		return -1;
//	}
//	lua_pushnumber(L, 1);
//	lua_gettable(L, -2);
//
//	if (!lua_isstring(L, -1))
//	{
//		return -1;
//	}
//	lua_pushstring(L, "192.168.1.111");
//	lua_setfield(L, -3, "1");
//
//	lua_close(L);*/
//	//ini.SaveComDev(cPath, devTag);
//	return 1;
//}

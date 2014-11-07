#ifndef TOOLS_H
#define TOOLS_H 
#include <string>
#include <iostream>
#include <vector>

#include <string.h>


using namespace std;


string itostr(int i);

vector<string> Split(const string s,string token);

string Replace(string& s,const string& token,const string& t);

/*
 *	Apr 15 2009 04:04:17:000PM
 *  获取数据库支持的当前时间
 */
string getDBDateTimeString();


string getDateTimeStringStand(time_t t);


string getFormatDateTimeString(string & format, time_t t);

string getNowDateTimeStringSQLServer();

#endif

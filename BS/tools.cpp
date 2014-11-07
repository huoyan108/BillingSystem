#include "tools.h"
#include <cctype>
#include <stdio.h>


vector<string> Split(const string s,string token)
{
        vector<string> strvec;
		if(s.empty() || token.empty())
			return strvec;

        string::size_type pos1, pos2;
        pos2 = s.find(token);
        pos1 = 0;        
		int tokenlen = token.length();
        while (string::npos != pos2)
        {
                strvec.push_back(s.substr(pos1, pos2 - pos1));
                
                pos1 = pos2 + tokenlen;
                pos2 = s.find(token, pos1);
        }
        strvec.push_back(s.substr(pos1));
		return strvec;
}


string Replace(string& s,const string& token,const string& t)
{
		if(s.empty() || token.empty())
			return s;
        string::size_type pos1, pos2;

		int tokenlen = token.length();
        int tlen = t.length();

        pos1 = 0;
        pos2 = s.find(token);

        while (string::npos != pos2)
        {
			 s.replace(pos2,tokenlen,t);
             
             pos1 = pos2 + tlen;
             pos2 = s.find(token, pos1);
        }
		return s;
}



string itostr(int i)
{
	string dest;
	char buf[32] = {0};
	sprintf(buf,"%d",i);
	dest += buf;
	return dest;
}



/*
 *	Apr 15 2009 04:04:17:000PM
 *  获取数据库支持的当前时间
 */
string getDBDateTimeString()
{

	time_t t;
	char timestr[200]={0};

    time(&t);
    struct tm *tms = localtime(&t);
	strftime(timestr,200, "%b %d %Y %H:%M:%S:000%p", tms);
    string dts(timestr);
    //Apr 23 2009  13:04:59:000PM 
	return dts; 
}

//2009-03-13/09:13:50
string getDateTimeStringStand(time_t t)
{
	char timestr[200]={0};
    struct tm *tms = localtime(&t);

	strftime(timestr,200, "%Y-%m-%d %H:%M:%S", tms);
    string dts(timestr);
    //Apr 23 2009  13:04:59:000PM 
	return dts;
}

//2009-11-12 11:35:08
string getNowDateTimeStringSQLServer()
{
	time_t t;
	char timestr[200]={0};
	
    time(&t);
    struct tm *tms = localtime(&t);
	
	strftime(timestr,200, "%Y-%m-%d %H:%M:%S", tms);
    string dts(timestr);
	return dts;
}

string getFormatDateTimeString(string & format, time_t t)
{
	char timestr[200]={0};
    struct tm *tms = localtime(&t);

	strftime(timestr,200, format.c_str() , tms);
    string dts(timestr);
    //Apr 23 2009  13:04:59:000PM 
	return dts;
}

/*
int main()
{
        string test ;
		string token ;
        vector<string> strvec = Split(test,token);

        vector<string>::iterator iter1 = strvec.begin(), iter2 = strvec.end();
        while (iter1 != iter2)
        {
                cout << *iter1 << endl;
                ++iter1;
        } 
        
        return 0;
}
*/

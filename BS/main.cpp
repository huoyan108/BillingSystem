//ZMQ通信
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "debuginfo.cpp"
#include "IniOper.h"
#include <vector>
using namespace std;
#include "DataBusiness.h"
#ifdef __cplusplus             //告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的

extern "C"{

#endif

	/*…*/

#ifdef __cplusplus

}

#endif

#define ADDDEV "AddDev"
#define DELDEV "DelDev"
#define MODIFDEV "ModifDev"

#define SERVER_VERSION_STR "1.00.0000"

int g_daemon_off = 0;
int g_refork_off = 0;
int DEBUG_LEVEL = 2;


static void version() {
	fprintf(stdout, "%s\n", SERVER_VERSION_STR);
}

static void usage() {
	fprintf(stdout, "BDSMS server %s, build on %s %s, usage:\n",
		SERVER_VERSION_STR, __DATE__, __TIME__);
	fprintf(stdout, "BDSMS configfile path[options]\n");
	fprintf(stdout, "-v show version\n");
	fprintf(stdout, "-h help\n");
	//fprintf(stdout, "-d daemon off, do not go to back ground.\n");
	fprintf(stdout, "-r supervisor off, do not re-fork working process.\n");
	fprintf(stdout, "\n");
}

int main(int argc, char **argv)
{
	int i = 1;
	while (i < argc) {
		if (strcmp("-v", argv[i]) == 0) {
			i++;
			version();
			exit(-1);
		}
		else if (strcmp("-h", argv[i]) == 0) {
			i++;
			usage();
			exit(-1);
		}
		else if (strcmp("-D", argv[i]) == 0) {
			i++;
			DEBUG_LEVEL = atoi(argv[i]);
			i++;
		}
		/*else if (strcmp("-d", argv[i]) == 0) {
			i++;
			g_daemon_off = 1;
		}*/
		else if (strcmp("-r", argv[i]) == 0) {
			i++;
			g_refork_off = 1;
		}
		else {
			/* unknown option, bypass. */
			i++;
		}
	}


	//意外中止重启
	if (g_refork_off != 1)
	{
		int fv;
		int status;
		while (true)
		{
			//生成子进程
			for (;;) 
			{
				DEBUG_INFO(DEBUG_2, "Supervisor process %d is starting", getpid());
				fv = fork();
				if (fv < 0) {
					sleep(60);
				}
				else {
					break;
				}
			}
			//end 生成子进程
			//判断终止情况
			if (fv > 0)
			{ 
				for (;;) {
					fv = wait(&status);
					if (WIFEXITED(status)) 
					{
						DEBUG_INFO(DEBUG_2, "Worker process %d is exited normally with code %d", fv, status);
						/* child terminated normally, supervisor exit. */
						exit(0);
					}
					sleep(0);
					if (fv > 0) {
						DEBUG_INFO(DEBUG_2, "Worker process %d is exited abnormally with code %d, supervisor will be restarted it auto", fv, status);
						break;
					}
				}
			}
			else {
				break;
			}
			//end
		}

	}
	CDataBusiness business;

	signal(SIGCHLD, SIG_IGN); /* ignore child */
	signal(SIGTSTP, SIG_IGN); /* ignore tty signals */
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	//signal(SIGHUP, handle_signal);
	//signal(SIGTERM, handle_signal);

	while (true)
	{
		sleep(100000);

	}

	return 1;
}

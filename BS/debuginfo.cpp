#ifndef CDATA_H
#define CDATA_H 

#include <stdio.h>
#include <stdarg.h>
#include "tools.h"

extern int DEBUG_LEVEL;

#define DEBUG_0		0	//not important, do not need show it		info
#define DEBUG_1		1	//not important, sometime have to show it	info
#define DEBUG_2		2	//normal									info
#define DEBUG_3		3	//important!								warning
#define DEBUG_4		4	//very important!							error

//#define	DEBUG_OFF
#ifdef DEBUG_OFF
#define DEBUG_INFO 
#define DEBUG_DUMP
#else
#define DEBUG_INFO debug_info
#define DEBUG_DUMP debug_dump_hex
#endif

inline void debug_info(int _debug_level, const char *format, ...)
{
	if (_debug_level >= DEBUG_LEVEL)
	{
		if( _debug_level == DEBUG_3 )
			printf("[WARN] (%s) ", getDateTimeStringStand(time(0)).c_str());
		else if ( _debug_level == DEBUG_4 )
			printf("[ERRO] (%s) ", getDateTimeStringStand(time(0)).c_str());
		else
			printf("[INFO] (%s) ", getDateTimeStringStand(time(0)).c_str());
		
		va_list argptr;
		va_start(argptr, format);
		vprintf (format, argptr);
		va_end  (argptr);
		printf("\n");
	}
}

inline void debug_dump_hex(const void* dumpdata, int dumplen)
{
	int offset, i, j, k;
	FILE *fptmp = stdout;
	unsigned char *ucptr = (unsigned char*)dumpdata;

	if (DEBUG_LEVEL > 2)
		return;
	/*{
		char buff[24];
		time_t now = time(NULL);
		strftime(buff, 20, "%Y-%m-%d %H:%M:%S\n", localtime(&now));
		fprintf(fptmp, buff);
	}*/
	fprintf(fptmp, "OFFSET       -0--1--2--3--4--5--6--7-*-8--9--a--b--c--d--e--f- DISPLAY\n");
    offset = i = 0;
    
    while (i < dumplen)
    {
        fprintf(fptmp, "%05x(%05d) ", offset, offset);
        for (j = 0; (j < 16) && (i < dumplen); j++, i++)
        {
            if (j < 7)
            {
                fprintf(fptmp, "%02x ", *(ucptr + i));
            }
            else if (j == 7)
            {
                fprintf(fptmp, "%02x -", *(ucptr + i));
            }
            else
            {
                fprintf(fptmp, " %02x", *(ucptr + i));
            }
        }
        
        for (k = j; k < 16; k++)
        {
            fprintf(fptmp, "   ");
        }
        
        if (j < 8)
        {
            fprintf(fptmp, " ");
        }
        
        fprintf(fptmp, " ");
		
        for (k = 0; k < j; k++)
        {
            if (isprint(*(ucptr + i - j + k)))
            {
                fprintf(fptmp, "%c", *(ucptr + i - j + k));
            }
            else
            {
                fprintf(fptmp, ".");
            }
        }
        
        fprintf(fptmp, "\n");
		
        offset += 16;
    }
    
    fprintf(fptmp, "\n");
}
#endif


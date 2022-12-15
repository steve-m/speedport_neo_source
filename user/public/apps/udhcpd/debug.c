#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "debug.h"

void _sc_debug(int debug_type, const char *format, ...)
{
    char buf[4096] = "";
    va_list arg;
    int fd, len;

#ifdef __SC_DEBUG__    
    if ((debug_type & __SC_DEBUG__) == 0)
#endif
        return;

    va_start(arg, format);
    len = vsnprintf(buf, 4096, format, arg);
    va_end(arg);

	if((fd = open("/dev/console", O_WRONLY)) >= 0)
	{
	    write(fd, buf, len);
	    close(fd);
	}

    usleep(1);
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include "scutil.h"

int util_lock_reg(int fd, short type, int retry_time)
{
    struct flock ret;
    ret.l_type = type;
    ret.l_start = 0;
    ret.l_whence = SEEK_SET;
    ret.l_len = 0;
    ret.l_pid = getpid();
    int times = 0;

again:
    times++;
    if (times <= LOCK_RETRY_COUNT)
    {
        if (fcntl(fd, F_SETLK, &ret) < 0)
        {
            usleep(retry_time);
            goto again;
        }
    }
    if (times == LOCK_RETRY_COUNT + 1)
        return -1;
    else
        return 0;
}

int util_lock(char *file, int retry_time)
{
    int times = 0;
    int fd = -1;
    struct flock flockptr = {.l_type = F_WRLCK,
                             .l_start = 0, 
                             .l_whence = SEEK_SET,
                             .l_len = 0   
    };
                           
    if ((fd = open(file, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0)
        return -1;
add_wlock:
    if(0 != retry_time && ++times > retry_time)
    {
        close(fd);
        return -1;
    }
    if (fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        if(errno == EINTR)
	{
            goto add_wlock;
	}
        else
        {
	   close(fd);
           return -1; 
	}
    }
    return fd;

}
void util_unlock(int fd)
{
   
   struct flock flockptr = {.l_type = F_UNLCK,
                             .l_start = 0, 
                             .l_whence = SEEK_SET,
                             .l_len = 0   
    };
    if(fd >= 0)
    {
        fcntl(fd, F_SETLK, &flockptr);    
	close(fd);
    }
}

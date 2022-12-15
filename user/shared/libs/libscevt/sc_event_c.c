#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include "sc_event.h"


int sc_event(struct sc_event_msg *sc_evt_msg, int len)
{
    int ret = -1;
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(fd != -1) {
        struct sockaddr_un cmd_addr;
        bzero(&cmd_addr, sizeof(cmd_addr));
        cmd_addr.sun_family = AF_UNIX;
        strcpy(cmd_addr.sun_path, SC_EVENT_PATH);

        ret = sendto(fd, sc_evt_msg, len, 0, (struct sockaddr *)&cmd_addr, sizeof(cmd_addr));
        close(fd);
    }

    return ret;

}

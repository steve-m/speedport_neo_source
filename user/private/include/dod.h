#ifndef DOD_H
#define DOD_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DOD_READY_FILE "/var/run/dod_ready"

static inline int dod_is_ready(void)
{
    return access(DOD_READY_FILE, F_OK) == 0;
}

static inline int set_dod_ready(void)
{
    int fd = open(DOD_READY_FILE, O_CREAT | O_EXCL | O_RDONLY, 0644);
    if(fd != -1)
        close(fd);

    return 0;
}

static inline int set_dod_unready(void)
{
    return unlink(DOD_READY_FILE);
}

static inline int dod_up(void)
{
    if(dod_is_ready()) {
        set_dod_unready();
        system("/usr/bin/killall -SIGUSR1 cpm_1"); /* FIXME: may need to check which one is PPP DoD */
    }

    return 0;
}

#endif

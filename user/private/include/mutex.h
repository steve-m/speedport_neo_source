#ifndef __SC_SEM_H_
#define __SC_SEM_H_
#include <sys/types.h>
#include <sys/sem.h>
enum{
	CREATE_UNLOCKED,
	CREATE_LOCKED
};
enum{
	NO_WAIT,
	WAIT_FOREVER
};
int scSemCreat(key_t keyid, int full);
int scSemGet(key_t keyid);
int scSemDelete(int semid);
int scSemValid(int semid);
int scSemLock(int semid, int type);
int scSemUnlock(int semid);
#endif

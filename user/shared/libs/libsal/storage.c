#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include "sal_storage.h"

int sal_sync_set_status(sync_status_t status_info,char *fileName)
{
	sync_status_t status_tmp;
	FILE* fp = NULL;
	size_t count = 1024;
	time_t t;
	struct tm *tm;
	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		memset(&status_tmp, 0, sizeof(status_tmp));
		count = fread(&status_tmp, sizeof(status_tmp), 1, fp);
		if(count != 0)
        {
            int status = 0, last_status = 0;
            if(strcmp(status_tmp.sync_status, "started") == 0)
                last_status = 0;
            else
                last_status = 1;
            if(strcmp(status_info.sync_status, "started") == 0)
                status = 0;
            else
                status = 1;

			if(last_status == status)
				strcpy(status_info.sync_laststatus, status_tmp.sync_laststatus);
			else
				strcpy(status_info.sync_laststatus, status_tmp.sync_status);
        }
		fclose(fp);
	}

	fp = fopen(fileName, "w+");
	if (fp == NULL)
        return 0;

    time(&t);
    tm = localtime(&t);
    sprintf(status_info.sync_timestamp, "%d-%02d-%02d %02d:%02d:%02d",
	    			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec); 

    if(!strcmp(status_info.sync_status, "failure") && strlen(status_info.sync_reason) == 0) 
        strcpy(status_info.sync_reason, "nas_state_job_failure"); 
    fwrite(&status_info, sizeof(status_info), 1, fp);
    fclose(fp);
    return 1;
}

sync_status_t sal_sync_get_status(char *fileName)
{
	sync_status_t status_info;
	memset(&status_info, 0, sizeof(status_info));
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
        return status_info;
    fread(&status_info, sizeof(status_info), 1, fp);
    fclose(fp);
    return status_info;
}

int sal_backup_set_status(backup_status_t status_info,char *fileName)
{
	backup_status_t status_tmp;
	FILE* fp = NULL;
	size_t count = 1024;
	time_t t;
	struct tm *tm;
	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		memset(&status_tmp, 0, sizeof(status_tmp));
		count = fread(&status_tmp, sizeof(status_tmp), 1, fp);
		if(count != 0)
        {
            int status = 0, last_status = 0;
            if(strcmp(status_tmp.backup_status, "started") == 0)
                last_status = 0;
            else
                last_status = 1;
            if(strcmp(status_info.backup_status, "started") == 0)
                status = 0;
            else
                status = 1;

			if(last_status == status)
				strcpy(status_info.backup_laststatus, status_tmp.backup_laststatus);
			else
				strcpy(status_info.backup_laststatus, status_tmp.backup_status);
        }
		fclose(fp);
	}
	fp = fopen(fileName, "w+");
	if (fp == NULL)
        return 0;

    time(&t);
    tm = localtime(&t);
    sprintf(status_info.backup_timestamp, "%d-%02d-%02d %02d:%02d:%02d",
	    			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec); 

    if(!strcmp(status_info.backup_status, "failure") && strlen(status_info.backup_reason) == 0) 
	strcpy(status_info.backup_reason, "nas_state_job_failure"); 
    fwrite(&status_info, sizeof(status_info), 1, fp);
    fclose(fp);
    return 1;
}

backup_status_t sal_backup_get_status(char *fileName)
{
	backup_status_t status_info;
	memset(&status_info, 0, sizeof(status_info));
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
        return status_info;
    fread(&status_info, sizeof(status_info), 1, fp);
    fclose(fp);
    return status_info;
}

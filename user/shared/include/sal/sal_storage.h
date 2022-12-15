#ifndef _SAL_STORAGE_
#define _SAL_STORAGE_

typedef struct  
{
	char id[8];
	char sync_status[32];
	char sync_laststatus[32]; 
	char sync_timestamp[32]; 
	char sync_reason[32]; 
}sync_status_t;

typedef struct  
{
	char id[8];
	char backup_status[32];
	char backup_laststatus[32]; 
	char backup_timestamp[32]; 
	char backup_reason[32]; 
}backup_status_t;

sync_status_t sal_sync_get_status(char *fileName);
int sal_sync_set_status(sync_status_t status_info,char *fileName);

backup_status_t sal_backup_get_status(char *fileName);
int sal_backup_set_status(backup_status_t status_info, char *fineName);
#endif

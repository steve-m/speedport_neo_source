#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <ctype.h>

#define HU_END_SYMBOL	        0x00
#define HU_TMP_PATH "/tmp/http_users"

extern int readFileBin(char *path, char **pBuf);
extern void writeFileBin(char *path, char *data, int len);

char* hu_get_fun(const char *name,char *path)
{
	char *bufspace;
	int size;
	char *s,*sp;

	if((size=readFileBin(path, &bufspace))<0)
		return NULL;

	for (s = bufspace; *s; s++) {
		if (!strncmp(s, name, strlen(name)) && *(s+strlen(name))=='=') {
			sp=malloc(strlen(s)-strlen(name));
			memcpy(sp,(s+strlen(name)+1),(strlen(s)-strlen(name)));
			free(bufspace);
			return sp;
		}
		while(*(++s));
	}
	free(bufspace);
	return NULL;
}

char* hu_get(const char *name)
{
	char *pt;
	
	if((pt=hu_get_fun(name,HU_TMP_PATH))==NULL){
		pt=malloc(1);
		*pt = '\0';
	}
	return pt;
}

void hu_set(const char* name,const char* value)
{
	char *bufspace, *targetspace;
	int size;
	char *sp, *s;
	int found=0;

	if((size=readFileBin(HU_TMP_PATH, &bufspace))>0) {
	    targetspace=malloc(size+strlen(name)+strlen(value)+2);
	}
	else {
	    targetspace=malloc(strlen(name)+strlen(value)+2);
	}

	sp=targetspace;
	if(size > 0) {
	   for (s = bufspace; *s; s++) {
		if (!strncmp(s, name, strlen(name)) && *(s+strlen(name))=='=') {
			found=1;
  			strcpy(sp, name);
			sp+=strlen(name);
        		*(sp++) = '=';
       			strcpy(sp, value);
			sp+=strlen(value);
			while (*(++s));
		}
		while(*s) *(sp++)=*(s++);
	        *(sp++)=HU_END_SYMBOL;
	    }

		free(bufspace);
	}
	if(!found){
		strcpy(sp, name);
		sp+=strlen(name);
        	*(sp++) = '=';
	        strcpy(sp, value);
		sp+=strlen(value);
	        *(sp++) = HU_END_SYMBOL;
	}

	*(sp) = HU_END_SYMBOL;

	writeFileBin(HU_TMP_PATH, targetspace, (sp-targetspace)+1);
	free(targetspace);
}

void hu_flush(void)
{
	writeFileBin(HU_TMP_PATH, "", 0);
}

void hu_show(void)
{
	char *bufspace;
	int size;
	char *s,*pt;
	
	if((size=readFileBin(HU_TMP_PATH, &bufspace))<0) {
	    printf("can't find %s!!\n", HU_TMP_PATH);
	    exit(1);
	}
	
	if(size > 0) {
	   for (s = bufspace; *s; s++) {
	   	for(pt=strchr(s,0x01);pt;pt=strchr(pt+1,0x01)) *pt=0x20;
		printf("%s\n",s);
		while(*(++s));
	   }
	
		free(bufspace);
	}
}

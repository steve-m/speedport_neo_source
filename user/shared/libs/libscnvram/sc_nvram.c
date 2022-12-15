#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <sys/file.h>
#include "sc_nvram.h"
#include <linux/compiler.h>
#include "mtd/mtd-user.h"

#define RETRY_TIMES 3

/*martin_huang@sdc.sercomm.com:lock for nvram commit sequence access*/
#define NVRAM_OP_LOCK 	"/tmp/nvram.lock"

static int nvram_lock(void)
{
    int times = 0;
    int fd = -1;
    struct flock flockptr = {.l_type = F_WRLCK,
                             .l_start = 0, 
                             .l_whence = SEEK_SET,
                             .l_len = 0   
    };
                           
    if ((fd = open(NVRAM_OP_LOCK, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0)
        return -1;
add_wlock:
    if(++times > RETRY_TIMES )
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
static void nvram_unlock(int fd)
{
   
   struct flock flockptr = {.l_type = F_UNLCK,
                             .l_start = 0, 
                             .l_whence = SEEK_SET,
                             .l_len = 0   
    };
    if(fd >= 0)
    {
        fcntl(fd, F_SETLKW, &flockptr);    
	close(fd);
    }
}
static ssize_t safe_read(int fd, void *buf, size_t count)
{
	ssize_t n;

	do {
		n = read(fd, buf, count);
	} while (n < 0 && errno == EINTR);

	return n;
}

static ssize_t full_read(int fd, void *buf, size_t len)
{
	ssize_t cc;
	ssize_t total;

	total = 0;

	while (len) {
		cc = safe_read(fd, buf, len);

		if (cc < 0)
			return cc;	/* read() returns -1 on failure. */

		if (cc == 0)
			break;

		buf = ((char *)buf) + cc;
		total += cc;
		len -= cc;
	}

	return total;
}
static ssize_t safe_write(int fd, const void *buf, size_t count)
{
	ssize_t n;

	do {
    		lseek(fd, 0, SEEK_SET);
		n = write(fd, buf, count);
	} while (n < 0 && errno == EINTR);

	return n;
}
int readFileBin(char *path, char **data)
{
    int total;
    int fd = -1;
    int times = 0;
    struct flock flockptr = {.l_type = F_RDLCK,
                             .l_start = 0,
                             .l_whence = SEEK_SET,
                             .l_len = 0
    };

    *data = NULL;

    if ((fd = open(path, O_RDONLY)) < 0) {
        //perror("readFileBin:");
        return -1;
    }
add_rlock:
    if(++times > RETRY_TIMES )
    {
         close(fd);
         return -1;
    }
    if (fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        perror("fcntl:");
        if(errno == EINTR)
            goto add_rlock;
    }

    total = lseek(fd, 0, SEEK_END);

    /**
     * read zero is meaningful
     * Denny Zhang 2011年 06月 07日 星期二 11:40:05 CST
     */

    //if(total <= 0)
    if(total < 0)
    {
        flockptr.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW,&flockptr);
        close(fd);
        return -1;
    }
	
    lseek(fd, 0, 0);
    
    if ((*data = malloc(total)) == NULL) {
        flockptr.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW,&flockptr);
        perror("malloc:");
        close(fd);
        return -1;
    }

    if (full_read(fd, *data, total) != total) { 
        free(*data);
        *data = NULL;
        flockptr.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW,&flockptr);
        perror("read:");
        close(fd);
        return -1;
    }

    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &flockptr);    
    close(fd);
    
    return total;
}

void writeFileBin(char *path, char *data, int len)
{
    int fd;
    int ret = -1;
    int times = 0;
    struct flock flockptr = {.l_type = F_WRLCK,
                             .l_start = 0, 
                             .l_whence = SEEK_SET,
                             .l_len = 0   
    };
                           
    if ((fd = open(path, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0)
        return;

add_wlock:
    if(++times > RETRY_TIMES )
    {
        close(fd);
        return;
    }
    if (fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        perror("fcntl:");
        if(errno == EINTR)
            goto add_wlock;
    }

    if (ftruncate(fd, 0) < 0)
        perror("truncate file error:");

    ret = safe_write(fd, data, len);
    if (ret != len)
    {
        perror("WriteFileBin write Error");
    }
    
    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW,&flockptr);    

    close(fd);
}

static unsigned long crc32(char *data, int length)
{
	unsigned long crc, poly;
	long crcTable[256];
	int i, j;
	poly = 0xEDB88320L;
	for (i=0; i<256; i++) {
		crc = i;
		for (j=8; j>0; j--) {
			if (crc&1) {
				crc = (crc >> 1) ^ poly;
			} else {
				crc >>= 1;
			}
		}
		crcTable[i] = crc;
	}
	crc = 0xFFFFFFFF;

	while( length-- > 0) {
		crc = ((crc>>8) & 0x00FFFFFF) ^ crcTable[ (crc^((char)*(data++))) & 0xFF ];
	}
	
	return crc^0xFFFFFFFF;
}


/**
 * As our new design, this function just touch an empty file
 * Denny Zhang  2011年 06月 07日 星期二 10:15:22 CST
 */
#if 0
extern void nvram_default()
{
	int fd = -1;

	if((fd = open(NVRAM_TMP_PATH, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR)) < 0)
    {
        perror("open Error");
        return;
    }

	close(fd);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief  make a mirrorimage from flash to ram for default config
 *         This can improve performance when do nvram operation
 * @author Denny Zhang
 * @date   2011年 06月 07日 星期二 11:12:49 CST
 * @returns errorno if error happenes, see details in nvram.h  
 */
/* ----------------------------------------------------------------------------*/
extern int nvram_load_default(void)
{
    int fd = -1;
    int ret = -1;
    struct flock flockptr = {.l_type = F_WRLCK,
        .l_start = 0,
        .l_whence = SEEK_SET,
        .l_len = 0
    };
    int errorno = NVRAM_SUCCESS;
    int fd_in = -1;
    char *data = NULL;
    int len = 0;

    if((fd_in = open(NVRAM_DEFAULT, O_RDONLY)) < 0)
    {
        perror("open /etc/default Error");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }

    if((len = lseek(fd_in, 0, SEEK_END)) <= 0)
    {
        perror("caculate length Error");
        errorno = NVRAM_LEN_ERR;
        goto clean;
    }

    if( (data = (char *)malloc(len)) == NULL)
    {
        perror("malloc Error");
        errorno = NVRAM_MALLOC_ERR;
        goto clean;
    }

    lseek(fd_in, 0, SEEK_SET);
    if(read(fd_in, data, len) < 0)
    {
        perror("read Error");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }

    if((fd = open(NVRAM_TMP_DEFAULT, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0)
    {
        perror("open Error");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }

    if(fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        perror("fcntl:");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }

    if(ftruncate(fd, 0) < 0)
    {
        perror("truncate file error:");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }


    ret = safe_write(fd, data, len);
    if(ret < 0)
    {
        perror("write Error");
        errorno = NVRAM_FLASH_ERR;
        goto clean;
    }
    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW,&flockptr);

clean:
    if(-1 != fd_in)
        close(fd_in);

    if(-1 != fd)
        close(fd);

    if(data) 
        free(data);

    return errorno;
}

extern int nvram_load()
{
    unsigned long crc = 0;
    int fd1 = -1;
    int errorno = NVRAM_SUCCESS;
    char *data = NULL;
    int ret = -1;
    nvram_header_t header;
    int fd2 = -1;
#if 0
    /** make a mirrorimage for default config to 
      * improve performance when do nvram_get
      * Denny Zhang 2011年 06月 07日 星期二 11:10:46 CST
      */
    errorno = nvram_load_default();
    if(NVRAM_SUCCESS != errorno)
        goto end;
#endif

    fd2 = nvram_lock();
    if(fd2 < 0 )
    {
        printf("nvram lock fail\n");
    }
    /*read user config from FLASH*/
    fd1=open(NVRAM_PATH,O_RDONLY);
    if(fd1<0)
    {
        printf("NVRAM_FLASH_ERR, path %s\n", NVRAM_PATH);
        errorno = NVRAM_FLASH_ERR;
        goto end;
    }

    ret = read(fd1, &header,sizeof(nvram_header_t));

    if(ret < 0 || ret != sizeof(nvram_header_t))
    {
        printf("NVRAM_FLASH_ERR, path %s\n", NVRAM_PATH);
        close(fd1);
        errorno = NVRAM_FLASH_ERR;
        goto end;
    }
    /*seek to header end*/
    lseek(fd1,NVRAM_HEADER_SIZE,0);
    if(header.magic!=NVRAM_MAGIC)
    {

        close(fd1);
        errorno = NVRAM_MAGIC_ERR;
        goto end;
    }

    data = (char *)malloc(header.len+1);
    if(!data)
    {
        printf("%s:%d malloc(%lu) error, \n", __FUNCTION__, __LINE__, header.len+1);
        close(fd1);
        errorno = NVRAM_MALLOC_ERR;
        goto end;
    }
    ret = read(fd1, data, header.len);

    if(ret < 0 || ret != header.len)
    {
        printf("NVRAM_FLASH_ERR, ret = %d\n", ret);
        close(fd1);
        errorno = NVRAM_FLASH_ERR;
        goto end;
    }		
    close(fd1);	

    crc=crc32(data, header.len);
    if(crc!=header.crc)
    {
        printf("header.crc=%lx crc=%lx\n",header.crc, crc);
        free(data);
        errorno = NVRAM_CRC_ERR;
        goto end;
    }
    writeFileBin(NVRAM_TMP_PATH, data, header.len);
    free(data);
    /*end of read user config from flash*/

end:
    nvram_unlock(fd2);
    return errorno;
}

/*
 * mtd_erase: for Ralink CFI(MTD Flash driver) Must First Erase, before write
 * Input:   mtd_fd        mtdblock handle
 * Reutrn:     0 --- successful
 *             -1 --- fail
 * PS: Don't close the fd after erase
 */
int mtd_erase(int mtd_fd)
{
    int fd = -1;
	struct mtd_info_user mtdInfo;
	struct erase_info_user mtdEraseInfo;

	fd = mtd_fd;
	if(fd < 0) {
	   return -1;
	}

	if(ioctl(fd, MEMGETINFO, &mtdInfo)) {
   	    return -1;
	}
	mtdEraseInfo.length = mtdInfo.erasesize;

	for (mtdEraseInfo.start = 0;
		 mtdEraseInfo.start < mtdInfo.size;
		 mtdEraseInfo.start += mtdInfo.erasesize)
       {
		ioctl(fd, MEMUNLOCK, &mtdEraseInfo);//we do not need this by now
		if(ioctl(fd, MEMERASE, &mtdEraseInfo))
		{
		    return -1;
		}
	}
	return 0;
}

extern int nvram_commit()
{
	int fd1 = -1;
        int fd2 = -1;
	char *data = NULL;
	unsigned long len = 0;
	int ret = -1;
	nvram_header_t header;
	nvram_header_t TmpHeader;

        fd2 = nvram_lock();
	if(fd2 < 0 )
	{
	    printf("nvram lock fail\n");
	}

	printf("Enter NVRAM_COMMIT function.\n");
	memset(&header, 0, sizeof(nvram_header_t));
	memset(&TmpHeader, 0, sizeof(nvram_header_t));
	
	// Blinking power led.
	system("echo 't3' > /proc/led");

	if((fd1 = open(NVRAM_PATH,O_RDWR)) < 0)
	{
	    perror("open fail:");
	    nvram_unlock(fd2);
	    return NVRAM_FLASH_ERR;
	}

    /**
     * read zero is meaningful
     * Denny Zhang 2011年 06月 07日 星期二 11:40:05 CST
     */
	if((len = readFileBin(NVRAM_TMP_PATH, &data)) < 0)
	{
        	if(data)
            	   free(data);
		 printf("%d - readFileBin fail\n", __LINE__);
	         nvram_unlock(fd2);
		return NVRAM_SHADOW_ERR;
	}
	header.magic=NVRAM_MAGIC;
	header.crc=crc32(data, len);
	header.len=len; 

	//printf("header.crc=%lx, len=%lx\n", header.crc, header.len);

	/* For Ralink CFI interface, MUST erase it before write */
	ret = mtd_erase(fd1);
        
        if(ret < 0)
        {
            if(data)
               free(data);
            close(fd1);
	    nvram_unlock(fd2);
            printf("%s, %d erase error:\n", __FUNCTION__, __LINE__);
	    return NVRAM_FLASH_ERR;
	}

	
	ret=write(fd1, (char *)&header, sizeof(nvram_header_t));
	if( ret <= 0 || ret != sizeof(nvram_header_t))
	{
	    perror("write header error:");
            if(data)
               free(data);
            close(fd1);
	    nvram_unlock(fd2);
	    return NVRAM_FLASH_ERR;
    }
	
	ret = lseek(fd1, 0, 0);

    if(ret < 0)
    {
        perror("lseek 0 error:");
    }

    ret=read(fd1, &TmpHeader, sizeof(nvram_header_t));

    if( ret <= 0 || ret != sizeof(nvram_header_t))
    {
        printf("%s, %d nvram header error:ret = %d\n", __FUNCTION__, __LINE__, ret);
        if(data)
            free(data);
        close(fd1);
	nvram_unlock(fd2);
	return NVRAM_FLASH_ERR;
    }

    //printf("TmpHeader.crc=%lx,header.crc=%lx len=%lx header.len=%lx ret=%d\n", TmpHeader.crc, header.crc, TmpHeader.len,header.len, ret);
    if(header.crc != TmpHeader.crc)
    {
        printf("%s, %d crc error:\n", __FUNCTION__, __LINE__);
    }
	lseek(fd1,NVRAM_HEADER_SIZE,0);
	ret = write(fd1, data, len);
	//printf("%s,%d: write: ret=%d, len=%lu\n", __FUNCTION__, __LINE__, ret, len);
	if (ret != len)
	{
	    printf("%s,%d: write error: len=%lu\n", __FILE__, __LINE__, len);
            if(data)
               free(data);
            close(fd1);
	    nvram_unlock(fd2);
	    return NVRAM_FLASH_ERR;
    }
    lseek(fd1,NVRAM_HEADER_SIZE,0);
    ret = read(fd1, data,len);
    if( ret <= 0 || ret != len)
    {
        printf("%s, %d nvram header error:ret = %d\n", __FUNCTION__, __LINE__, ret);
        if(data)
            free(data);
        close(fd1);
	nvram_unlock(fd2);
	return NVRAM_FLASH_ERR;
    }
	if(header.crc!=crc32(data, len))
        {
             printf("crc error: header.crc=%lu\n", header.crc);
	     close(fd1);
	     free(data);
	     nvram_unlock(fd2);
	     return NVRAM_FLASH_ERR;
	}			
        //printf("crc correct! done\n",NVRAM_PATH);
	close(fd1);
	free(data);

	nvram_unlock(fd2);
	return NVRAM_SUCCESS;
}

#endif

extern char* nvram_get_fun(const char *name,char *path)
{
	char *bufspace;
	int size;
	char *s,*sp;
	
	if((size=readFileBin(path, &bufspace))<0) 
		return NULL;

	for (s = bufspace; *s; s++) {
		if (!strncmp(s, name, strlen(name)) && *(s+strlen(name))=='=') {
			sp=malloc(strlen(s)-strlen(name));
			if(sp == NULL)
			{
				free(bufspace);
				return NULL;
			}
			memcpy(sp,(s+strlen(name)+1),(strlen(s)-strlen(name)));
			free(bufspace);
			return sp;
		}
		while(*(++s));
	}
	free(bufspace);
	return NULL;
}
/*
 *   write for called by scfmgr_getall
 * */
#if 0
extern char*  nvram_getall(char *data,int bytes)
{
 	char *bufspace;
	int size;

 	 if((size=readFileBin(NVRAM_TMP_PATH, &bufspace))<0)
                return (char *)NULL;
	 if (size<bytes)
		 bytes=size;
    memcpy(data,bufspace,bytes);
    free(bufspace);
    return data;
}

/**
 * step   one: get config from nvram"/tmp/nvram"
 *
 * step   two: if no this nvram item in user config 
 *             we get it from default config in RAM
 *             but don't add this item to user config.
 *
 * step three: if no default file exists"/tmp/default"
 *             we get it from default config in Flash
 *             and we try to reload default config to RAM
 * Denny Zhang,2011年 06月 07日 星期二 11:17:42 CST
 */
extern char* nvram_get(const char *name)
{	
    char *pt;

    if((pt=nvram_get_fun(name,NVRAM_TMP_PATH))==NULL)
    {
        if(0 != access(NVRAM_TMP_DEFAULT,F_OK))
        {
           if(NVRAM_SUCCESS != nvram_load_default())
           {
                /*if mirror default failed, we get value from /etc/default in Flash*/
                if((pt = nvram_get_fun(name,NVRAM_DEFAULT)) == NULL)
                    return NULL;
                else
                    return pt;
           }
        }
        if((pt = nvram_get_fun(name,NVRAM_TMP_DEFAULT)) == NULL)
            return NULL;
    }

    return pt;
}

static char emp_str[]="";

extern char* nvram_safe_get(const char *name)
{
	char *pt;

    pt = nvram_get(name);

    if(NULL == pt)
        pt = strdup(emp_str);
#if 0
    if((pt=nvram_get_fun(name,NVRAM_TMP_PATH))==NULL){
			if((pt=nvram_get_fun(name,NVRAM_DEFAULT))!=NULL)
				nvram_set(name,pt);
			else
				pt=strdup(emp_str);
	}
#endif

	return pt;
}

extern int nvram_set(const char* name,const char* value)
{
	// Blinking power led.
	system("echo 't1' > /proc/led");
	return nvram_set_p(NVRAM_TMP_PATH, name, value);
}
#endif
extern int nvram_set_p(const char *path, const char* name,const char* value)
{
	char *bufspace, *targetspace;
	int size;
	char *sp, *s;
	int found=0;
		
	if((size = readFileBin(path, &bufspace)) >= 0) 
        {
	    targetspace = malloc(size+strlen(name)+strlen(value)+2);
	}
	else 
        {
        	
	    targetspace=malloc(strlen(name)+strlen(value)+3);

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
	        *(sp++)=END_SYMBOL;
	    }
	
		free(bufspace);
	}
	if(!found){
		strcpy(sp, name);
		sp+=strlen(name);
        	*(sp++) = '=';
	        strcpy(sp, value);
		sp+=strlen(value);
	        *(sp++) = END_SYMBOL;
	}
        
	*(sp) = END_SYMBOL;

	writeFileBin(path, targetspace, (sp-targetspace)+1);
	free(targetspace);
	
	return NVRAM_SUCCESS;
}

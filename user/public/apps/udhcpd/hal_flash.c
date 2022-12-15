
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "scutil.h"


#define DHCP_LEASE_MAX_FLASH_SIZE (24*1024)
#define DHCP_LEASE_FLASH_DATA_PATH "/tmp/ubi9_0/dhcp_lease_info"

#define DHCP_LEASE_MAGIC_NUMBER 0x20111228

typedef struct lease_flash_header_s
{
    unsigned long magic;
    unsigned long data_len;
    unsigned long data_crc;
    unsigned long reserved;
}lease_flash_header_t;


static int write_data_to_file(char *buf, unsigned long buf_len, char *path)
{
    int fd = -1;
    struct flock flockptr = {
        .l_type = F_WRLCK,
        .l_start = 0,
        .l_whence = SEEK_SET,
        .l_len = 0
    };

    if (!buf)
    {
        printf("Invalid data pointer!\n");
        goto _error;
    }

    if (!path)
    {
        printf("Invalid path pointer!\n");
        goto _error;
    }

    if ((fd = open(path, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0)
    {
        printf("Open file \"%s\" failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error;
    }

    if (fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        printf("Fcntl F_SETLKW file \"%s\" failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error;
    }

    if (write(fd, buf, buf_len) != (long)buf_len)
    {
        printf("Write file \"%s\" failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error2;
    }

    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &flockptr);
    close(fd);
    return 0;

_error2:
    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &flockptr);
_error:
    if (fd >= 0)
        close(fd);
    return -1;
}

static int read_data_from_file(char **buf, unsigned long *buf_len, char *path, unsigned long header_len)
{
    struct stat file_stat;
    int fd = -1;
    struct flock flockptr = {
        .l_type = F_WRLCK,
        .l_start = 0,
        .l_whence = SEEK_SET,
        .l_len = 0
    };

    *buf = NULL;
    *buf_len = 0;

    if (!path)
    {
        printf("Invalid file pointer!\n");
        goto _error;
    }

    if ((fd = open(path, O_RDWR)) < 0)
    {
        printf("Open file \"%s\" failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error;
    }

    if (fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        printf("Fcntl F_SETLKW file \"%s\" failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error;
    }

    if (stat(path, &file_stat) < 0)
    {
        printf("Get file \"%s\" status failed, errno:%d(%s).\n", path, errno, strerror(errno));
        goto _error2;
    }

    *buf = (char *)malloc(header_len + file_stat.st_size);
    if (*buf == NULL)
    {
        printf("Malloc failed, errno:%d(%s).", errno, strerror(errno));
        goto _error2;
    }

    if (read(fd, (*buf)+header_len, file_stat.st_size) != file_stat.st_size)
    {
        printf("Read failed, errno:%d(%s).", errno, strerror(errno));
        goto _error2;
    }

    *buf_len = header_len + file_stat.st_size;

    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &flockptr);
    close(fd);
    return 0;

_error2:
    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &flockptr);
_error:
    if (*buf)
    {
        free(*buf);
        *buf = NULL;
    }
    if (fd >= 0)
        close(fd);
    return -1;
}

static int write_data_to_flash(char *buf, unsigned long buf_len, char *path)
{
    return write_data_to_file(buf, buf_len, path);
}

static int read_data_from_flash(char **buf, unsigned long *buf_len, char *path)
{
    return read_data_from_file(buf, buf_len, path, 0);
}

int hal_flash_store_dhcp_lease_info(char *data_file)
{
    lease_flash_header_t header;
    int header_len = sizeof(lease_flash_header_t);
    char *buf = NULL;
    unsigned long buf_len = 0;

    if (read_data_from_file(&buf, &buf_len, data_file, header_len) < 0)
    {
        printf("Read data from file \"%s\" failed, errno:%d(%s).", data_file, errno, strerror(errno));
        goto _error;
    }

    memset(&header, 0, header_len);
    header.magic = DHCP_LEASE_MAGIC_NUMBER;
    header.data_len = buf_len - header_len;
    header.data_crc = util_crc32(buf+header_len, header.data_len);
    memcpy(buf, &header, header_len);

    if (write_data_to_flash(buf, buf_len, DHCP_LEASE_FLASH_DATA_PATH) < 0)
    {
        printf("Write data to flash failed, errno:%d(%s).", errno, strerror(errno));
        goto _error;
    }

    free(buf);
    return 0;

_error:
    if (buf)
        free(buf);
    return -1;
}

int hal_flash_load_dhcp_lease_info(char *data_file)
{
    lease_flash_header_t *p_header;
    int header_len = sizeof(lease_flash_header_t);
    char *buf = NULL;
    unsigned long buf_len = 0;

    if (read_data_from_flash(&buf, &buf_len, DHCP_LEASE_FLASH_DATA_PATH) < 0)
    {
        printf("Read data from flash failed, errno:%d(%s).", errno, strerror(errno));
        goto _error;
    }

    p_header = (lease_flash_header_t *)buf;

    if (p_header->magic != DHCP_LEASE_MAGIC_NUMBER)
    {
        printf("Error, magic number is different.\n");
        goto _error;
    }
    if ((p_header->data_len + header_len) != buf_len)
    {
        printf("Error, data length is not right. d_len:%lu, h_len:%lu, t:%lu\n", p_header->data_len, header_len, buf_len);
        goto _error;
    }
    if (p_header->data_crc != util_crc32(buf+header_len, p_header->data_len))
    {
        printf("CRC Error, maybe data has been destroyed.\n");
        goto _error;
    }

    if (write_data_to_file(buf+header_len, p_header->data_len, data_file) < 0)
    {
        printf("Write data to file failed, errno:%d(%s).", errno, strerror(errno));
        goto _error;
    }

    free(buf);
    return 0;

_error:
    if (buf)
        free(buf);
    return -1;
}

int hal_flash_get_dhcp_lease_info_max_size(void)
{
    return (DHCP_LEASE_MAX_FLASH_SIZE - sizeof(lease_flash_header_t));
}







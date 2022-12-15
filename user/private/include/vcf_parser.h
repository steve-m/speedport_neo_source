#ifndef __VCF_PARSER__
#define __VCF_PARSER__

#define UPLD_MAX_VCF_FILE   (1*1024*1024)    /* 1M */

#define UP_VCF_NAME     "/tmp/var/vd168.vcf"    /*the import vcf file name*/
#define VCF_RET_NAME    "/tmp/var/vcf.ret"      /*the parser result*/
#define UP_VCF_LOG      "/tmp/var/vcf.log"      /*the upload vcf status */

#define VCF_PARSER_WAITTING_TIME    5

typedef enum
{
    VCF_UP_NONE = 0,
    VCF_UP_NOFILE = 1,
    VCF_UP_WRONGFILE = 2,
    VCF_UP_NOMEMORY = 3,
    VCF_UP_WRONGCONT = 4,
    VCF_UP_OK = 5,
}UP_VCF_STATUS;

typedef struct sc_vcf_status_s {
    int  status;
    int  fail_entries;    
    int  ok_entries;
} sc_vcf_status_t;

#endif

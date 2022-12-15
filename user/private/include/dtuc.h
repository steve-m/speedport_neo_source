#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#ifdef DTUC_DEBUG
#define ERROR(...) fprintf(stderr, __VA_ARGS__)
#define WARN(...) fprintf(stderr, __VA_ARGS__)
#define INFO(...) fprintf(stderr, __VA_ARGS__)
#define DEBUG(...) fprintf(stdout, __VA_ARGS__)
#else
#define ERROR(...) 
#define WARN(...) 
#define INFO(...) 
#define DEBUG(...) 
#endif

#define CHECK_CPE_FW                    1
#define CHECK_EMAIL_ABUSE               1<<1
#define CHECK_DFND_FW                   1<<2

/* DT Update Check */
enum {
    DTUC_RET_OK,                        /* success, product(CPE) found */        
    DTUC_RET_FAIL = 100,                /* failure, system error or product(CPE) not found */
    DTUC_RET_CONNECT_FAIL,              /* failure, http server connect fail */
};

typedef struct DTUC_Input_s{
    char url[256];                      /* Download URL */
    int  attribute;                     /* DTUC event flag */
    char *extra_product_name;           /* Extra parameter for specify DFND product name */
}DTUC_Input_t;

typedef struct DTUC_ParaObj_s{
    char product_class[256];            /* ProductClass */
    char model_name[256];               /* ModelName */
    char fw_version[256];               /* FirmwareVersion */
    char iwa_version[256];              /* IWAVersion */
    char image_url[256];                /* ImageURL */
    char digest[256];                   /* Digest */
}DTUC_ParaObj_t;

typedef struct DTUC_Output_s{
    DTUC_ParaObj_t data;
    struct DTUC_Output_s *next;
}DTUC_Output_t;

//int dtuc_show_list(DTUC_Output_t* head);
DTUC_Output_t* dtuc_init_list(void);
void dtuc_free_list(DTUC_Output_t* head);
void cleanup_dt_update_check(void);
/* Return 
 * DTUC_RET_OK:             Success, we found target 
 * DTUC_RET_FAIL:           Fail, becasue system error or can not find target
 * DTUC_RET_CONNECT_FAIL:   Fail, because server connect fail, need do retry
 *
 * Detail information will collect in DTUC_Output_t *g_DTUC_Ret if Return DTUC_RET_OK
 */
int do_dt_update_check(DTUC_Input_t *g_DTUC_Conf, DTUC_Output_t *g_DTUC_Ret);


#ifndef CAL_USB_STORAGE_H 
#define CAL_USB_STORAGE_H

typedef struct _us_disk
{
    char key[8];
    char disk_name[256];
    char dev_name[32];    /* key, template */
    //char alias_disk_name[256];
    char vol_name[64];
    char serial_num[64];
    char partition[32];
    //char letter[2];
    char fs_type[8];
    char capacity[64];
    char approve[8];
    char index;
}cal_us_disk;
#endif


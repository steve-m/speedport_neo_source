#ifndef _USB_API_H
#define _USB_API_H

#define MAX_CONNDISK_NUM    8
#define CONNECTED_DISKS     "/tmp/uxx_s/con_disks"

struct con_disks
{
    char index;
    char disk_name[256];
    //char alias_disk_name[256];
    char serial_num[64];
    char mount_point_name[256];
};

void usb_record_connected_storages(cal_us_disk disk, char* mount_path);
int usb_find_mount_path(char *disk_name, char *mount_path);
int usb_parse_given_folder(char *folder, char *disk_name, char *dir);
#endif


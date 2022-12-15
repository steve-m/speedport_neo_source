/**
 * @file   unim_client.h
 * @author Martin_Huang@sdc.sercomm.com
 * @date   2011-10-10
 * @brief  notify mechanism 
 *         client will notify unim that uni configration has been updated 
 *
 * Copyright - 2011 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */

#ifndef __BGM_H__
#define __BGM_H__
#include <net/if.h>

#define BGM_CFG_BASE     "/tmp/1/"
#define BGM_SOCK_NAME    BGM_CFG_BASE"sname"
#define BGM_L2_DDB       BGM_CFG_BASE"ddb"

#define BGM_MAX_EMAC_NUM           4
#define BGM_MAX_PORT_NUM_PER_EMAC  1
#define BGM_MAX_UNI_NUM            (BGM_MAX_EMAC_NUM * BGM_MAX_PORT_NUM_PER_EMAC )

typedef struct tag_BGM_PORT_INFO{
    char used;
    char index;
    char state;
    char tag_num;
    char br_name[IFNAMSIZ];
    char port_name[IFNAMSIZ];
    char bridging;
    int type_bit;
    int port_bit;
    int flood_map;
    int port_state_bit;
    int ether_type;
    int inner_vid;
    int inner_pbit;
    int outer_vid;
    int outer_pbit;
    struct tag_BGM_PORT_INFO *related;
}BGM_PORT_INFO_t;

typedef struct tag_BGM_COMMAND{
    int cmd;
    int sub_cmd;
    char data[256];
}BGM_COMMAND_t;

enum {
    BGM_CLIENT_NOTIFY_CMD,
};
enum {
    BGM_CLIENT_USER,
    BGM_CLIENT_OMCI,
};

int bgm_update_notified_by_omci(void);
int bgm_update_notified_by_user(void);
#endif



#ifndef _SC_DRV_WIFI_INOF_H_
#define _SC_DRV_WIFI_INOF_H_

typedef struct sc_wifi_stats_s{
    unsigned long tx_data;
    unsigned long rx_data;
    unsigned long tx_packets;
    unsigned long tx_drops;
    unsigned long rx_packets;
    unsigned long rx_crc_errors;
    unsigned long rx_drops;
}sc_wifi_stats_t;

#endif


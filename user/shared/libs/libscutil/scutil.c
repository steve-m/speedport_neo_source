#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include "scutil.h"
#include  "wifi/wifi_define_bcm.h"

const unsigned char ibm_tounicode[128]=
{
    0xC7, 0xFC, 0xE9, 0xE2, 0xE4, 0xE0, 0xE5, 0xE7, 0xEA, 0xEB, 0xE8, 0xEF, 0xEE, 0xEC, 0xC4, 0xC5, 
    0xC9, 0xE6, 0xC6, 0xF4, 0xF6, 0xF2, 0xFB, 0xF9, 0xFF, 0xD6, 0xDC, 0xA2, 0xA3, 0xA5, 0x00, 0x00, 
    0xE1, 0xED, 0xF3, 0xFA, 0xF1, 0xD1, 0xAA, 0xBA, 0xBF, 0x00, 0xAC, 0xBD, 0xBC, 0xA1, 0xAB, 0xBB, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xDF, 0x00, 0x00, 0x00, 0x00, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xB1, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x00, 0xB0, 0x00, 0xB7, 0x00, 0x00, 0xB2, 0x00, 0xA0,  	
};

long get_uptimes(void)
{
    struct sysinfo info;
    sysinfo(&info);
    return info.uptime;
}

int get_sockfd()
{
	int sockfd = -1;
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("user: socket creating failed");
		return (-1);
	}
	return sockfd;
}

int getIFInfo(char *if_name, if_info_t *if_info)
{
	unsigned char *pt;
	struct ifreq ifr;
	struct sockaddr_in *saddr;
	int fd;
	int ret=0;

	strcpy(if_info->ifname,if_name);
	if ((fd=get_sockfd())>=0)
	{
		strcpy(ifr.ifr_name, if_info->ifname);
		ifr.ifr_addr.sa_family = AF_INET;
		/* get ip address */
		if (ioctl(fd, SIOCGIFADDR, &ifr)==0){
			saddr = (struct sockaddr_in *)&ifr.ifr_addr;
			strcpy(if_info->ipaddr,(char *)inet_ntoa(saddr->sin_addr));
			/* for hide on demand ip */
			if(strcmp(if_info->ipaddr,"10.64.64.64")==0)
				ret=-2;
		}else
			ret=-1;
		/* get netmask */
		if (ioctl(fd,SIOCGIFNETMASK , &ifr)==0){
			saddr = (struct sockaddr_in *)&ifr.ifr_addr;
			strcpy(if_info->mask,(char *)inet_ntoa(saddr->sin_addr));
		}else
			ret=-1;
		/* get mtu */
		if (ioctl(fd,SIOCGIFMTU, &ifr)==0){
			if_info->mtu=ifr.ifr_mtu;
		}else
			ret=-1;
		/* get mac address */
		if (ioctl(fd, SIOCGIFHWADDR, &ifr)==0){
			pt=(unsigned char*)ifr.ifr_hwaddr.sa_data;
			sprintf(if_info->mac,"%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX"
					,*pt,*(pt+1),*(pt+2),*(pt+3),*(pt+4),*(pt+5));
			if_info->mac[17]='\0';
			snprintf(if_info->mac_raw, sizeof(if_info->mac_raw), "%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"
					,*pt,*(pt+1),*(pt+2),*(pt+3),*(pt+4),*(pt+5));
		}else
			ret=-1;
		close(fd);

		/*Try to get gateway*/
		{
			FILE *fp;

			if_info->gw.s_addr = 0;

			fp = fopen("/proc/net/route","r");
			if(fp)
			{
				char line[256];
				while(fgets(line, sizeof(line), fp)){
					if(!strstr(line, if_name))
						continue;
					if(sscanf(line, "%*s\t00000000\t%x", (int *)&if_info->gw.s_addr))
						break;	
				}
				fclose(fp);
			}	
		}

		return ret;

	}
	return -1;
}

int ibmpc_to_utf8(uint8_t *in, int insize, uint8_t **out)
{
    int i = 0;
    int outsize = 0;
    int charscount = 0;
    uint8_t *result = NULL;
    uint8_t *tmp = NULL;
    uint8_t unicode;

    charscount = insize / sizeof(uint8_t);
    result = (uint8_t *)malloc(charscount * 3 + 1);
    memset(result, 0, charscount * 3 + 1);
    tmp = result;

    for (i = 0; i < charscount; i++)
    {
        if (in[i] >= 0x00 && in[i] <= 0x7f)
        {
            *tmp = (uint8_t)in[i];
            tmp += 1;
            outsize += 1;
        }
        else if (in[i] >= 0x80 && in[i] <= 0xff)
        {
            unicode = ibm_tounicode[in[i]-128];
            *tmp = 0xc0 | (unicode >> 6);
            tmp += 1;
            *tmp = 0x80 | (unicode & (0xff >> 2));
            tmp += 1;
            outsize += 2;
        }
    }
    *tmp = '\0';
    *out = result;
    return 0;
}

int scWlanMacExit(unsigned char *mac)
{
    unsigned char *tmp_c = mac;
    char tmp[2048]="";
	char *pt=NULL;
	FILE *fp;
	if (access(RADIO_STATUS_24GUP, F_OK) == 0)
    {
	system("/usr/sbin/wlctl -i wl0 assoclist > /tmp/wlan_mac");
	system("/usr/sbin/wlctl -i wl0.1 assoclist >> /tmp/wlan_mac");
	}
	if (access(RADIO_STATUS_5GUP, F_OK) == 0)
    {
	system("/usr/sbin/wlctl -i wl1 assoclist >> /tmp/wlan_mac");
	system("/usr/sbin/wlctl -i wl1.1 assoclist >> /tmp/wlan_mac");
	}
	fp=fopen("/tmp/wlan_mac","r");
	if(fp==NULL)
		return -1;

	fread(tmp,2048,1,fp);
	fclose(fp);

    while(*tmp_c)
    {
        if(*tmp_c >= 'a' && *tmp_c <= 'z')
            *tmp_c -= 'a' - 'A';
        tmp_c++;
    }

	if((pt=strstr(tmp,mac))!=NULL){
		return 1;
	}

    return 0; 
}

unsigned long util_crc32(char *data, int length)
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

char *scGetStdTime(int sec)
{
	static char time_buf[64] = "";
	time_t t;
	struct tm *st;
	struct sysinfo info;
	
	sysinfo(&info);
	
	//setenv("TZ", cal_ntp_get_timezone(), 1);
	t = time(NULL);
	
	t -= info.uptime-(time_t)sec;
	t = t/4;
	t = t*4;
	st = localtime(&t);

	sprintf(time_buf, "%d-%02d-%02d %02d:%02d:%02d"
							,st->tm_year + 1900
							,st->tm_mon + 1
							,st->tm_mday
							,st->tm_hour
							,st->tm_min
							,st->tm_sec);
							
	return time_buf;
}

void getTimeofDay(char *buffer)
{
    time_t t;
    struct tm *st;
    int len = 0;
    
    time(&t);
    st=localtime(&t); 
#ifdef DT
    len = sprintf(buffer,"%02d.%02d.%d %02d:%02d:%02d"
                  ,st->tm_mday
                  ,st->tm_mon+1
                  ,st->tm_year+1900
                  ,st->tm_hour
                  ,st->tm_min
                  ,st->tm_sec);

#else    
    len = sprintf(buffer,"%d-%02d-%02d %02d:%02d:%02d"
                ,st->tm_year+1900
                ,st->tm_mon+1
                ,st->tm_mday
                ,st->tm_hour
                ,st->tm_min
                ,st->tm_sec);
#endif
    buffer[len] = 0;
}

/************************************************************************
 * check_call_status
 * if line call status is emergency call(status = 11),
 * voip can not be stop(restart), device can not reboot
 *
 * input  :
 *          st  Which status want to check
 *
 * return : 
 *          1   voip can be reboot or stop(restart).
 *          0   voip can not be reboot or stop(restart).  
*************************************************************************/
int check_call_status(int st)
{
    FILE *console;
    FILE* fp;

	if (access("/var/vgw.lock", F_OK) != 0)
		return 1;

    if((fp=fopen("/var/telno_status", "r")) != NULL)
    {
        char tmp[256] = {0};
        int callstatus, emgStatus;

        while(fgets(tmp, sizeof(tmp), fp))
        {
            sscanf(tmp, "%*[^:]:%d:%d", &callstatus, &emgStatus);
            if(st == 0)
            {
                if (callstatus != 0)
                {
                    console=fopen("/dev/console", "w");
                    fprintf(console,"[%s]: Call %s is not idle\n", __FILE__, tmp);
                    fclose(console);
                    fclose(fp);

                    return 0;
                }
            }
            else
            {
                if (emgStatus == 1)
                {
                    console=fopen("/dev/console", "w");
                    fprintf(console,"[%s]: Call %s is emergency call\n", __FILE__, tmp);
                    fclose(console);
                    fclose(fp);

                    return 0;
                }
            }
        }
        fclose(fp);
    }

    return 1;
}

int getFonClientNum()
{
    struct stat fon_stat;

    system("wlctl -i wl0.1 assoclist > /tmp/var/hsfon_clientnum");
    system("wlctl -i wl1.1 assoclist >> /tmp/var/hsfon_clientnum");

    if(access("/tmp/var/hsfon_clientnum", F_OK) != 0)
        return 0;

    stat("/tmp/var/hsfon_clientnum", &fon_stat);

    unlink("/tmp/var/hsfon_clientnum");
    if(fon_stat.st_size <= 0)
        return 0;
    else
        return 1;
}

/************************************************************************
 * check_cwmp_state
 *
 * return : 
 *          1   cwmp running
 *          0   cwmp idle
*************************************************************************/
int check_cwmp_state(void)
{
	if(access("/tmp/var/tr69", F_OK)==0)
		return 1;

	return 0;
}

int getMgtBrInfo(if_info_t *if_info)
{
    char ifName[16];
    FILE *fp;
    char line[64+1];
    int vlanId = 0;
    
    /*If vlan disabled*/
    if((fp=fopen("/tmp/vlan.conf","r"))==NULL)
    {
        sprintf(ifName,"br0");
    }
    else
    {
        fgets(line, 64, fp); /* eat native vlan id */
        fgets(line, 64, fp); /* management vlan id */
        vlanId = atoi(line);
        sprintf(ifName,"br%d", vlanId);
        fclose(fp);
    }
    return getIFInfo(ifName, if_info);
}

int getIP6Info1(char *ifname, char *address , int ipv6_addr_scope)
{    
#if defined(AF_INET6) && defined(IN6_IS_ADDR_V4MAPPED)

	FILE *fp;
	char addr6[40], devname[20];
    struct in6_addr inaddr6;
	int plen, scope, dad_status, if_idx;
	char addr6p[8][5];
    
    if ((fp = fopen(PATH_PROCNET_IFINET6, "r")) != NULL) {
		while ( fscanf(fp, "%4s%4s%4s%4s%4s%4s%4s%4s %02x %02x %02x %02x %20s\n",
				addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
				addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
				&dad_status, devname) != EOF) {
		    if (!strcmp(devname, ifname) && (scope == ipv6_addr_scope)){
		        
		        sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
						addr6p[0], addr6p[1], addr6p[2], addr6p[3],
						addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
				inet_pton(AF_INET6, addr6, &inaddr6);				
				inet_ntop(AF_INET6, (void *)&inaddr6, address, INET6_ADDRSTRLEN);
				sprintf(address,"%s/%d",address,plen);
				
				fclose(fp);				
				return 0;
		    }
		    else
		        continue;
	    }
	fclose(fp);
	}
	return -1;	
#else
    return -1;
#endif
}
int lan_ipv6_prefix_generate(char *prefix)
{
	FILE *fp;
        char prefix_full_addr[128] = {0};
        struct in6_addr pre;
        char addrstr[INET6_ADDRSTRLEN];
        unsigned int subnetID;
       
        sscanf(sal_lan_get_subnetid_t(), "%x", &subnetID);
	memset(&pre, 0, sizeof(struct in6_addr));
        inet_pton(AF_INET6, sal_lan_get_gua_56bit_prefix_t(), &pre);
        pre.s6_addr[7] = subnetID;
        inet_ntop(AF_INET6, &pre, addrstr, sizeof(addrstr));

        strcpy(prefix, addrstr);
   	memset(prefix_full_addr, 0, 128);
	fp = fopen("/tmp/prefix_full", "r");
	if (!fp) {
		fp = fopen("/tmp/prefix_full", "w");
		if (fp) {
			fprintf(fp, "%s\n", addrstr);
			sal_lan_set_gua_prefix_t(addrstr);
			fclose(fp);
		}
	} else {
		if (fgets(prefix_full_addr, sizeof(prefix_full_addr), fp) != NULL) {
			fclose(fp);
			fopen("/tmp/prefix_full", "w");
			if (fp) {
				fprintf(fp, "%s\n", addrstr);
				sal_lan_set_gua_prefix_t(addrstr);
				fprintf(fp, "%s", prefix_full_addr);
				fclose(fp);
			}
		} 
	}
    return 0;
}
/*
*  For creating subnetID
*/
int lan_ipv6_subnetid_generate(char *p_subnetid_h)
{
    FILE *fp = NULL;
    unsigned char tmp_id_c = 0, old_subnetid_c=0;

    sscanf(p_subnetid_h, "%2x", &old_subnetid_c);
    
    fp = fopen("/dev/urandom","r");
    do {
        if (fp!=NULL) {
            tmp_id_c = fgetc(fp);
        }
        else {
            srand(time(NULL));
            tmp_id_c = rand()%256;
        }
    } while(tmp_id_c == old_subnetid_c);

    if (fp!=NULL) 
        fclose(fp);

    sprintf(p_subnetid_h,"%02x", tmp_id_c);
    return 0;
}

int get_productname(char *buffer)
{
    FILE *fp = NULL;
    char *p = NULL;
    char line_str[128];
   
    buffer[0]='\0';

    if((access("/etc/productname", F_OK) == 0) && (fp = fopen("/etc/productname", "r")))
    {
        fgets(line_str, sizeof(line_str), fp);
        if ((p=strchr(line_str,'\n'))!=NULL)
            *p='\0';
        fclose(fp);

        strcpy(buffer, line_str); 
        return 0;
    }

    return -1;
}


/*
 * options.c -- DHCP server option packet tools
 * Rewrite by Russ Dill <Russ.Dill@asu.edu> July 2001
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "dhcpd.h"
#include "files.h"
#include "options.h"
#include "leases.h"
#ifdef __SC_BUILD__
#include "sc_event.h"
#endif


/* supported options are easily added here */
struct dhcp_option options[] = {
	/* name[10]	flags					code */
	{"subnet",	OPTION_IP | OPTION_REQ,			0x01},
#ifdef __SC_BUILD__
	{"timezone",	OPTION_S32 | OPTION_REQ,				0x02},
#else
	{"timezone",	OPTION_S32,				0x02},
#endif
	{"router",	OPTION_IP | OPTION_LIST | OPTION_REQ,	0x03},
	{"timesvr",	OPTION_IP | OPTION_LIST,		0x04},
	{"namesvr",	OPTION_IP | OPTION_LIST,		0x05},
	{"dns",		OPTION_IP | OPTION_LIST | OPTION_REQ,	0x06},
	{"logsvr",	OPTION_IP | OPTION_LIST,		0x07},
	{"cookiesvr",	OPTION_IP | OPTION_LIST,		0x08},
	{"lprsvr",	OPTION_IP | OPTION_LIST,		0x09},
	{"hostname",	OPTION_STRING | OPTION_REQ,		0x0c},
	{"bootsize",	OPTION_U16,				0x0d},
	{"domain",	OPTION_STRING | OPTION_REQ,		0x0f},
	{"swapsvr",	OPTION_IP,				0x10},
	{"rootpath",	OPTION_STRING,				0x11},
	{"ipttl",	OPTION_U8,				0x17},
	{"mtu",		OPTION_U16,				0x1a},
	{"broadcast",	OPTION_IP | OPTION_REQ,			0x1c},

#ifdef __SC_BUILD__
	{"ntpsrv",	OPTION_IP | OPTION_LIST | OPTION_REQ,	0x2a},
	{"vendorinfo",  OPTION_HEX,           0x2b},
#else
	{"ntpsrv",	OPTION_IP | OPTION_LIST,		0x2a},
#endif
	{"wins",	OPTION_IP | OPTION_LIST,		0x2c},
	{"requestip",	OPTION_IP,				0x32},
	{"lease",	OPTION_U32,				0x33},
	{"dhcptype",	OPTION_U8,				0x35},
	{"serverid",	OPTION_IP,				0x36},
	{"message",	OPTION_STRING,				0x38},
#ifdef __SC_BUILD__
	{"vendorid",  OPTION_HEX,                 0x3c},
    {"clroute",OPTION_REQ |OPTION_LIST|OPTION_CLROUTE,   0x79},
#endif
	{"tftp",	OPTION_STRING,				0x42},
	{"bootfile",	OPTION_STRING,				0x43},
	{"sipsrv",	OPTION_STRING,				0x78},
	{"pu240",	OPTION_STRING,		        0xf0},  // pu = private use
	{"pu241",	OPTION_STRING,		        0xf1},
	{"pu242",	OPTION_STRING,		        0xf2},
	{"pu243",	OPTION_STRING,		        0xf3},
	{"pu244",	OPTION_STRING,		        0xf4},
	{"pu245",	OPTION_STRING,		        0xf5},
	{"pu246",	OPTION_STRING,		        0xf6},
	{"pu247",	OPTION_STRING,		        0xf7},
	{"pu248",	OPTION_STRING,		        0xf8},
	{"pu250",	OPTION_STRING,		        0xfa},
	{"",		0x00,				0x00}
};

/* Lengths of the different option types */
int option_lengths[] = {
	[OPTION_IP] =		4,
	[OPTION_IP_PAIR] =	8,
	[OPTION_BOOLEAN] =	1,
	[OPTION_STRING] =	1,
#ifdef __SC_BUILD__
	[OPTION_HEX]=		1,
#endif
	[OPTION_U8] =		1,
	[OPTION_U16] =		2,
	[OPTION_S16] =		2,
	[OPTION_U32] =		4,
	[OPTION_S32] =		4,
#ifdef __SC_BUILD__
	[OPTION_ROUTE] =	9,
    [OPTION_CLROUTE] =  1
#endif
};


/* get an option with bounds checking (warning, not aligned). */
unsigned char *get_option(struct dhcpMessage *packet, int code)
{
	int i, length;
	unsigned char *optionptr;
	int over = 0, done = 0, curr = OPTION_FIELD;

	optionptr = packet->options;
	i = 0;
	length = 308;
	while (!done) {
		if (i >= length) {
			LOG(LOG_WARNING, "bogus packet, option fields too long.");
			return NULL;
		}
		if (optionptr[i + OPT_CODE] == code) {
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
			return optionptr + i + 2;
		}
		switch (optionptr[i + OPT_CODE]) {
		case DHCP_PADDING:
			i++;
			break;
		case DHCP_OPTION_OVER:
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
			over = optionptr[i + 3];
			i += optionptr[OPT_LEN] + 2;
			break;
		case DHCP_END:
			if (curr == OPTION_FIELD && over & FILE_FIELD) {
				optionptr = packet->file;
				i = 0;
				length = 128;
				curr = FILE_FIELD;
			} else if (curr == FILE_FIELD && over & SNAME_FIELD) {
				optionptr = packet->sname;
				i = 0;
				length = 64;
				curr = SNAME_FIELD;
			} else done = 1;
			break;
		default:
			i += optionptr[OPT_LEN + i] + 2;
		}
	}
	return NULL;
}

#ifdef __SC_BUILD__
#define SC_OPTION_BACKUP_FILE    "/var/udhcpd.option"  
int sc_save_option_x(unsigned char *cmac, unsigned char *data, int code)
{
    FILE *fp;
    char line[512]={0}, filename[32];
    char *p=NULL;
    char cmd[256];
    int flag = 0;

    /*format 00:01:02:03:03:05=4D53465420352E30 */
    sprintf(cmd, "/bin/echo %s=%s >> %s%d&", cmac, data, SC_OPTION_BACKUP_FILE, code);
    sprintf(filename, "%s%d", SC_OPTION_BACKUP_FILE, code);
    fp=fopen(filename, "r");
    if(fp!=NULL)
    {
        while(fgets(line,sizeof(line),fp))
        {
            p=strstr(line,cmac);
            if(p==NULL)
                continue;
            flag = 1;
            break;        
        }
        fclose(fp);
    }
    if(flag)
        return 0;
    
    system(cmd);
    return 1;
}

unsigned char *sc_create_option_file(struct dhcpMessage *packet ,int code)
{
	int i, length;
	unsigned char *optionptr;
        int over = 0, done = 0, curr = OPTION_FIELD;
        unsigned char option_data[128], option_data_hex[256], cmac[18];
        unsigned char *p = NULL;
        int len=0, j;

	optionptr = packet->options;
	i = 0;
	length = 308;
	while (!done) {
		if (i >= length) {
			LOG(LOG_WARNING, "bogus packet, option fields too long.");
			return NULL;
		}
		if (optionptr[i + OPT_CODE] == code) {
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
                        
                        p = &optionptr[i + OPT_DATA];
                        sprintf(cmac, "%02X:%02X:%02X:%02X:%02X:%02X",  
                            packet->chaddr[0], packet->chaddr[1], packet->chaddr[2], 
                            packet->chaddr[3], packet->chaddr[4], packet->chaddr[5]);
                        //get data
                        memcpy(option_data, p, optionptr[i + OPT_LEN]);
                        option_data[optionptr[i + OPT_LEN]]='\0';
                        memset(option_data_hex, 0, 256);
                        for(j=0;j<optionptr[i + OPT_LEN];j++)
                            len += sprintf(option_data_hex+len, "%02X", option_data[j]);
                        //LOG(LOG_EMERG, "<%s,%d>cmac=%s, data=%s.\n", __FUNCTION__, __LINE__, cmac, option_data_hex);
                        sc_save_option_x(cmac, option_data_hex, code);

			return optionptr + i + 2;
		}
		switch (optionptr[i + OPT_CODE]) {
		case DHCP_PADDING:
			i++;
			break;
		case DHCP_OPTION_OVER:
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
			over = optionptr[i + 3];
			i += optionptr[OPT_LEN] + 2;
			break;
		case DHCP_END:
			if (curr == OPTION_FIELD && over & FILE_FIELD) {
				optionptr = packet->file;
				i = 0;
				length = 128;
				curr = FILE_FIELD;
			} else if (curr == FILE_FIELD && over & SNAME_FIELD) {
				optionptr = packet->sname;
				i = 0;
				length = 64;
				curr = SNAME_FIELD;
			} else done = 1;
			break;
		default:
			i += optionptr[OPT_LEN + i] + 2;
		}
	}
	return NULL;
}
#endif


#ifdef __SC_BUILD__
unsigned char *get_option_x(struct dhcpMessage *packet, int code, int *len)
{
	int i, length;
	unsigned char *optionptr;
	int over = 0, done = 0, curr = OPTION_FIELD;

	optionptr = packet->options;
	i = 0;
	length = 308;
        *len = 0;
	while (!done) {
		if (i >= length) {
			LOG(LOG_WARNING, "bogus packet, option fields too long.");
			return NULL;
		}
		if (optionptr[i + OPT_CODE] == code) {
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
			*len = *(optionptr + i + 1);
			return optionptr + i + 2;
		}
		switch (optionptr[i + OPT_CODE]) {
		case DHCP_PADDING:
			i++;
			break;
		case DHCP_OPTION_OVER:
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return NULL;
			}
			over = optionptr[i + 3];
			i += optionptr[OPT_LEN] + 2;
			break;
		case DHCP_END:
			if (curr == OPTION_FIELD && over & FILE_FIELD) {
				optionptr = packet->file;
				i = 0;
				length = 128;
				curr = FILE_FIELD;
			} else if (curr == FILE_FIELD && over & SNAME_FIELD) {
				optionptr = packet->sname;
				i = 0;
				length = 64;
				curr = SNAME_FIELD;
			} else done = 1;
			break;
		default:
			i += optionptr[OPT_LEN + i] + 2;
		}
	}
	return NULL;
}
int is_option_required(char code)
{
    int i;
    for(i = 0; options[i].code; i++)
    {
        if(code == options[i].code)
        {
	   if(options[i].flags & OPTION_REQ)
		return 1;
	}
    }
    return 0;
}
/* add for hidden page get all option from server*/
int sc_record_all_option(struct dhcpMessage *packet)
{
	FILE *fp = NULL;
    int len=0;
    char *temp = NULL;
    char output[1024] = {0};
    u_int32_t ip_int;
    char ip_str[32]={0};
    struct in_addr in;

    if (!(fp = fopen("/tmp/h_dhcpoptrecord_client.txt", "w"))) {
        return -1;
    }

    /* get option 3 router */
    if((temp = get_option_x(packet, DHCP_ROUTER	, &len)))
    {
        
        output[0]=0;
        ip_int = 0;
        ip_str[0] = 0;
        memcpy(&ip_int,temp,len);
        in.s_addr = ip_int;
        strncpy(ip_str,inet_ntoa(in),16);
        sprintf(output,"%d:%s\n",DHCP_ROUTER,ip_str);

        fwrite(output, strlen(output), 1, fp);
        temp = NULL;
        
    }
    /*get option 6 dns server*/ 
    if((temp = get_option_x(packet, DHCP_DNS_SERVER, &len)))
    {
        int cnt = 0;        
        int str_len = 0;
        
        output[0]=0;
        ip_int = 0;
        ip_str[0] = 0;
        
        str_len += sprintf(output+str_len,"%d:",DHCP_DNS_SERVER);
        while(cnt < len)
        {
            ip_int = 0;
            ip_str[0] = 0;
            memcpy(&ip_int,temp+cnt,4);
            in.s_addr = ip_int;
            strncpy(ip_str,inet_ntoa(in),16);
            str_len += sprintf(output+str_len,"[%s]",ip_str);
             cnt+=4;
        } 

        str_len += sprintf(output+str_len,"\n");
        fwrite(output, strlen(output), 1, fp);
        temp = NULL;
    }
    /*get option 51 leasetime*/ 
    if((temp = get_option_x(packet, DHCP_LEASE_TIME	, &len)))
    {
        output[0]=0;
        ip_int = 0;
        
        memcpy(&ip_int,temp,len);
        sprintf(output,"%d:%ld\n",DHCP_LEASE_TIME,ip_int);
        fwrite(output, strlen(output), 1, fp);
        temp = NULL;
    }

    /*get option 54 dhcp server*/ 
    if((temp = get_option_x(packet, DHCP_SERVER_ID, &len)))
    {
        output[0]=0;
        ip_int = 0;
        ip_str[0] = 0;
        
        memcpy(&ip_int,temp,len);
        in.s_addr = ip_int;
        strncpy(ip_str,inet_ntoa(in),16);
        sprintf(output,"%d:%s\n",DHCP_SERVER_ID,ip_str);
        fwrite(output, strlen(output), 1, fp);
        temp = NULL;

    }
    /*get option 121 static router*/ 
    if((temp = get_option_x(packet, DHCP_CLASSLESS_ROUTE , &len)))
    {
        int cnt = 0,str_len = 0,i = 0;
        int mask_code = 0;
        struct in_addr dest;
        struct in_addr netmask;
        struct in_addr gw;
        
        output[0]=0;
        
        char dest_buf[16], gw_buf[16];
        str_len += sprintf(output+str_len,"%d:",DHCP_CLASSLESS_ROUTE );
        while(len > 0)
        {
            mask_code = *(temp++);
             cnt = mask_code / 8;
             if (mask_code % 8)
                 cnt++;
             if((len = len - (1 + cnt + 4)) < 0)
                 break;

             netmask.s_addr=0xFFFFFFFF;
             for (i = 0; i < (32 - mask_code); i++){
                 netmask.s_addr = netmask.s_addr << 1;
             }

            dest.s_addr = *((uint32_t *)temp);
            dest.s_addr = dest.s_addr & netmask.s_addr;
            temp += cnt;
            gw.s_addr = *((uint32_t *)temp);
            temp += 4;
            sprintf(dest_buf, "%s", inet_ntoa(dest));
            sprintf(gw_buf, "%s", inet_ntoa(gw));
            str_len += sprintf(output+str_len,"[%s/%d-%s]",dest_buf ,mask_code, gw_buf);
        } 
   //    str_len += sprintf(output+str_len,"]");
        fwrite(output, strlen(output), 1, fp);
        temp = NULL;
    }
    fclose(fp);
  return 0;
}
#endif
/***********************************************************************
* Vendor class identifier( option 60 ) Format :                                                          
*                                                                                                                          
* 0                        7                          15                                                      31               
* ---------------+---------------+---------------+---------------+        
*         code(60)                Length                         Enterprise Code
* ---------------+---------------+---------------+---------------+
*       Field type              Field length                          Field value
*
************************************************************************/
#ifdef __SC_BUILD__
unsigned int get_vendor_id(struct dhcpMessage *packet, char *vendor_id, unsigned int id_length)
{
#define OPT60_ENTERPRISE_CODE_LEN		2

#define OPT60_FIELD_CODE				0
#define OPT60_FIELD_LEN					1
#define OPT60_FIELD_DATA				2

#define OPT60_FIELD_TYPE_VENDOR		1
#define OPT60_FIELD_TYPE_CATEGORY		2
#define OPT60_FIELD_TYPE_MODEL		3
#define OPT60_FIELD_TYPE_VERSION		4
#define OPT60_FIELD_TYPE_PROTO_PORT	5

	int i, length;
	unsigned char *optionptr;
	int over = 0, done = 0, curr = OPTION_FIELD;
	
	unsigned int last_length = 0, offset = 0;
	unsigned int field_type = 0, field_length = 0;
	char enterprise_code[OPT60_ENTERPRISE_CODE_LEN];

	if(!vendor_id || id_length<32)
	{
		return 0;
	}
	strcpy(vendor_id, "Computer");

	optionptr = packet->options;
	i = 0;
	length = 308;
	// CTC is "00"
	enterprise_code[0] = 0;
	enterprise_code[1] = 0;
	
	while (!done) 
	{
		if (i >= length) 
		{
			LOG(LOG_WARNING, "bogus packet, option fields too long.");
			return 0;
		}
		if (optionptr[i + OPT_CODE] == DHCP_VENDOR)  //option 60
		{   
			if (i /*offset*/ + 1 /*size of option code*/+ optionptr[i + OPT_LEN] /*option len*/ >= length) // total length is overflow
			{ 
				LOG(LOG_WARNING, "bogus packet, the value of option 60 length is too long.");
				return 0;
			}
			if(optionptr[i + OPT_LEN] <= 2) // option length is invalid
			{
				LOG(LOG_WARNING, "bogus packet, the value of option 60 length is too short.");
				return 0;
			}

			if( memcmp(optionptr + i + OPT_DATA, enterprise_code, OPT60_ENTERPRISE_CODE_LEN)==0 ) // enterprise code, CTC is "00"
			{
				/* Notes: '1 + 1' means 'size of field code' + 'size of field length' */
				for(
					last_length	= optionptr[i + OPT_LEN] -OPT60_ENTERPRISE_CODE_LEN, //the length of the fields except enterprise code length
					offset 		= i + 1 + 1 + OPT60_ENTERPRISE_CODE_LEN // start from field head;
					;
					last_length >= (unsigned int)1+ 1 + optionptr[offset + OPT60_FIELD_LEN] // total length is overflow
					;
					last_length	-= (1 + 1 + field_length),
					offset		+= (1 + 1 + field_length)
				) 
				{
					field_type	= optionptr[offset+OPT60_FIELD_CODE];
					field_length	= optionptr[offset+OPT60_FIELD_LEN];

					if( field_type == OPT60_FIELD_TYPE_CATEGORY )
					{
						if(field_length>=1 && field_length<=32)
						{
							memset(vendor_id, 0, id_length);
							memcpy(vendor_id, optionptr+offset+OPT60_FIELD_DATA, field_length);
						}
						return 1;
					}
				}
			}
			else
			{
			//	LOG(LOG_WARNING, "bogus packet, enterprise code incorrect (Not CTC).");
				return 0;
			}
		}	
		switch (optionptr[i + OPT_CODE]) {
		case DHCP_PADDING:
			i++;
			break;
		case DHCP_OPTION_OVER:
			if (i + 1 + optionptr[i + OPT_LEN] >= length) {
				LOG(LOG_WARNING, "bogus packet, option fields too long.");
				return 0;
			}
			over = optionptr[i + 3];
			i += optionptr[OPT_LEN] + 2;
			break;
		case DHCP_END:
			if (curr == OPTION_FIELD && over & FILE_FIELD) {
				optionptr = packet->file;
				i = 0;
				length = 128;
				curr = FILE_FIELD;
			} else if (curr == FILE_FIELD && over & SNAME_FIELD) {
				optionptr = packet->sname;
				i = 0;
				length = 64;
				curr = SNAME_FIELD;
			} else done = 1;
			break;
		default:
			i += optionptr[OPT_LEN + i] + 2;
		}
	}
	return 0;
}
#endif
/* return the position of the 'end' option (no bounds checking) */
int end_option(unsigned char *optionptr)
{
	int i = 0;

	while (optionptr[i] != DHCP_END) {
		if (optionptr[i] == DHCP_PADDING) i++;
		else i += optionptr[i + OPT_LEN] + 2;
	}
	return i;
}


/* add an option string to the options (an option string contains an option code,
 * length, then data) */
int add_option_string(unsigned char *optionptr, unsigned char *string)
{
	int end = end_option(optionptr);


	/* end position + string length + option code/length + end option */
	if (end + string[OPT_LEN] + 2 + 1 >= 308) {
		LOG(LOG_ERR, "Option 0x%02x did not fit into the packet!", string[OPT_CODE]);
		return 0;
	}
	DEBUG(LOG_INFO, "adding option 0x%02x", string[OPT_CODE]);
	memcpy(optionptr + end, string, string[OPT_LEN] + 2);
	optionptr[end + string[OPT_LEN] + 2] = DHCP_END;
	return string[OPT_LEN] + 2;
}
#ifdef __SC_BUILD__
int add_options_directly(unsigned char *optionptr, unsigned char code, char *data, unsigned int length)
{

	unsigned char option[2 + length];

	option[OPT_CODE] = code;
	option[OPT_LEN] = length;
	memcpy(option + 2, data, length);
	return add_option_string(optionptr, option);
}
#endif
/* add a one to four byte option to a packet */
int add_simple_option(unsigned char *optionptr, unsigned char code, u_int32_t data)
{
	char length = 0;
	int i;
	unsigned char option[2 + 4];
	unsigned char *u8;
	u_int16_t *u16;
	u_int32_t *u32;
	u_int32_t aligned;
	u8 = (unsigned char *) &aligned;
	u16 = (u_int16_t *) &aligned;
	u32 = &aligned;

	for (i = 0; options[i].code; i++)
		if (options[i].code == code) {
			length = option_lengths[options[i].flags & TYPE_MASK];
		}

	if (!length) {
		DEBUG(LOG_ERR, "Could not add option 0x%02x", code);
		return 0;
	}

	option[OPT_CODE] = code;
	option[OPT_LEN] = length;

	switch (length) {
		case 1: *u8 =  data; break;
		case 2: *u16 = data; break;
		case 4: *u32 = data; break;
	}
	memcpy(option + 2, &aligned, length);
	return add_option_string(optionptr, option);
}


/* find option 'code' in opt_list */
struct option_set *find_option(struct option_set *opt_list, char code)
{
	while (opt_list && opt_list->data[OPT_CODE] < code)
		opt_list = opt_list->next;

	if (opt_list && opt_list->data[OPT_CODE] == code) return opt_list;
	else return NULL;
}

static int parse_dhcp_option_sip(char *src_buf, int src_len, char *sip_buf)
{
    int sip_len = 0;

    if (isdigit(*src_buf))
    {
        sip_buf[sip_len++] = 1; // encoding ip list
        struct in_addr addr;
        char delim[2] = ";";
        char *ip = strtok(src_buf, delim);
        while (ip)
        {
            if (inet_aton(ip, &addr))
            {
                memcpy(sip_buf + sip_len, (char *)&addr, sizeof(struct in_addr));
                sip_len += sizeof(struct in_addr);
            }
            ip = strtok(NULL, delim);
        }
    }
    else
    {
        sip_buf[sip_len++] = 0; // encoding domain name
        char delim[2] = ";";
        char *domain = strtok(src_buf, delim);
        while (domain)
        {
            char *pos = domain;
            char *str;
            while ((str = strchr(pos, '.')) && *pos != '\0')
            {
                sip_buf[sip_len++] = str - pos;
                memcpy(sip_buf + sip_len, pos, str - pos);
                sip_len += str - pos;
                pos = str + 1;
            }
            if (*pos != '\0')
            {
                sip_buf[sip_len++] = strlen(pos);
                memcpy(sip_buf + sip_len, pos, strlen(pos));
                sip_len += strlen(pos);
            }
            sip_buf[sip_len++] = 0; // one end
            domain = strtok(NULL, delim);
        }
    }

    return sip_len;
}

/* add an option to the opt_list */
void attach_option(struct option_set **opt_list, struct dhcp_option *option, char *buffer, int length)
{
	struct option_set *existing, *new, **curr;

	/* add it to an existing option */
	if ((existing = find_option(*opt_list, option->code))) {
		DEBUG(LOG_INFO, "Attaching option %s to existing member of list", option->name);
		if (option->flags & OPTION_LIST) {
			if (existing->data[OPT_LEN] + length <= 255) {
				existing->data = realloc(existing->data, 
						existing->data[OPT_LEN] + length + 2);
				memcpy(existing->data + existing->data[OPT_LEN] + 2, buffer, length);
				existing->data[OPT_LEN] += length;
			} /* else, ignore the data, we could put this in a second option in the future */
		} /* else, ignore the new data */
	} else {
		DEBUG(LOG_INFO, "Attaching option %s to list", option->name);
		
        char *opt;
	    int opt_len;
	    char sip_buf[300] = "";

	    if (DHCP_SIP_SERVERS == option->code)
	    {
	        opt = sip_buf;
	        opt_len = parse_dhcp_option_sip(buffer, length, sip_buf);
	    }
	    else
	    {
            opt = buffer;
            opt_len = length;
        }
		/* make a new option */
		new = malloc(sizeof(struct option_set));
		new->data = malloc(opt_len + 2);
		new->data[OPT_CODE] = option->code;
		new->data[OPT_LEN] = opt_len;
		memcpy(new->data + 2, opt, opt_len);
		
		curr = opt_list;
		while (*curr && (*curr)->data[OPT_CODE] < option->code)
			curr = &(*curr)->next;
			
		new->next = *curr;
		*curr = new;		
	}
}

#ifdef __SC_BUILD__
/*send event when reveiced packets from dhcp server*/
void  sc_send_client_options(struct dhcpMessage *packet)
{
    unsigned char *temp54, *temp15;
    unsigned long server_addr;
    struct sc_event_msg *sc_evt_msg = NULL;
    struct sc_dhcp_client_option *sc_client_opts = NULL;
    int evt_len = 0, option_len = 0;
    char *name = "dhcpv4_client";

    evt_len = 64+sizeof(struct sc_dhcp_client_option);
    sc_evt_msg = malloc(evt_len);
    sc_client_opts = malloc(sizeof(struct sc_dhcp_client_option));

    //get dhcp server id
    if ((temp54 = get_option(packet, DHCP_SERVER_ID))) 
    {
        struct in_addr temp_addr;
        memcpy(&server_addr, temp54, 4);
        temp_addr.s_addr = server_addr;
        snprintf(sc_client_opts->option54, 9, "%4X", temp_addr.s_addr );
    }

    //get domain name
    if ((temp15 = get_option_x(packet, DHCP_DOMAIN_NAME, &option_len))) 
    {
        if(option_len > 127)
            option_len = 127;
        memcpy(sc_client_opts->option15, temp15, option_len);
        sc_client_opts->option15[option_len] = '\0';
    }

    strcpy(sc_evt_msg->name, name);
    memcpy((struct sc_dhcp_client_option *)sc_evt_msg->buf, sc_client_opts, sizeof(struct sc_dhcp_client_option));
    //send event
    sc_event(sc_evt_msg, evt_len);

    if(sc_evt_msg)
        free(sc_evt_msg);
    if(sc_client_opts)
        free(sc_client_opts);
}
#endif

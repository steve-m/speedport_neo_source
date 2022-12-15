/*
 * files.c -- DHCP server file manipulation *
 * Rewrite by Russ Dill <Russ.Dill@asu.edu> July 2001
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <netdb.h>
#include <fcntl.h>
#ifdef __SC_BUILD__
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/ether.h>
#include "snbd_cmd.h"
#endif

#include "debug.h"
#include "dhcpd.h"
#include "pidfile.h"
#include "files.h"
#include "socket.h"
#include "options.h"
#include "leases.h"
#include "static_leases.h"
#include "option_action.h"

/* on these functions, make sure you datatype matches */
static int read_ip(char *line, void *arg)
{
    struct in_addr *addr = arg;
    struct hostent *host;
    int retval = 1;

    if (!inet_aton(line, addr)) {
#ifdef __SC_BUILD__
        if (strlen(line) && (host = gethostbyname(line)))
#else
            if ((host = gethostbyname(line))) 
#endif
                addr->s_addr = *((unsigned long *) host->h_addr_list[0]);
            else retval = 0;
    }
    return retval;
}
#ifdef __SC_BUILD__
static void add_to_ip_list(struct dhcp_ip_list_s **list, struct dhcp_ip_list_s *ip_node)
{
    struct dhcp_ip_list_s *cur = NULL;

    if (NULL == *list)
        *list = ip_node;
    else
    {
        cur = *list;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = ip_node;
    }
}

static int read_ip_list(char *line, void *arg)
{
    struct in_addr addr;
    struct dhcp_ip_list_s *ip_node = NULL;

    if (inet_aton(line, &addr))
    {
        ip_node = (struct dhcp_ip_list_s *)malloc(sizeof(struct dhcp_ip_list_s));
        if (ip_node)
        {
            ip_node->ip = addr.s_addr;
            ip_node->next = NULL;
            add_to_ip_list(arg, ip_node);
        }
    }
    return 1;
}

static int read_mac(const char *line, void *arg)
{
    uint8_t *mac_bytes = arg;
    struct ether_addr *temp_ether_addr;
    int retval = 1;

    temp_ether_addr = ether_aton(line);

    if(temp_ether_addr == NULL)
        retval = 0;
    else
        memcpy(mac_bytes, temp_ether_addr, 6);

    return retval;
}
#endif

static int read_str(char *line, void *arg)
{
    char **dest = arg;

    if (*dest) free(*dest);
    *dest = strdup(line);

    return 1;
}


static int read_u32(char *line, void *arg)
{
    u_int32_t *dest = arg;
    char *endptr;
    *dest = strtoul(line, &endptr, 0);
    return endptr[0] == '\0';
}


static int read_yn(char *line, void *arg)
{
    char *dest = arg;
    int retval = 1;

    if (!strcasecmp("yes", line))
        *dest = 1;
    else if (!strcasecmp("no", line))
        *dest = 0;
    else retval = 0;

    return retval;
}


/* read a dhcp option and add it to opt_list */
static int read_opt(char *line, void *arg)
{
    struct option_set **opt_list = arg;
    char *opt, *val, *endptr;
    struct dhcp_option *option = NULL;
    int retval = 0, length = 0;
    char buffer[255];
    u_int16_t result_u16;
    u_int32_t result_u32;
    int i;
#ifdef __SC_BUILD__
    int j;
    unsigned char hex[2];
    unsigned char *hex_buf;
#endif
    if (!(opt = strtok(line, " \t="))) return 0;

    for (i = 0; options[i].code; i++)
        if (!strcmp(options[i].name, opt))
            option = &(options[i]);

    if (!option) return 0;

    do {
        val = strtok(NULL, ",\t"); // keep space in val, old: ", \t"
        if (val) {
            length = option_lengths[option->flags & TYPE_MASK];
            retval = 0;
            switch (option->flags & TYPE_MASK) {
            case OPTION_IP:
                retval = read_ip(val, buffer);
                break;
            case OPTION_IP_PAIR:
                retval = read_ip(val, buffer);
                if (!(val = strtok(NULL, ", \t/-"))) retval = 0;
                if (retval) retval = read_ip(val, buffer + 4);
                break;
            case OPTION_STRING:
                length = strlen(val);
                if (length > 0) {
                    if (length > 254) length = 254;
                    memcpy(buffer, val, length);
                    buffer[length] = '\0';
                    retval = 1;
                }
                break;
#ifdef __SC_BUILD__
            case OPTION_HEX:
                length = strlen(val)/2-1; // if odd, ignore last hex
                if(length > 0){
                    if (length > 254) length = 254;
                    if(strncmp(val, "0x", 2)==0)
                    {
                        val = val + 2;
                        hex_buf = (unsigned char*)malloc(length);
                        bzero(hex_buf, length);
                        for(i=0; i<length; i++, val+=2)
                        {
                            for(j=0; j<2; j++)
                            {
                                if(*(val+j)>='0'&&*(val+j)<='9')
                                    hex[j] = *(val+j) - '0';
                                else if(*(val+j)>='a'&&*(val+j)<='f')
                                    hex[j] = *(val+j) - 'a' + 10;
                                else if(*(val+j)>='A'&&*(val+j)<='F')
                                    hex[j] = *(val+j) - 'A' + 10;
                                else // incorrect hex format
                                {
                                    buffer[0] = '\0';
                                    free(hex_buf);
                                    return 0;
                                }
                            }
                            *(hex_buf+i) = ( ( (hex[0]<<4)&0xF0) | (hex[1]&0x0F) );
                        }
                        memcpy(buffer, hex_buf, length);
                        free(hex_buf);
                        retval = 1;
                    }
                }
                break;
#endif
            case OPTION_BOOLEAN:
                retval = read_yn(val, buffer);
                break;
            case OPTION_U8:
                buffer[0] = strtoul(val, &endptr, 0);
                retval = (endptr[0] == '\0');
                break;
            case OPTION_U16:
                result_u16 = htons(strtoul(val, &endptr, 0));
                memcpy(buffer, &result_u16, 2);
                retval = (endptr[0] == '\0');
                break;
            case OPTION_S16:
                result_u16 = htons(strtol(val, &endptr, 0));
                memcpy(buffer, &result_u16, 2);
                retval = (endptr[0] == '\0');
                break;
            case OPTION_U32:
                result_u32 = htonl(strtoul(val, &endptr, 0));
                memcpy(buffer, &result_u32, 4);
                retval = (endptr[0] == '\0');
                break;
            case OPTION_S32:
                result_u32 = htonl(strtol(val, &endptr, 0));
                memcpy(buffer, &result_u32, 4);
                retval = (endptr[0] == '\0');
                break;
            default:
                break;
            }
            if (retval)
                attach_option(opt_list, option, buffer, length);
        };
    } while (val && retval && option->flags & OPTION_LIST);
    return retval;
}
#ifdef __SC_BUILD__
static int read_staticlease(char *const_line, void *arg)
{

    char *line;
    char *mac_string;
    char *ip_string;
    uint8_t *mac_bytes;
    uint32_t *ip;


    /* Allocate memory for addresses */
    mac_bytes = malloc(sizeof(unsigned char) * 8);
    ip = malloc(sizeof(uint32_t));

    /* Read mac */
    line = (char *) const_line;
    mac_string = strtok(line, " \t");
    read_mac(mac_string, mac_bytes);

    /* Read ip */
    ip_string = strtok(NULL, " \t");
    read_ip(ip_string, ip);

    addStaticLease(arg, mac_bytes, ip);

#ifdef UDHCP_DEBUG
    printStaticLeases(arg);
#endif

    return 1;

}
#endif


#ifdef __SC_BUILD__
static int list_add_in_trail(struct option_arg_s **head, struct option_arg_s *newp)
{
    struct option_arg_s *cur;

    if(*head == NULL)
    {
        *head = newp;
    }
    else
    {
        cur = *head;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = newp;
    }
    return 1;
}

static int read_client_option_info(char *const_line, void *arg)
{
    struct client_option_s **client_option = arg;
    struct client_option_s *cur;
    struct client_option_s *new_client_option;
    //struct option_arg_s    *arg;
    char buf[256] = "";
    char *line;
    char *offer_string;
    char *file_string;
    char *script_string;
    char *num_string;
    char *opt_arg;
    int len;
    int i;

    new_client_option = malloc(sizeof(struct client_option_s));
    if (!new_client_option) {
        //show_info("can not alloc space for new_client_option\n");
        return -1;
    }
    memset(new_client_option, 0, sizeof(struct client_option_s));

    line = (char *) const_line;
    len = strlen(line);

    offer_string = strtok(line, " \t");
    new_client_option->offer = strdup(offer_string);

    file_string = strtok(NULL, " \t");
    new_client_option->file = strdup(file_string);

    script_string = strtok(NULL, " \t");
    new_client_option->script.file = strdup(script_string);

    num_string = strtok(NULL, " \t");
    new_client_option->script.arg_num = atoi(strdup(num_string));

    new_client_option->script.arg = NULL;
    for (i = 0; i < new_client_option->script.arg_num; i++)
    {
        arg = malloc(sizeof(struct option_arg_s));
        if (!arg) {
            //show_info("can not alloc space for option_arg_s\n");
            continue;
        }
        memset(arg, 0, sizeof(struct option_arg_s));
        opt_arg = strtok(NULL, " \t");
        ((struct option_arg_s *)arg)->value = strdup(opt_arg);
        ((struct option_arg_s *)arg)->next = NULL;
        list_add_in_trail(&new_client_option->script.arg, arg);
    }

    new_client_option->opt_value = NULL;
    if (0 == i)
        opt_arg = num_string;
    len = (line + len) - (opt_arg + strlen(opt_arg) + 1);
    if (len >= 1)
    {
        memcpy(buf, (opt_arg + strlen(opt_arg) + 1), len);
        buf[len] = '\0';
        opt_arg = buf;
        while (*opt_arg == ' ' || *opt_arg == '\t')
            opt_arg++;
        new_client_option->opt_value = malloc(strlen(opt_arg) + 1);
        if (new_client_option->opt_value)
        {
            memcpy(new_client_option->opt_value, opt_arg, strlen(opt_arg) + 1);
            len = strlen(new_client_option->opt_value);
            while (new_client_option->opt_value[len - 1] == ' '
                   || new_client_option->opt_value[len - 1] == '\t')
            {
                new_client_option->opt_value[len - 1] = '\0';
                len--;
            }
        }
    }

    new_client_option->next = NULL;
    if(*client_option == NULL)
    {
        *client_option = new_client_option;
    }
    else
    {
        cur = *client_option;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_client_option;
    }
    return 1;
}

static int read_pipe_option_info(char *const_line, void *arg)
{
    struct pipe_option_s **pipe_option = arg;
    struct pipe_option_s *p;
    struct pipe_option_s *cur;
    //struct option_arg_s  *arg;
    char *line;
    char *pipe_string;
    char *mode_string;
    char *cmd_string;
    char *pipe;
    char *mode;
    char *cmd;
    char *session_string;
    char *session;
    char *client_string;
    char *dns_string;
    char *client;
    char *client_mask_string;
    char *client_mask;
    char *dns;
    char *id = NULL;
    char *opt_arg;
    char buf[256] = "";
    int new_flag = 0;
    int len;

    line = (char *) const_line;
    len = strlen(line);
    pipe_string = strtok(line, " \t");
    pipe = strdup(pipe_string);

    session_string = strtok(NULL, " \t");
    session = strdup(session_string);

    mode_string = strtok(NULL, " \t");
    mode = strdup(mode_string);

    cmd_string = strtok(NULL, "\t");
    cmd = strdup(cmd_string);

    client_string = strtok(NULL, " \t");

    client = malloc(sizeof(unsigned char) * 8);
    read_mac(client_string, client);


    client_mask_string = strtok(NULL, " \t");
    client_mask = malloc(sizeof(unsigned char) * 8);
    read_mac(client_mask_string, client_mask);

    dns_string = strtok(NULL, " \t");
    dns = strdup(dns_string);

    int counter = 0;

    char *temp = dns;
    char *ret;
    char *dnsList;
    while((ret = index(temp, ':')) != NULL)
    {
        counter++;
        ret++;
        temp = ret;
    }
    counter++;

    dnsList = malloc(sizeof(uint32_t) * counter + 2);
    dnsList[0] = DHCP_DNS_SERVER;
    dnsList[1] = sizeof(uint32_t) * counter;
    uint32_t *tempB = (uint32_t *)&dnsList[2];
    temp = dns;
    while((ret = index(temp, ':')) != NULL)
    {
        *ret = '\0';
        read_ip(temp, tempB);
        ret++;
        tempB++;
        temp = ret;
    }
    read_ip(temp, tempB);
    free(dns);
    opt_arg = dns_string;
    len = (line + len) - (opt_arg + strlen(opt_arg));
    if (len >= 0)
    {
        memcpy(buf, (opt_arg + strlen(opt_arg) + 1), len);
        buf[len] = '\0';
        opt_arg = buf;
        while (*opt_arg == ' ' || *opt_arg == '\t')
            opt_arg++;
        id = malloc(strlen(opt_arg) + 1);
        if (id)
        {
            memcpy(id, opt_arg, strlen(opt_arg) + 1);
            len = strlen(id);
            while (id[len - 1] == ' ' || id[len - 1] == '\t')
            {
                id[len - 1] = '\0';
                len--;
            }
        }
    }

    p = *pipe_option;
    while(p)
    {
        if ((strcmp(p->name, pipe) == 0) && (strcmp(p->session, session) == 0))
            break;
        p = p->next;
    }
    if (!p)
    {
        p = malloc(sizeof(struct pipe_option_s));
        if (!p)
            return -1;
        memset(p, 0, sizeof(struct pipe_option_s));
        new_flag = 1;
    }
    p->name = pipe;
    p->mode = mode;
    p->session = session;
    p->cmd = cmd;

    p->clientID.len = 6;
    p->clientID.value = client;

    p->clientMask.len = 6;
    p->clientMask.value = client_mask;

    p->dns.len = sizeof(uint32_t) * counter + 2;
    p->dns.value = dnsList;

    if(id)
    {
        arg = malloc(sizeof(struct option_arg_s));
        if (!arg)
            return -1;
        memset(arg, 0, sizeof(struct option_arg_s));
        ((struct option_arg_s *)arg)->value = id;
        ((struct option_arg_s *)arg)->next = NULL;
        list_add_in_trail(&p->arg, arg);
    }
    if (1 == new_flag)
    {
        p->next = NULL;
        if(*pipe_option == NULL)
        {
            *pipe_option = p;
        }
        else
        {
            cur = *pipe_option;
            while(cur->next != NULL)
            {
                cur = cur->next;
            }
            cur->next = p;
        }
    }
    return 1;
}

/*static int read_client_vendor_info(char *const_line, void *arg)
  {

  char *line;
  char *pipe_string;
  char *mode_string;
  char *id_string;
  char *pipe;
  char *mode;
  char *id;

  line = (char *) const_line;
  pipe_string = strtok(line, " \t");

  pipe = strdup(pipe_string);
  mode_string = strtok(NULL, " \t");
  mode = strdup(mode_string);
  id_string = strtok(NULL, " \t");
  id = strdup(id_string);

  add_vendor_id(arg, pipe, mode, id);
  return 1;
  }*/


static struct config_kw_arr k_arr[MAX_INTERFACES] = {
    {/* keyword[14]	handler   variable address		default[20] */
        {
            {"server",	read_ip,  &(server_config[0].server),	"192.168.0.1"},
            {"start",	read_ip,  &(server_config[0].start),	"192.168.0.2"},
            {"end",		read_ip,  &(server_config[0].end),		"192.168.0.254"},
            {"interface",	read_str, &(server_config[0].interface),	"br0"},
            {"cds_enable",  read_str, &(server_config[0].cds_enable),	"0"},
            {"vendor_bind", read_str, &(server_config[0].vendor_bind),	""},
            {"mac_bind", read_str, &(server_config[0].mac_bind),	""},
#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
            {"brg_port_bind", read_u32, &(server_config[0].brg_port_bind), ""},
#endif
            {"wan_bind", read_str, &(server_config[0].wan_bind),	""},
            {"dns_proxy", read_str, &(server_config[0].dns_proxy),	"1"},
            {"dns_server", read_ip_list, &(server_config[0].dns_server),	""},
            {"option",	read_opt, &(server_config[0].options),	""},
            {"opt",		read_opt, &(server_config[0].options),	""},
            {"max_leases",	read_u32, &(server_config[0].max_leases),	"254"},
            {"remaining",	read_yn,  &(server_config[0].remaining),	"yes"},
            {"auto_time",	read_u32, &(server_config[0].auto_time),	"1"/*"7200"*/},
            {"decline_time",read_u32, &(server_config[0].decline_time),"3600"},
            {"conflict_time",read_u32,&(server_config[0].conflict_time),"3600"},
            {"offer_time",	read_u32, &(server_config[0].offer_time),	"60"},
            {"min_lease",	read_u32, &(server_config[0].min_lease),	"60"},
            {"lease_file",	read_str, &(server_config[0].lease_file),	"/var/udhcpd.leases"},
            {"pidfile",	read_str, &(server_config[0].pidfile),	"/var/run/udhcpd.pid"},
            {"notify_file", read_str, &(server_config[0].notify_file),	""},
            {"siaddr",	read_ip,  &(server_config[0].siaddr),	"0.0.0.0"},
            {"sname",	read_str, &(server_config[0].sname),	""},
            {"boot_file",	read_str, &(server_config[0].boot_file),	""},
            {"static_lease",read_staticlease, &(server_config[0].static_leases),	""},
            {"pipe",read_pipe_option_info, &(server_config[0].pipe),	""},
            {"vendor_id",read_client_option_info, &(vendor_header),	""},
            {"client_id",read_client_option_info, &(client_header),	""},
            {"user_class_id",read_client_option_info, &(user_class_header),	""},
#ifdef TR069
            {"oui", read_str, &(server_config[0].manufacturer_oui),	""},
            {"serial_number",    read_str, &(server_config[0].serial_number),	""},
            {"model_name",       read_str, &(server_config[0].model_name),	""},
#endif
            /*ADDME: static lease */}},
    {/* keyword[14]	handler   variable address		default[20] */
        {
            {"server",	read_ip,  &(server_config[1].server),	"192.168.0.1"},
            {"start",	read_ip,  &(server_config[1].start),	"192.168.0.2"},
            {"end",		read_ip,  &(server_config[1].end),		"192.168.0.254"},
            {"interface",	read_str, &(server_config[1].interface),	"br0"},
            {"cds_enable",  read_str, &(server_config[1].cds_enable),	"1"},
            {"vendor_bind", read_str, &(server_config[1].vendor_bind),	""},
            {"mac_bind", read_str, &(server_config[1].mac_bind),	""},
#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
            {"brg_port_bind", read_u32, &(server_config[1].brg_port_bind), ""},
#endif
            {"wan_bind", read_str, &(server_config[1].wan_bind),	""},
            {"dns_proxy", read_str, &(server_config[1].dns_proxy),	"1"},
            {"dns_server", read_ip_list, &(server_config[1].dns_server),	""},
            {"option",	read_opt, &(server_config[1].options),	""},
            {"opt",		read_opt, &(server_config[1].options),	""},
            {"max_leases",	read_u32, &(server_config[1].max_leases),	"254"},
            {"remaining",	read_yn,  &(server_config[1].remaining),	"yes"},
            {"auto_time",	read_u32, &(server_config[1].auto_time),	"1"/*"7200"*/},
            {"decline_time",read_u32, &(server_config[1].decline_time),"3600"},
            {"conflict_time",read_u32,&(server_config[1].conflict_time),"3600"},
            {"offer_time",	read_u32, &(server_config[1].offer_time),	"60"},
            {"min_lease",	read_u32, &(server_config[1].min_lease),	"60"},
            {"lease_file",	read_str, &(server_config[1].lease_file),	"/var/udhcpd1.leases"},
            {"pidfile",	read_str, &(server_config[1].pidfile),	"/var/run/udhcpd.pid"},
            {"notify_file", read_str, &(server_config[1].notify_file),	""},
            {"siaddr",	read_ip,  &(server_config[1].siaddr),	"0.0.0.0"},
            {"sname",	read_str, &(server_config[1].sname),	""},
            {"boot_file",	read_str, &(server_config[1].boot_file),	""},
            {"static_lease",read_staticlease, &(server_config[1].static_leases),	""},
            {"pipe",read_pipe_option_info, &(server_config[1].pipe),	""},
            {"vendor_id",read_client_option_info, &(vendor_header),	""},
            {"client_id",read_client_option_info, &(client_header),	""},
            {"user_class_id",read_client_option_info, &(user_class_header),	""},
#ifdef TR069
            {"oui", read_str, &(server_config[1].manufacturer_oui),	""},
            {"serial_number",    read_str, &(server_config[1].serial_number),	""},
            {"model_name",       read_str, &(server_config[1].model_name),	""},
#endif

        }},
    {/* keyword[14]	handler   variable address		default[20] */
        {
            {"server",	read_ip,  &(server_config[2].server),	"192.168.0.1"},
            {"start",	read_ip,  &(server_config[2].start),	"192.168.0.2"},
            {"end",		read_ip,  &(server_config[2].end),		"192.168.0.254"},
            {"interface",	read_str, &(server_config[2].interface),	"br0"},
            {"cds_enable",  read_str, &(server_config[2].cds_enable),	"1"},
            {"vendor_bind", read_str, &(server_config[2].vendor_bind),	""},
            {"mac_bind", read_str, &(server_config[2].mac_bind),	""},
#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
            {"brg_port_bind", read_u32, &(server_config[2].brg_port_bind), ""},
#endif
            {"wan_bind", read_str, &(server_config[2].wan_bind),	""},
            {"dns_proxy", read_str, &(server_config[2].dns_proxy),	"1"},
            {"dns_server", read_ip_list, &(server_config[2].dns_server),	""},
            {"option",	read_opt, &(server_config[2].options),	""},
            {"opt",		read_opt, &(server_config[2].options),	""},
            {"max_leases",	read_u32, &(server_config[2].max_leases),	"254"},
            {"remaining",	read_yn,  &(server_config[2].remaining),	"yes"},
            {"auto_time",	read_u32, &(server_config[2].auto_time),	"1"/*"7200"*/},
            {"decline_time",read_u32, &(server_config[2].decline_time),"3600"},
            {"conflict_time",read_u32,&(server_config[2].conflict_time),"3600"},
            {"offer_time",	read_u32, &(server_config[2].offer_time),	"60"},
            {"min_lease",	read_u32, &(server_config[2].min_lease),	"60"},
            {"lease_file",	read_str, &(server_config[2].lease_file),	"/var/udhcpd2.leases"},
            {"pidfile",	read_str, &(server_config[2].pidfile),	"/var/run/udhcpd.pid"},
            {"notify_file", read_str, &(server_config[2].notify_file),	""},
            {"siaddr",	read_ip,  &(server_config[2].siaddr),	"0.0.0.0"},
            {"sname",	read_str, &(server_config[2].sname),	""},
            {"boot_file",	read_str, &(server_config[2].boot_file),	""},
            {"static_lease",read_staticlease, &(server_config[2].static_leases),	""},
            {"pipe",read_pipe_option_info, &(server_config[2].pipe),	""},
            {"vendor_id",read_client_option_info, &(vendor_header),	""},
            {"client_id",read_client_option_info, &(client_header),	""},
            {"user_class_id",read_client_option_info, &(user_class_header),	""},
#ifdef TR069
            {"oui", read_str, &(server_config[2].manufacturer_oui),	""},
            {"serial_number",    read_str, &(server_config[2].serial_number),	""},
            {"model_name",       read_str, &(server_config[2].model_name),	""},
#endif

        }},
    {/* keyword[14]	handler   variable address		default[20] */
        {
            {"server",	read_ip,  &(server_config[3].server),	"192.168.0.1"},
            {"start",	read_ip,  &(server_config[3].start),	"192.168.0.2"},
            {"end",		read_ip,  &(server_config[3].end),		"192.168.0.254"},
            {"interface",	read_str, &(server_config[3].interface),	"br0"},
            {"cds_enable",  read_str, &(server_config[3].cds_enable),	"1"},
            {"vendor_bind", read_str, &(server_config[3].vendor_bind),	""},
            {"mac_bind", read_str, &(server_config[3].mac_bind),	""},
#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
            {"brg_port_bind", read_u32, &(server_config[3].brg_port_bind), ""},
#endif
            {"wan_bind", read_str, &(server_config[3].wan_bind),	""},
            {"dns_proxy", read_str, &(server_config[3].dns_proxy),	"1"},
            {"dns_server", read_ip_list, &(server_config[3].dns_server),	""},
            {"option",	read_opt, &(server_config[3].options),	""},
            {"opt",		read_opt, &(server_config[3].options),	""},
            {"max_leases",	read_u32, &(server_config[3].max_leases),	"254"},
            {"remaining",	read_yn,  &(server_config[3].remaining),	"yes"},
            {"auto_time",	read_u32, &(server_config[3].auto_time),	"1"/*"7200"*/},
            {"decline_time",read_u32, &(server_config[3].decline_time),"3600"},
            {"conflict_time",read_u32,&(server_config[3].conflict_time),"3600"},
            {"offer_time",	read_u32, &(server_config[3].offer_time),	"60"},
            {"min_lease",	read_u32, &(server_config[3].min_lease),	"60"},
            {"lease_file",	read_str, &(server_config[3].lease_file),	"/var/udhcpd3.leases"},
            {"pidfile",	read_str, &(server_config[3].pidfile),	"/var/run/udhcpd.pid"},
            {"notify_file", read_str, &(server_config[3].notify_file),	""},
            {"siaddr",	read_ip,  &(server_config[3].siaddr),	"0.0.0.0"},
            {"sname",	read_str, &(server_config[3].sname),	""},
            {"boot_file",	read_str, &(server_config[3].boot_file),	""},
            {"static_lease",read_staticlease, &(server_config[3].static_leases),	""},
            {"pipe",read_pipe_option_info, &(server_config[3].pipe),	""},
            {"vendor_id",read_client_option_info, &(vendor_header),	""},
            {"client_id",read_client_option_info, &(client_header),	""},
            {"user_class_id",read_client_option_info, &(user_class_header),	""},
#ifdef TR069
            {"oui", read_str, &(server_config[3].manufacturer_oui),	""},
            {"serial_number",    read_str, &(server_config[3].serial_number),	""},
            {"model_name",       read_str, &(server_config[3].model_name),	""},
#endif

        }}
};

int read_config(char *file)
{
    FILE *in;
    char buffer[500], orig[500], *token, *line;
    int i, j, index;
    int fd = -1;
    struct flock flockptr = {.l_type = F_RDLCK,
        .l_start = 0,
        .l_whence = SEEK_SET,
        .l_len = 0
    };

    /* fopen file, wait up to 3s */
    i = 0;
    while (1)
    {
        in = fopen(file, "r");
        if (in)
            break;
        i++;
        if (i > 3)
        {
            return 0;
        }
        sleep(1);
    }
    /* lock file */
    fd = fileno(in);
    if(fcntl(fd, F_SETLKW, &flockptr) < 0)
    {
        fclose(in);
        return 0;
    }
    for (index = 0; index < MAX_INTERFACES; index++)
        for (j = 0; j < MAX_KEYWORDS; j++)
            if (strlen(k_arr[index].keywords[j].def))
                k_arr[index].keywords[j].handler(k_arr[index].keywords[j].def, k_arr[index].keywords[j].var);


    index = -1;
    while (fgets(buffer, 500, in)) {
        if (strchr(buffer, '\n')) *(strchr(buffer, '\n')) = '\0';
        strncpy(orig, buffer, 500);
        //if (strchr(buffer, '#')) *(strchr(buffer, '#')) = '\0';
        token = buffer + strspn(buffer, " \t");
        if (*token == '\0') continue;
        line = token + strcspn(token, " \t=");
        if (*line == '\0') continue;
        *line = '\0';
        line++;

        /* eat leading whitespace */
        line = line + strspn(line, " \t=");
        /* eat trailing whitespace */
        for (i = strlen(line) ; i > 0 && isspace(line[i-1]); i--);
        line[i] = '\0';

        for (j = 0; j < MAX_KEYWORDS; j++)
        {

            if (!strcasecmp(token, "server")) {
                index++;
            }

            if (index>-1&&!strcasecmp(token, k_arr[index].keywords[j].keyword)) {
                if (!k_arr[index].keywords[j].handler(line, k_arr[index].keywords[j].var)) {
                    LOG(LOG_ERR, "unable to parse '%s'", orig);
                    /* reset back to the default value */
                    k_arr[index].keywords[j].handler(k_arr[index].keywords[j].def, k_arr[index].keywords[j].var);
                }
                break;
            }
        }
    }
    no_of_ifaces = index+1;
    /* unlock file */
    flockptr.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW,&flockptr);

    fclose(in);
    return 1;
}

static void free_client_option(struct client_option_s *client_option)
{
    struct client_option_s *opt;
    struct client_option_s *opt_next;
    struct option_arg_s *arg;
    struct option_arg_s *arg_next;

    opt = client_option;
    while (opt)
    {
        opt_next = opt->next;
        if (opt->offer)
            free(opt->offer);
        if (opt->file)
            free(opt->file);
        if (opt->opt_value)
            free(opt->opt_value);
        if (opt->script.file)
            free(opt->script.file);
        arg = opt->script.arg;
        while (arg)
        {
            arg_next = arg->next;
            if (arg->value)
            {
                free(arg->value);
            }
            free(arg);
            arg = arg_next;
        }
        free(opt);
        opt = opt_next;
    }
}

static void free_server_config_malloc(struct server_config_t *cfg)
{
    struct option_set *options;
    struct option_set *options_next;
    struct static_lease *static_leases;
    struct static_lease *static_leases_next;
    struct pipe_option_s *pipe;
    struct pipe_option_s *pipe_next;
    struct option_arg_s *arg;
    struct option_arg_s *arg_next;
    struct dhcp_ip_list_s *ip_list;
    struct dhcp_ip_list_s *ip_list_next;

    options = cfg->options;
    while (options)
    {
        options_next = options->next;
        if (options->data)
            free(options->data);
        free(options);
        options = options_next;
    }

    if (cfg->interface)
        free(cfg->interface);
    if (cfg->lease_file)
        free(cfg->lease_file);
    if (cfg->pidfile)
        free(cfg->pidfile);
    if (cfg->notify_file)
        free(cfg->notify_file);
    if (cfg->sname)
        free(cfg->sname);
    if (cfg->boot_file)
        free(cfg->boot_file);
    if (cfg->vendor_bind)
        free(cfg->vendor_bind);
    if (cfg->mac_bind)
        free(cfg->mac_bind);
    if (cfg->wan_bind)
        free(cfg->wan_bind);
    if (cfg->dns_proxy)
        free(cfg->dns_proxy);
    if (cfg->cds_enable)
        free(cfg->cds_enable);

    ip_list = cfg->dns_server;
    while (ip_list)
    {
        ip_list_next = ip_list->next;
        free(ip_list);
        ip_list = ip_list_next;
    }

    static_leases = cfg->static_leases;
    while (static_leases)
    {
        static_leases_next = static_leases->next;
        if (static_leases->mac)
            free(static_leases->mac);
        if (static_leases->ip)
            free(static_leases->ip);
        free(static_leases);
        static_leases = static_leases_next;
    }

    pipe = cfg->pipe;
    while (pipe)
    {
        pipe_next = pipe->next;
        if (pipe->name)
        {
            free(pipe->name);
            pipe->name = NULL;
        }
        if (pipe->session)
        {
            free(pipe->session);
            pipe->session = NULL;
        }
        if (pipe->mode)
        {
            free(pipe->mode);
            pipe->mode = NULL;
        }
        if (pipe->cmd)
        {
            free(pipe->cmd);
            pipe->cmd = NULL;
        }

        if(pipe->clientID.value)
        {
            free(pipe->clientID.value);
            pipe->clientID.value = NULL;
        }
        if(pipe->clientMask.value)
        {
            free(pipe->clientMask.value);
            pipe->clientMask.value = NULL;
        }
        if(pipe->dns.value)
        {
            free(pipe->dns.value);
            pipe->dns.value = NULL;
        }
        arg = pipe->arg;
        while (arg)
        {
            arg_next = arg->next;
            if (arg->value)
                free(arg->value);
            free(arg);
            arg = arg_next;
        }
        free(pipe);
        pipe = pipe_next;
    }

}
#else
static struct config_keyword keywords[] = {
    /* keyword[14]	handler   variable address		default[20] */
    {"start",	read_ip,  &(server_config.start),	"192.168.0.20"},
    {"end",		read_ip,  &(server_config.end),		"192.168.0.254"},
    {"interface",	read_str, &(server_config.interface),	"eth0"},
    {"option",	read_opt, &(server_config.options),	""},
    {"opt",		read_opt, &(server_config.options),	""},
    {"max_leases",	read_u32, &(server_config.max_leases),	"254"},
    {"remaining",	read_yn,  &(server_config.remaining),	"yes"},
    {"auto_time",	read_u32, &(server_config.auto_time),	"7200"},
    {"decline_time",read_u32, &(server_config.decline_time),"3600"},
    {"conflict_time",read_u32,&(server_config.conflict_time),"3600"},
    {"offer_time",	read_u32, &(server_config.offer_time),	"60"},
    {"min_lease",	read_u32, &(server_config.min_lease),	"60"},
    {"lease_file",	read_str, &(server_config.lease_file),	"/var/lib/misc/udhcpd.leases"},
    {"pidfile",	read_str, &(server_config.pidfile),	"/var/run/udhcpd.pid"},
    {"notify_file", read_str, &(server_config.notify_file),	""},
    {"siaddr",	read_ip,  &(server_config.siaddr),	"0.0.0.0"},
    {"sname",	read_str, &(server_config.sname),	""},
    {"boot_file",	read_str, &(server_config.boot_file),	""},
    /*ADDME: static lease */
    {"",		NULL, 	  NULL,				""}
};


int read_config(char *file)
{
    FILE *in;
    char buffer[80], orig[80], *token, *line;
    int i;

    for (i = 0; strlen(keywords[i].keyword); i++)
        if (strlen(keywords[i].def))
            keywords[i].handler(keywords[i].def, keywords[i].var);

    if (!(in = fopen(file, "r"))) {
        LOG(LOG_ERR, "unable to open config file: %s", file);
        return 0;
    }

    while (fgets(buffer, 80, in)) {
        if (strchr(buffer, '\n')) *(strchr(buffer, '\n')) = '\0';
        strncpy(orig, buffer, 80);
        if (strchr(buffer, '#')) *(strchr(buffer, '#')) = '\0';
        token = buffer + strspn(buffer, " \t");
        if (*token == '\0') continue;
        line = token + strcspn(token, " \t=");
        if (*line == '\0') continue;
        *line = '\0';
        line++;

        /* eat leading whitespace */
        line = line + strspn(line, " \t=");
        /* eat trailing whitespace */
        for (i = strlen(line); i > 0 && isspace(line[i - 1]); i--);
        line[i] = '\0';

        for (i = 0; strlen(keywords[i].keyword); i++)
            if (!strcasecmp(token, keywords[i].keyword))
                if (!keywords[i].handler(line, keywords[i].var)) {
                    LOG(LOG_ERR, "unable to parse '%s'", orig);
                    /* reset back to the default value */
                    keywords[i].handler(keywords[i].def, keywords[i].var);
                }
    }
    fclose(in);
    return 1;
}
#endif
#ifdef __SC_BUILD__
void reconfig_dhcpd(char *conf_file)
{
    unsigned int i,j;
    char *pt;
    int pid_fd;
    struct option_set *option;

    /* ok, config file updated, we need commit the changing*/
    for (i = 0; i < MAX_INTERFACES; i++)
    {
        free_server_config_malloc(&server_config[i]);
        memset(&server_config[i], 0, sizeof(struct server_config_t));
    }
    free_client_option(vendor_header);
    vendor_header = NULL;
    free_client_option(client_header);
    client_header = NULL;
    free_client_option(user_class_header);
    user_class_header = NULL;


    read_config(conf_file);

    if (no_of_ifaces == 0)
        return;

    for (i = 0; i < no_of_ifaces; i++)
    {
        pid_fd = pidfile_acquire(server_config[i].pidfile);
        pidfile_write_release(pid_fd);

        if ((option = find_option(server_config[i].options, DHCP_LEASE_TIME))) {
            memcpy(&server_config[i].lease, option->data + 2, 4);
            server_config[i].lease = ntohl(server_config[i].lease);
        }
        else server_config[i].lease = LEASE_TIME;

        if ((option = find_option(server_config[i].options, DHCP_SUBNET)))
        {
            memcpy(&server_config[i].netmask, option->data + 2, 4);
        }
        else
            server_config[i].netmask = htonl(SUBNET_MASK);

        //leases = malloc(sizeof(struct dhcpOfferedAddr) * server_config[i].max_leases);
        //memset(leases, 0, sizeof(struct dhcpOfferedAddr) * server_config[i].max_leases);

        //read_leases(server_config[i].lease_file, i);

        if (read_interface(server_config[i].interface, &server_config[i].ifindex,
                           &server_config[i].server, server_config[i].arp) < 0)
            server_config[i].active = FALSE;
        else
            server_config[i].active = TRUE;

#ifndef DEBUGGING
        pid_fd = pidfile_acquire(server_config[i].pidfile); /* hold lock during fork. */
        /* cfgmr req: do not fork */
        /*
           if (daemon(0, 0) == -1) {
           perror("fork");
           exit_server(1, i);
           }
           */

        pidfile_write_release(pid_fd);
#endif
    }

    return;
}
#endif

#ifdef __SC_BUILD__
void write_leases(int ifid)
#else
void write_leases(void)
#endif
{
    FILE *fp;
    unsigned int i;
    char buf[255];
    time_t curr = time(0);
    unsigned long lease_time;
#ifdef __SC_BUILD__
    if (!(fp = fopen(server_config[ifid].lease_file, "w"))) {
        LOG(LOG_ERR, "Unable to open %s for writing", server_config[ifid].lease_file);
        return;
    }

    for (i = 0; i < server_config[ifid].max_leases; i++) {
        if (leases[ifid][i].yiaddr != 0) {
            if (server_config[ifid].remaining) {
                if (lease_expired(&(leases[ifid][i])))
                    lease_time = 0;
                else lease_time = leases[ifid][i].expires - curr;
            } else lease_time = leases[ifid][i].expires;
            lease_time = htonl(lease_time);
            fwrite(leases[ifid][i].chaddr, 16, 1, fp);
            fwrite(&(leases[ifid][i].yiaddr), 4, 1, fp);
            fwrite(&lease_time, 4, 1, fp);
            fwrite(leases[ifid][i].hostname, MAX_HOSTNAME_LEN, 1, fp);
            /*
             * Notify sc_neighbored DHCP lease time expired. And
             * clean the lease after notify to make sure udhcpd
             * will not send lease time expired message continuely.
             */
            do {
                if(lease_expired(&leases[ifid][i])) {
                    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
                    if(fd == -1)
                        break;

                    struct sockaddr_un addr;
                    memset(&addr, 0, sizeof(addr));
                    addr.sun_family = AF_UNIX;
                    strcpy(addr.sun_path, SNBD_CMD_SOCKET_PATH);

                    struct snbd_cmd_dhcpv4 cmd;
                    memset(&cmd, 0, sizeof(cmd));
                    cmd.base.type = SNBD_CMD_TYPE_DHCPV4;
                    cmd.dhcp_cmd  = SNBD_CMD_DHCPV4_LEASE_EXPIRED;
                    memcpy(cmd.l2addr, leases[ifid][i].chaddr, ETH_ALEN);
                    sendto(fd, &cmd, sizeof(cmd), 0, (struct sockaddr *)&addr, sizeof(addr));
                    close(fd);
                    memset(&leases[ifid][i], 0, sizeof(leases[ifid][i]));
                }
            } while(0);

        }
    }
    fclose(fp);

    if (server_config[ifid].notify_file) {
        sprintf(buf, "%s %s", server_config[ifid].notify_file, server_config[ifid].lease_file);
        system(buf);
    }
#else
    if (!(fp = fopen(server_config.lease_file, "w"))) {
        LOG(LOG_ERR, "Unable to open %s for writing", server_config.lease_file);
        return;
    }

    for (i = 0; i < server_config.max_leases; i++) {
        if (leases[i].yiaddr != 0) {
            if (server_config.remaining) {
                if (lease_expired(&(leases[i])))
                    lease_time = 0;
                else lease_time = leases[i].expires - curr;
            } else lease_time = leases[i].expires;
            lease_time = htonl(lease_time);
            fwrite(leases[i].chaddr, 16, 1, fp);
            fwrite(&(leases[i].yiaddr), 4, 1, fp);
            fwrite(&lease_time, 4, 1, fp);
        }
    }
    fclose(fp);

    if (server_config.notify_file) {
        sprintf(buf, "%s %s", server_config.notify_file, server_config.lease_file);
        system(buf);
    }
#endif
}

#ifdef __SC_BUILD__
void read_leases(char *file, int ifid)
#else
void read_leases(char *file)
#endif
{
    FILE *fp;
    unsigned int i = 0;
    struct dhcpOfferedAddr lease;
    if (!(fp = fopen(file, "r"))) {
        LOG(LOG_ERR, "Unable to open %s for reading", file);
        return;
    }


#ifdef __SC_BUILD__
    while (i < server_config[ifid].max_leases && (fread(&lease, sizeof lease, 1, fp) == 1)) {
        /* ADDME: is it a static lease */
        if (lease.yiaddr >= server_config[ifid].start && lease.yiaddr <= server_config[ifid].end) {
            lease.expires = ntohl(lease.expires);
            if (!server_config[ifid].remaining) lease.expires -= time(0);
            if (!(add_lease(lease.chaddr, lease.yiaddr, lease.expires, ifid,lease.hostname))) {
                LOG(LOG_WARNING, "Too many leases while loading %s\n", file);
                break;
            }
            i++;
        }
    }
#else
    while (i < server_config.max_leases && (fread(&lease, sizeof lease, 1, fp) == 1)) {
        /* ADDME: is it a static lease */
        if (lease.yiaddr >= server_config.start && lease.yiaddr <= server_config.end) {
            lease.expires = ntohl(lease.expires);
            if (!server_config.remaining) lease.expires -= time(0);
            if (!(add_lease(lease.chaddr, lease.yiaddr, lease.expires))) {
                LOG(LOG_WARNING, "Too many leases while loading %s\n", file);
                break;
            }				
            i++;
        }
    }
#endif


    DEBUG(LOG_INFO, "Read %d leases", i);
    fclose(fp);
}



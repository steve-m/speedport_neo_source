/*
 * FON Status Manager Client Daemon (fonsmcd)
 *
 * This file is part of FONUCS. Copyright (C) 2007 FON Wireless Ltd.
 *
 * Created: 20070308 Pablo Martin Medrano <pablo@fon.com>
 *
 * $Id: fonsmcd.c 441 2008-03-26 10:20:13Z pablo.martin $
 *
 * protocol.[ch] and log.[ch] are shared
 * between FONSMC and FONSMS
 *
 */
#include <linux/limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <ip4.h>
#include <dns.h>
#include <log.h>
#include <protocol.h>
#include <aes.h>
#include <poption.h>
#include <libdaemon/daemon.h>
#include <errno.h>
#include <fonrsa.h>
#include <base64.h>
#include <base16.h>
#include <syslog.h>
#include "log_api.h"
#include "dod.h"

#define SUPPORT_IPV6

#ifdef SUPPORT_IPV6
#include <ip6.h>
#endif

stralloc domain = {0}; 	/* Doctor Bernstein C strings */
stralloc answer = {0};
stralloc arg ={0};
stralloc ip ={0};

typedef enum {
	E_UDP = 0,
	E_TCP = 1
} E_PROTOCOL;

typedef enum {
	E_ONLINE = -2,
	E_OFFLINE = -1,
	E_NOTHING = 0
} E_EXEC_CODE;

typedef struct {
	char hostname[256];
	char ip_address[4];
	int resolved;
	int is_ip_address; 	/* Thus, it doensnt need to be resolved */
	unsigned int port;
	E_PROTOCOL protocol; 
#ifdef SUPPORT_IPV6
	int is_ip_address_ipv6; 	/* Thus, it doensnt need to be resolved */
        char ip_address_ipv6[16];
        int resolved_ipv6;
        int is_ipv6;
#endif
} Host;

static struct ST_options {
	int test;
	int nodaemon;
	int killdaemon;
	int reloaddaemon;
	int printbd;
	int check;
	int port;
	char *host;
	char *config_path;
	char *mac;
	char *version;
	char *revision;
	char *status;
	char *key;
	int period_online;
	int period_offline;
	int period_fastdetection;
	int timeout;
	int retries;
	char *suffix;
	char *aespath;
	char *rsapath;
	char *trigger_online;
	char *trigger_offline;
} global_options;

typedef struct {
	int code;
	char executable[PATH_MAX];
} Trigger;

/* Client configuration structure */
#define MAX_FON_DOMAIN 64
#define MAX_CONFIGURATION_LINE_SIZE 1024

typedef struct {
	int counter;
	int (*function)(void *);
}Counter;

typedef enum {
	KEY_FIRST = 0,
	KEY_CURRENT = 1
} KEY_STATE;

typedef struct {
	/* Configuration */
	char suffix[MAX_FON_DOMAIN]; /* Domain to append to the queries */
	int period_online; 	/* Delay between queries, in seconds, when we are online */
	int period_offline; 	/* Delay between queries, in seconds, when we are offline */ 
	int period_fastdetection;  
	size_t num_hosts; 	/* Number of hosts in the hosts array */
	Host *hosts; 		/* Array of Host structures */
	size_t num_triggers; 	/* N of triggers in the trigger array */
	Trigger *trigger; 	/* Array of Trigger structures */
	int res_init_done; 	/* Internal flag */
	int retries; 		/* Number of retries to be done before getting angry 
				   (going offline) */
	int timeout; 		/* How much time to wait for an answer, in milliseconds */
	char rsapath[PATH_MAX]; /* Public key path */
	char aespath[PATH_MAX]; /* AES key path */
	/* State */
	void *qr; 		/* protocol library handler */
	int failed_queries; 	/* Number of failed queries while offline (if 0, we are online) */
	int fd; 		/* File descriptor for the signal pipe */
	fd_set fds;		/* File descriptor set for the signal pipe */	
	int quit; 		/* Internal flag */
	QR_regular_query query; /* Query data is always the same, until reload */
	int start; 		/* On start query */
	Counter *counters;
	void *fonrsa; 		/* FONRSA library handler */ 
	unsigned char first_key[32]; 	/* Original key (stored in boarddata). Loaded once */
	unsigned char current_key[32]; 	/* current AES key */
	KEY_STATE key_state; 	/* where the current AES key comes from */
} Fonsmcd;

struct ar531x_boarddata {
	unsigned long magic;           /* board data is valid */
	unsigned short cksum;          /* checksum (starting with BD_REV 2) */
	unsigned short rev;            /* revision of this struct */
	char   boardName[64];          /* Name of board */
	unsigned short major;          /* Board major number */
	unsigned short minor;          /* Board minor number */
	unsigned long config;          /* Board configuration */
	unsigned short resetConfigGpio;/* Reset factory GPIO pin */
	unsigned short sysLedGpio;     /* System LED GPIO pin */
	unsigned long cpuFreq;         /* CPU core frequency in Hz */
	unsigned long sysFreq;         /* System frequency in Hz */
	unsigned long cntFreq;         /* Calculated C0_COUNT frequency */
	unsigned char  wlan0Mac[6];
	unsigned char  enet0Mac[6];
	unsigned char  enet1Mac[6];
	unsigned short pciId;          /* Pseudo PCIID for common code */
	unsigned short memCap;         /* cap bank1 in MB */
	unsigned char  wlan1Mac[6];    /* (ar5212) */
	unsigned char  lbMac[6];
	unsigned char  pciMac[6];
	unsigned char serial_number[12]; /* add by alfa for FON serial number */
	unsigned char key_number[32];   /* add by alfa for FON key number */
};

static int SMC_init(Fonsmcd **fonsmcd);
static int SMC_end(Fonsmcd *fonsmcd);
static int SMC_retrieve_query_data(Fonsmcd *fonsmcd, QR_regular_query *query);
static int SMC_do_regular_query(Fonsmcd *fonsmcd);
static int SMC_execute_regular_answer(Fonsmcd *fonsmcd, QR_regular_answer *answer);
static int SMC_load_configuration(Fonsmcd *fonsmcd);
static int SMC_send_buffer(Fonsmcd *fonsmcd, Host *host, char *buffer, size_t buffer_size, unsigned char *rbuffer, size_t *rbuffer_size, size_t rbuffer_max);
static int SMC_alloc_configuration(Fonsmcd **fonsmcd);
static int SMC_free_configuration(Fonsmcd *fonsmcd);
static int SMC_alloc_configuration_arrays(Fonsmcd *fonsmcd);
static int SMC_dns_txt(Fonsmcd *fonsmcd, Host *host, stralloc *out,const stralloc *fqdn);
static int SMC_dns_resolve(Fonsmcd *fonsmcd, Host *host, const char *q,const char qtype[2]);
// static int SMC_print_configuration(Fonsmcd *fonsmcd);
static int SMC_resolv_host(Host *host);
static int SMC_resolv_host_ipv6(Host *host);
static int SMC_execute_buffer(char *buffer);
static int SMC_replace_data_in_exec(char **buffer, Trigger *trigger, QR_regular_answer *answer);
static int SMC_parsecmd(int *argc, char ***argv);
static Trigger *SMC_find_trigger(Fonsmcd *fonsmcd, int code);
static int SMC_execute_exception_trigger(Fonsmcd *fonsmcd, int code);
static int SMC_loop(Fonsmcd *fonsmcd);
static int SMC_execute_exception_trigger(Fonsmcd *fonsmcd, int code);

static int SMC_daemonize(Fonsmcd **fonsmcd);
static int SMC_signal_finish(Fonsmcd *fonsmcd);
static int SMC_signal_init(Fonsmcd *fonsmcd);

static int SMC_reload(Fonsmcd *fonsmcd);
static int SMC_refresh_triggers(Fonsmcd *fonsmcd);
/*
 static int SMC_deactivate_counter(Fonsmcd *fonsmcd, int counter);
 static int SMC_decrement_counter(Fonsmcd *fonsmcd);
 static int SMC_reset_counter(Fonsmcd *fonsmcd, int counter);
*/
int SMC_key_retriever_function(void *data, char *wlmac, unsigned char *key, size_t size_buffer, size_t *size);
static int SMC_replace_string_in_exec(char **buffer, Trigger *trigger, char *string, size_t size);
int SMC_retrieve_key_from_memory(Fonsmcd *fonsmcd);
int SMC_reload_key(Fonsmcd *fonsmcd);
int SMC_load_boarddata(struct ar531x_boarddata *binfo, int print);
void SMC_retrieve_key_from_boarddata(struct ar531x_boarddata *binfo, unsigned char *buf);
void SMC_print_boarddata(struct ar531x_boarddata *binfo);

int main(int argc, char **argv)
{
	Fonsmcd *fonsmcd;
	int ret = 0;
	int signal = 0;

	if (SMC_parsecmd(&argc, &argv)) {
		fprintf(stderr, "Error parsing options");
	}
	if (global_options.printbd) {
		struct ar531x_boarddata b;
		return SMC_load_boarddata(&b, 1);
	}
	if (global_options.check) {
		if (daemon_pid_file_is_running() >= 0) {
			fprintf(stderr, "fonsmcd already running\n");
			return 0;
		} else {
			fprintf(stderr, "fonsmcd not running\n");
			return 1;
		}
	}
	if (global_options.killdaemon)
		signal = SIGINT;
	else if (global_options.reloaddaemon)
		signal = SIGHUP;

	if (signal) {
		daemon_pid_file_ident = daemon_log_ident = daemon_ident_from_argv0(argv[0]);
		if ((ret = daemon_pid_file_kill_wait(signal, 5)) < 0)
			daemon_log(LOG_WARNING, "Failed sending signal %d to daemon", signal);
		return ret < 0 ? 1 : 0;	
	}
	if (!global_options.nodaemon) {
		daemon_pid_file_ident = daemon_log_ident = daemon_ident_from_argv0(argv[0]);
		ret = SMC_daemonize(&fonsmcd);
		if (ret != 0) {
			daemon_log(LOG_ERR, "Error daemonizing process");
			return ret;
		}
		if (LG_start("fonsmcd", LG_DEBUG, LG_SYSLOG, NULL, LOG_LOCAL6)) {
			daemon_log(LOG_ERR, "Error calling LG_start");
			return 1;
		}
	} else {
		if (LG_start("fonsmcd", LG_DEBUG, LG_STDERR, NULL, LOG_LOCAL6))
			return 1;
		if (SMC_init(&fonsmcd)) {
			fon_critical("Error calling SMC_init");
			return 1;
		}
	}

	fonsmcd->quit = 0;
	ret = SMC_signal_init(fonsmcd);
	if (ret != 0) {
		fon_critical("Error calling SMC_signal_init()");
	} else {
		ret = SMC_loop(fonsmcd);
	}
	if (SMC_end(fonsmcd)) {
		fon_critical("%s: Error calling SMC_end", __FUNCTION__);
		return 1;
	}
	return ret;
}

static char seed[128];

static int SMC_init(Fonsmcd **fonsmcd)
{
	struct timeval tv;
	QR_Init qrinit;

	if (SMC_alloc_configuration(fonsmcd)) {
		fon_critical("%s: Error in configuration struct malloc", __FUNCTION__);
		return -1;
	}

	dns_random_init(seed);
	if (gettimeofday(&tv, NULL)) {
		fon_critical("%s: gettimeofday failed?", __FUNCTION__);
		return 1;
	}
	srand((unsigned int)(tv.tv_sec + tv.tv_usec + getpid()));
	(*fonsmcd)->res_init_done = 1;

	
	if (SMC_reload(*fonsmcd)) {
		fon_critical("%s: Error calling SMC_reload", __FUNCTION__);
		return 1;
	}
	
	/* FIXME: Send first packet before returning (control to the caller process) */

	/* load the key */
	if (((*fonsmcd)->fonrsa = FR_init((*fonsmcd)->rsapath)) == NULL) {
		fon_critical("%s: error calling fr_init", __FUNCTION__);
		return 1;
	}

	memset((void *)&qrinit, 0, sizeof(QR_Init));
	qrinit.key_retriever = SMC_key_retriever_function;
	qrinit.key_retriever_data = (void *)(*fonsmcd);
	qrinit.decrypt = (QR_decrypt_function_t *)FR_decrypt_buffer;
	qrinit.decrypt_data = (void *)((*fonsmcd)->fonrsa);

	if (((*fonsmcd)->qr = QR_start(&qrinit)) == NULL) {
		fon_critical("%s: Error calling QR_init()", __FUNCTION__);
		return 1;
	}
	return 0;
}

static int SMC_daemonize(Fonsmcd **fonsmcd)
{
	pid_t pid;

	if ((pid = daemon_pid_file_is_running()) >= 0) {
		fon_critical("Daemon already running on PID file %u", pid);
		return 1;
	}
	daemon_retval_init();
	if ((pid = daemon_fork()) < 0) {
		daemon_log(LOG_ERR, "Error calling daemon_fork()"); 
		daemon_retval_done();
		return 1;
	} else if (pid) { /* parent process */
		int ret;
		if ((ret = daemon_retval_wait(20)) < 0) {
			daemon_log(LOG_ERR, "Could not recieve return value from daemon process.");
			return 255;
		}
		if (ret == 0)
			daemon_log(LOG_INFO, "fonsmcd successfully started");
		else
			daemon_log(LOG_ERR, "Failure (%i) starting daemon.", ret);
		exit(ret);
	} else { /* daemon */
		if (daemon_pid_file_create() < 0) {
			daemon_log(LOG_ERR, "Could not create PID file (%s).", strerror(errno));
			daemon_retval_send(1);
			return 1;
		}
	}

	if (daemon_signal_init(SIGINT, SIGQUIT, SIGHUP, SIGALRM, SIGUSR1, SIGUSR2, SIGPIPE, 0) < 0) {
		daemon_log(LOG_ERR, "Could not register signal handlers (%s).", strerror(errno));
		daemon_retval_send(1);
		return 1;
	}

	if (LG_start("fonsmcd", LG_DEBUG, LG_STDERR, NULL, LOG_LOCAL6)) {
		daemon_log(LOG_ERR, "Error calling LG_start");
		daemon_retval_send(1);
		return 1;
	}

	if (SMC_init(fonsmcd)) {
		daemon_log(LOG_ERR, "Error calling SMC_init");
		daemon_retval_send(1);
		return 1;
	}

	daemon_retval_send(0);
	daemon_log(LOG_INFO, "Sucessfully started");
	return 0;
}

static int SMC_signal_init(Fonsmcd *fonsmcd)
{
	if (!global_options.nodaemon) {
		/* This was already done by SMC_daemonize() */
		return 0;
	}
	if (daemon_signal_init(SIGINT, SIGQUIT, SIGHUP, SIGALRM, SIGUSR1, SIGUSR2, SIGPIPE, SIGINT, 0) < 0) {
		fon_critical("%s: Could not register signal handlers (%s).", __FUNCTION__, strerror(errno));
		return 1;
	}
	return 0;
}

static int SMC_signal_finish(Fonsmcd *fonsmcd)
{
	daemon_signal_done();
	return 0;
}

static int SMC_daemon_finish(Fonsmcd *fonsmcd)
{
	daemon_log(LOG_INFO, "Exiting...");
	daemon_pid_file_remove();
	return 0;
}

static int SMC_end(Fonsmcd *fonsmcd)
{
	SMC_signal_finish(fonsmcd);
	if (!global_options.nodaemon)
		SMC_daemon_finish(fonsmcd);
	FR_end(fonsmcd->fonrsa);
	QR_end(fonsmcd->qr);
	SMC_free_configuration(fonsmcd);
	free(fonsmcd);
	LG_end();
	return 0;
}

static int SMC_alloc_configuration(Fonsmcd **fonsmcd)
{
	*fonsmcd = (Fonsmcd *)malloc(sizeof(Fonsmcd));
	if (*fonsmcd == NULL)
		return -1;
	return 0;
}
static int SMC_free_configuration(Fonsmcd *fonsmcd)
{
	if (fonsmcd == NULL) 
		return 0;
	if (fonsmcd->hosts != NULL)
		free(fonsmcd->hosts);
	if (fonsmcd->trigger != NULL)
		free(fonsmcd->trigger);
	return 0;
}
/*
 * SMC_load_configuration: configuration load
 */
static int SMC_load_configuration(Fonsmcd *fonsmcd)
{
	Trigger *trigger;
	int i = 0;
	int len = 0;
	memset(fonsmcd, 0, sizeof(Fonsmcd));

	if (SMC_alloc_configuration_arrays(fonsmcd)) {
		fon_critical("%s: SMC_alloc_configuration_arrays failed", __FUNCTION__);
		return 1;
	}

	if (global_options.host) {
		fonsmcd->num_hosts = 1;
		fonsmcd->hosts = (Host *)malloc(sizeof(Host) * fonsmcd->num_hosts);
		memset(&(fonsmcd->hosts[0]), 0, sizeof(Host));
		strcpy(fonsmcd->hosts[0].hostname, global_options.host);

#ifdef SUPPORT_IPV6
		fonsmcd->hosts[0].is_ip_address_ipv6 = 0;
                if (SMC_resolv_host_ipv6(&(fonsmcd->hosts[0]))) {
                    fon_warning("%s: Error resolving host IPv6 [%s], will try later", __FUNCTION__, fonsmcd->hosts[0].hostname);
                }
#endif

		fonsmcd->hosts[0].is_ip_address = 1;
		for (i = 0; i < strlen(global_options.host); i++) {
			if ((global_options.host[i] != '.') && (!isdigit(global_options.host[i])))
				fonsmcd->hosts[0].is_ip_address = 0;
		}

		if (fonsmcd->hosts[0].is_ip_address) {
			fon_debug("%s: %s is already an ip address. Not resolving", __FUNCTION__,
				  fonsmcd->hosts[0].hostname);
			len = ip4_scan(global_options.host, fonsmcd->hosts[0].ip_address);
			if (len != strlen(global_options.host)) {
				fon_critical("%s: Error converting [%s] to an ip_address", __FUNCTION__, global_options.host);
				return -1;
			}
			fonsmcd->hosts[0].resolved = 1;
		} else {
			if (SMC_resolv_host(&(fonsmcd->hosts[0]))) {
				fon_warning("%s: Error resolving host [%s], will try later", __FUNCTION__, fonsmcd->hosts[0].hostname);
			}
		}
		if (global_options.port) 
			fonsmcd->hosts[0].port = global_options.port;
		else
			fonsmcd->hosts[0].port = 53;
		fonsmcd->hosts[0].protocol = E_UDP;
		fon_message("Host: %s", fonsmcd->hosts[0].hostname);
		fon_message("Port: %d", fonsmcd->hosts[0].port);
		fon_message("Protocol: %s", "UDP");
	} else {
		fon_critical("Host argument not found");
		return 1;
	}

	if (global_options.period_online) {
		fonsmcd->period_online = global_options.period_online;
		fon_message("Period online: %d", fonsmcd->period_online);
	} else {
		fon_critical("Period online argument not found");
		return 1;
	}

	if (global_options.period_offline) {
		fonsmcd->period_offline = global_options.period_offline;
		fon_message("Period offline: %d", fonsmcd->period_offline);
	} else {
		fon_critical("Period offline argument not found");
		return 1;
	}
	
        if (global_options.period_fastdetection) {
		fonsmcd->period_fastdetection = global_options.period_fastdetection;
		fon_message("Period fastdetection: %d", fonsmcd->period_fastdetection);
	} else {
		fon_critical("Period fastdetection argument not found");
		return 1;
	}
	if (global_options.timeout) {
		fonsmcd->timeout = global_options.timeout;
		fon_message("Timeout: %d", fonsmcd->timeout);
	} else {
		fon_critical("Timeout argument not found");
		return 1;
	}

	if (global_options.retries) {
		fonsmcd->retries = global_options.retries;
		fon_message("Retries: %d", fonsmcd->retries);
	} else {
		fon_critical("Retries argument not found");
		return 1;
	}

	if (global_options.aespath) {
		strcpy(fonsmcd->aespath, global_options.aespath);
		fon_message("aespath: %s", fonsmcd->aespath);
	} 
	else {
		fon_warning("aespath argument not found");
		// return 1;
	}

	if (global_options.rsapath) {
		strcpy(fonsmcd->rsapath, global_options.rsapath);		
		fon_message("rsapath: %s", fonsmcd->rsapath);
	} else {
		fon_critical("rsapath argument not found");
		return 1;
	}

	if (global_options.suffix) {
		strcpy(fonsmcd->suffix, global_options.suffix);		
		fon_message("suffix: %s", fonsmcd->suffix);
	} else {
		fon_critical("suffix argument not found");
		return 1;
	}

	if ((global_options.trigger_online) && (global_options.trigger_offline)) {
		fonsmcd->num_triggers = 2;
		fonsmcd->trigger = (Trigger *)malloc(sizeof(Trigger) * fonsmcd->num_triggers);

		trigger = &(fonsmcd->trigger[0]);
  		trigger->code = E_ONLINE;
		strcpy(trigger->executable, global_options.trigger_online);
		fon_message("trigger online: %s", trigger->executable);

		trigger = &(fonsmcd->trigger[1]);
  		trigger->code = E_OFFLINE;
		strcpy(trigger->executable, global_options.trigger_offline);
		fon_message("trigger offline: %s", trigger->executable);
	} else {
		fon_critical("missing trigger(s)");
		return 1;
	}
	// SMC_print_configuration(fonsmcd);
	return 0;
}

/*
   static int SMC_print_configuration(Fonsmcd *fonsmcd)
   {
   int i;

   fon_debug("%s: period online %d, period offline %d, retries %d, timeout %d", 
   __FUNCTION__, fonsmcd->period_online, fonsmcd->period_offline,
   fonsmcd->retries, fonsmcd->timeout);
   fon_debug("%s: suffix [%s]", __FUNCTION__, fonsmcd->suffix);
   for (i = 0; i < fonsmcd->num_hosts; i++) {
   fon_debug("%s: %d: hostname %s, port %d, protocol %d", __FUNCTION__, i, fonsmcd->hosts[i].hostname, fonsmcd->hosts[i].port, fonsmcd->hosts[i].protocol);
   }
   for (i = 0; i < fonsmcd->num_triggers; i++) {
   fon_debug("%s: %d: code %d, executable [%s]", __FUNCTION__, i, fonsmcd->trigger[i].code, fonsmcd->trigger[i].executable); 
   }
   return 0;	
   }
   */

static int SMC_alloc_configuration_arrays(Fonsmcd *fonsmcd)
{
	if ((fonsmcd->hosts = (Host *)malloc(sizeof(Host) * fonsmcd->num_hosts)) == NULL)
		return 1;
	if ((fonsmcd->trigger = (Trigger *)malloc(sizeof(Trigger) * fonsmcd->num_triggers)) == NULL) {
		free(fonsmcd->hosts);
		fonsmcd->hosts = NULL;
		return 1;
	}
	return 0;
}

static int sc_once_online=0;

static int SMC_do_regular_query(Fonsmcd *fonsmcd)
{
	QR_regular_answer answer;
	//char buffer[QUERY_SIZE+1];
	char buffer[1024];
	char qbuffer[1024];
	char rbuffer[1025];
	int exception_trigger = 0;
	int set_alarm_online = 0;
	QR_STRUCT_TYPE struct_type;
	size_t buffer_size, rbuffer_size;

	if (fonsmcd->num_hosts == 0) {
		fon_warning("%s: No hosts, no play", __FUNCTION__);
		return -1;
	}
    
        /*triger wan up*/
        if(1)
        {
            int retry = 0;
            while(retry < 3)
            {
                retry ++;
                if (access("/tmp/var/hsfon_wanidle", F_OK) == 0)
                {  
                    dod_up();
                    sleep(2);
                }
                else break;
            }
        }
	/*
	   if (SMC_retrieve_query_data(&(fonsmcd->query))) {
	   fon_warning("%s: Error retrieving query data", __FUNCTION__);
	   return -1;
	   }
	   */
	if (fonsmcd->start) {
		fonsmcd->query.type = QR_TYPE_REGULAR_START;
		fonsmcd->start = 0;
	} else if (fonsmcd->failed_queries != 0) {
		fonsmcd->query.type = QR_TYPE_REGULAR_RETRY;
		fonsmcd->query.retries = fonsmcd->failed_queries;
	} else {
		fonsmcd->query.type = QR_TYPE_REGULAR_ONLINE;
		fonsmcd->query.retries = 0;
	}

	struct_type = QR_REGULAR_QUERY;
	if (fonsmcd->key_state == KEY_FIRST) 
		struct_type = QR_REGULAR_QUERY_FIRST;	
	if (QR_encode_struct(fonsmcd->qr, QR_REGULAR_QUERY, buffer, 1024, &buffer_size, (void *)&(fonsmcd->query)) != QR_OK) {
		fon_warning("%s: Error encoding regular query", __FUNCTION__);
		return -1;
	}
	QR_print_struct(qbuffer, 1024, (void *)(&(fonsmcd->query)), QR_REGULAR_QUERY);
	fon_debug("QUERY [%s]", qbuffer);
	/* add the .sm.fon.com at the end */
	memcpy(buffer + buffer_size, fonsmcd->suffix, strlen(fonsmcd->suffix));
	buffer_size += strlen(fonsmcd->suffix);
	buffer[buffer_size] = '\0';
	
	/* Set the alarm tentatively before sending DNS packet, to the period_online
	 * (presumably bigger than period_offline)
	 */
/*	if (fonsmcd->failed_queries == 0) {
		alarm(fonsmcd->period_online);
		set_alarm_online = 1;
	} else {
		set_alarm_online = 0;
	}
*/
	if (SMC_send_buffer(fonsmcd, &(fonsmcd->hosts[0]), buffer, buffer_size, (unsigned char *)rbuffer, &rbuffer_size, 1025)) {
		if (fonsmcd->failed_queries != 0) {
			fonsmcd->failed_queries++;
			if (fonsmcd->failed_queries == fonsmcd->retries) {
				fon_debug("TRIGGER [offline]");
				exception_trigger = E_OFFLINE;
                                syslog(LOG_INFO, "%s"LOG_ERRCODE_FO002, log_type_db[GENERAL_LOG]);
			}
			fon_debug("Setting the %s host as unresolved", fonsmcd->hosts[0].hostname);
			fonsmcd->hosts[0].resolved = 0;
#ifdef SUPPORT_IPV6
			fonsmcd->hosts[0].resolved_ipv6 = 0;
#endif
		} else {
			fonsmcd->failed_queries = 1;
			fon_debug("On %d retries we will go offline", fonsmcd->retries);
			fon_debug("Setting the %s host as unresolved", fonsmcd->hosts[0].hostname);
			fonsmcd->hosts[0].resolved = 0;
#ifdef SUPPORT_IPV6
			fonsmcd->hosts[0].resolved_ipv6 = 0;
#endif
		}
	} else {
		fon_debug("%s: Query succeeded", __FUNCTION__);
		if (fonsmcd->failed_queries >= fonsmcd->retries || sc_once_online==0) {
			/* We went offline */
                        sc_once_online = 1;
			fonsmcd->failed_queries = 0;
			fon_debug("TRIGGER [online]");
			exception_trigger = E_ONLINE;
                        syslog(LOG_INFO, "%s"LOG_ERRCODE_FO001, log_type_db[GENERAL_LOG]);
		}  else {
			if (fonsmcd->failed_queries) {
				fon_debug("%s: After %d failed queries, we received an answer!", __FUNCTION__, fonsmcd->failed_queries);
				fonsmcd->failed_queries = 0;
			}
		}
	}
	/* We set the alarm before calling triggers and parsing the protocols,
	 * trying to be more accurate
	 */
	if (fonsmcd->failed_queries == 0) {
		if (!set_alarm_online) {
			alarm(fonsmcd->period_online);
		}
	} else {
                if (fonsmcd->failed_queries >= fonsmcd->retries) {
		        alarm(fonsmcd->period_offline);
                }else{
		        alarm(fonsmcd->period_fastdetection);
                }
	}

	if (exception_trigger != E_NOTHING) {
		SMC_execute_exception_trigger(fonsmcd, exception_trigger); 
	}
	/* And we return here if we are offline */
	if (fonsmcd->failed_queries)
		return 1;
	rbuffer[rbuffer_size] = '\0';
	fon_debug("BUFFER [%d] [%s]", rbuffer_size, rbuffer);
	if (rbuffer[0] == 'a')
		struct_type = QR_REGULAR_ANSWER_NOP;
	else if (rbuffer[0] == 'b')
		struct_type = QR_REGULAR_ANSWER;
	else {
		fon_warning("%s: Unknown answer %c received", __FUNCTION__, rbuffer[0]);
		return -1;
	}
	if (QR_decode_struct(fonsmcd->qr, struct_type, (void *)&answer, rbuffer, rbuffer_size)) {
		fon_warning("%s: Error decoding regular answer", __FUNCTION__);
		return -1;
	}
	if (fonsmcd->query.trid != answer.trid) {
		fon_warning("%s: Transaction ID is not the same of the query", __FUNCTION__);
		return -1;
	}
	QR_print_struct(buffer, 1024, (void *)(&(answer)), QR_REGULAR_ANSWER);
	fon_debug("ANSWER [%s]", buffer);
	if (SMC_execute_regular_answer(fonsmcd, &answer)) {
		fon_warning("%s: Error executing the associated action", __FUNCTION__);
		return -1;
	}
	return 0;
}
int SMC_update_alarm_triggers(Fonsmcd *fonsmcd)
{
	return 0;	
}

/* SMC_key_retriever: */
int SMC_key_retriever_function(void *data, char *wlmac, unsigned char *key, size_t size_buffer, size_t *size)
{
	Fonsmcd *fonsmcd = (Fonsmcd *)data;

	if (size_buffer < 32)
		return 1;
	if (fonsmcd->key_state == KEY_FIRST)  
		memcpy(key, fonsmcd->first_key, 32);
	else
		memcpy(key, fonsmcd->current_key, 32);
	*size = 32;

	return 0;
}

int SMC_reload_key(Fonsmcd *fonsmcd)
{
	int fd, size;
	char base64buffer[65];
	char curbuffer[32];
	aes_context ctx;

	if (SMC_retrieve_key_from_memory(fonsmcd)) {
		fon_warning("%s: error calling SMC_retrieve_key_from_memory", __FUNCTION__);
		return 1;
	}
	return 0;
	/*
	fd = open(fonsmcd->aespath ,O_RDONLY);
	if (fd == -1) {
		fonsmcd->key_state = KEY_FIRST;
		return 0;
	}
	if (read(fd, base64buffer, 64) != (ssize_t)64) {
		close(fd);
		return 2;
	}
	base64buffer[64] = '\0';
	size = B16_decode(base64buffer, curbuffer, 64, 32);
	if (size < 0) {
		close(fd);
		fon_warning("%s: Error calling B6_decode", __FUNCTION__);
		return 3;
	}
	*/
	aes_set_key(&ctx, fonsmcd->first_key, 256);
	aes_decrypt(&ctx, curbuffer, fonsmcd->current_key);
	aes_decrypt(&ctx, curbuffer + 16, fonsmcd->current_key + 16);
	fonsmcd->key_state = KEY_CURRENT;
	return 0;
}

int SMC_load_boarddata(struct ar531x_boarddata *binfo, int print)
{
        int file;

        if ((file = open("/dev/mtd9ro", O_RDONLY)) == -1)
                return 1; 
        if ((read(file, (void*)(binfo), sizeof(struct ar531x_boarddata))) != (ssize_t)sizeof(struct ar531x_boarddata)) {
		close(file);
		return 1;
	}
	close(file);
	return 0;
}
#ifdef FONERADEBUG
void SMC_print_boarddata(struct ar531x_boarddata *binfo)
{
	char wlan0Mac_string[20];
	char enet0Mac_string[20];
	char enet1Mac_string[20];
	char wlan1Mac_string[20];
	char lbMac_string[20];
	char pciMac_string[20];
	char serial_number_string[20];
	char key_number_string[65];
	int size;

	printf("magic %8.8x cksum %4.4x rev %4.4x\n", binfo->magic, binfo->cksum,  binfo->rev);
	printf("boardname[%64.64s]\n", binfo->boardName);
	printf("major %4.4x minor %4.4x config %8.8x\n", binfo->major, binfo->minor, binfo->config);
	printf("resetConfigGpio %4.4x sysLedGpio %4.4x\ncpuFreq %8.8x sysFreq %8.8x cntFreq %8.8x\n",
		binfo->resetConfigGpio, binfo->sysLedGpio, binfo->cpuFreq, binfo->sysFreq, binfo->cntFreq); 
	QR_convert_six_bytes_to_mac_string(wlan0Mac_string, binfo->wlan0Mac);
	QR_convert_six_bytes_to_mac_string(enet0Mac_string, binfo->enet0Mac);
	QR_convert_six_bytes_to_mac_string(enet1Mac_string, binfo->enet1Mac);
	printf("wlan0Mac [%s] enet0Mac [%s] enet1Mac [%s]\n",
		wlan0Mac_string, enet0Mac_string, enet1Mac_string);
	printf("pciId %4.4x memCap %4.4x\n", binfo->pciId, binfo->memCap);
	QR_convert_six_bytes_to_mac_string(wlan1Mac_string, binfo->wlan1Mac);
	QR_convert_six_bytes_to_mac_string(lbMac_string, binfo->lbMac);
	QR_convert_six_bytes_to_mac_string(pciMac_string, binfo->pciMac);
	printf("wlan1Mac [%s] lbMac [%s] pciMac [%s]\n", wlan1Mac_string, lbMac_string, pciMac_string);
	memcpy(serial_number_string, binfo->serial_number,10);
	binfo->serial_number[10] = '\0';
	printf("serial_number [%s]\n", serial_number_string);
	size = B16_encode(binfo->key_number, key_number_string, 32, 64);
	if (size < 0)
		key_number_string[64] = '\0';
	else
		printf("arg\n");
	printf("key_number [%s]\n", key_number_string);
}
#else
void SMC_print_boarddata(struct ar531x_boarddata *binfo)
{
	return;
}
#endif

void SMC_retrieve_key_from_boarddata(struct ar531x_boarddata *binfo, unsigned char *buf)
{
	int i;

	for (i = 0; i < 32; i++)
		buf[i] = binfo->key_number[31 - i];
}

int SMC_retrieve_key_from_memory(Fonsmcd *fonsmcd)
{
	struct ar531x_boarddata binfo;
	int ret;
	FILE *pipe;
	char bufferkw[65]; // 64 + 0

#if ((defined FONTEST) || (defined FONAP))
	if (global_options.key) {
		ret = B16_decode((char *)global_options.key ,fonsmcd->first_key, 64, 32);
		if (ret < 0) {
			fon_critical("%s: Error loading key. Is that base64?", __FUNCTION__);
			return 1;
		}
	} else {
		fon_critical("keyword argument not found");
		return 1;
	}
#else
	if (SMC_load_boarddata(&binfo, 0)) {
		fon_critical("%s: Error loading boarddata", __FUNCTION__);
		return 1;
	}
	SMC_retrieve_key_from_boarddata(&binfo, fonsmcd->first_key);
#endif
	return 0;
}

/* SMC_retrieve_query_data */
static int SMC_retrieve_query_data(Fonsmcd *fonsmcd, QR_regular_query *query)
{
	FILE *pipe;
	struct ar531x_boarddata boarddata;
	char buffermac[20];
	char buffer[1024];
	char buffer_version[3][4];
	char *p;
	int version_digit, version_i;

	query->timestamp = time(NULL);
	if (global_options.mac == NULL) {
#if ((defined FONTEST) || (defined FONAP))
		fon_critical("Mac argument not found");
		return 1;
#else
		if (SMC_load_boarddata(&boarddata, 0)) {
			fon_warning("Error loading boarddata\n");
			return 1;
		}
		QR_convert_six_bytes_to_mac_string(buffermac, boarddata.wlan0Mac);
		strcpy(query->mac, buffermac);
#endif
		fon_debug("wlmac [%s]", query->mac);
	} else {
		strcpy(query->mac, global_options.mac);
	}
	if (global_options.version == NULL) {
		fon_critical("Version argument not found");
		return 1;
	} else {
		sprintf(buffer, global_options.version);
	}
	version_digit = 0;
	version_i = 0;
	for (p = buffer; *p; p++) {
		if (!isdigit(*p)) {
			if (*p != '.') {
				fon_warning("%s: Error parsing version", __FUNCTION__);
				return -1;
			}
			if (version_i == 0) {
				fon_warning("%s: Error parsing version", __FUNCTION__);
				return -1;
			}
			buffer_version[version_digit][version_i + 1] = '\0';
			version_digit++;
			version_i = 0;
			if (version_digit > 2) {
				fon_warning("%s: Error parsing version", __FUNCTION__);
				return -1;
			}
		} else {
			if (version_i > 1) {
				fon_warning("%s: Error parsing version", __FUNCTION__);
				return -1;
			}
			buffer_version[version_digit][version_i] = *p;
			version_i++;
		}
	}
	if ((version_i == 0) || (version_i > 2)) {
		fon_warning("%s: Error parsing version", __FUNCTION__);
		return -1;
	}
	buffer_version[version_digit][version_i + 1] = '\0';

	query->protocol_version = 0;
	query->type = QR_TYPE_REGULAR_START;
// we want netgear to be have higher priority over fonap
// if both simbols are defined
#ifdef NETGEAR
	query->arch = QR_ARCH_NETGEAR;
#elif (defined FONAP)
	query->arch = QR_ARCH_PC;
#else
	query->arch = QR_ARCH_FONERA;
#endif
	query->major_version = atoi(buffer_version[0]);
	query->minor_version = atoi(buffer_version[1]);
	query->micro_version = atoi(buffer_version[2]);
	if (global_options.revision == NULL) {
		fon_critical("Revision argument not found");
		return 1;
	} else {
		strcpy(buffer, global_options.revision);
	}
	if (strlen(buffer) > 2) {
		fon_warning("%s: Invalid revision read", __FUNCTION__);
		return -1;
	}
	for (p = buffer; *p; p++) {
		if (!isdigit(*p)) {
			fon_warning("%s: Invalid revision read", __FUNCTION__);
			return -1;
		}
	}
	query->revision = atoi(buffer);
	query->status = 0;
	return 0;
}

/* SMC_execute_regular_answer */
static int SMC_execute_regular_answer(Fonsmcd *fonsmcd, QR_regular_answer *answer)
{
	Trigger *trigger;
	char *b;
	char data_file[PATH_MAX];
	int fd;

	if (answer->exec == QR_EXEC_NOTHING)
		return 0;
	if ((trigger = SMC_find_trigger(fonsmcd, answer->exec)) == NULL) {
		fon_critical("%s: Trigger not found for exec %d", __FUNCTION__, answer->exec);
		return -1;
	}
	sprintf(data_file, "/tmp/fonsmdata_%8.8x", answer->trid);
	fd = creat(data_file, 0644);
	if (fd == -1) {
		remove(data_file);
		fd = creat(data_file, 0644);
	}
	if (fd == -1) {
		fon_critical("%s: Error opening tmp file", __FUNCTION__);
		return -1;
	}
	if ((write(fd, answer->data, answer->size_data)) != ((ssize_t)(answer->size_data))) {
		fon_critical("%s: Error writing data in tmp file", __FUNCTION__);
		return -1;
	}
	close(fd);
	if (SMC_replace_string_in_exec(&b, trigger, data_file, strlen(data_file))) {
		fon_critical("%s Error replacing data in exec", __FUNCTION__);
		return -1;
	}
	/*
	if (SMC_replace_data_in_exec(&b, trigger, answer)) {
		fon_critical("%s: Error replacing data in exec", __FUNCTION__);
		return -1;
	}
	*/
	if (SMC_execute_buffer(b)) {
		free(b);
		remove(data_file);
		fon_critical("%s: Error executing buffer", __FUNCTION__);
		return -1;
	}
	free(b);
	remove(data_file);
	return 0;
}

static Trigger *SMC_find_trigger(Fonsmcd *fonsmcd, int code)
{
	Trigger *trigger;
	int i;

	trigger = NULL;
	for (i = 0; i < fonsmcd->num_triggers; i++) {
		if (fonsmcd->trigger[i].code == code)
			trigger = &(fonsmcd->trigger[i]);
	}
	return trigger;
}

/* SMC_execute_exception_trigger */
static int SMC_execute_exception_trigger(Fonsmcd *fonsmcd, int code)
{
	Trigger *trigger;

	if ((trigger = SMC_find_trigger(fonsmcd, code)) == NULL) {
		fon_critical("%s: Trigger not found for exec %d", __FUNCTION__, code);
		return -1;
	}
	if (SMC_execute_buffer(trigger->executable)) {
		fon_critical("%s: Error executing buffer", __FUNCTION__);
		return -1;
	}
	return 0;
}

static int SMC_execute_buffer(char *buffer)
{
	int r;

	r = system(buffer);
	if (r != 0)
		fon_critical("%s: Error exec. [%s]", __FUNCTION__, buffer); 
	return r;
}

/* SMC_replace_data_in_exec */
static int SMC_replace_data_in_exec(char **buffer, Trigger *trigger, QR_regular_answer *answer)
{
	return SMC_replace_string_in_exec(buffer, trigger, answer->data, answer->size_data);
}

/* SMC_replace_string_in_exec */
static int SMC_replace_string_in_exec(char **buffer, Trigger *trigger, char *string, size_t size)
{
	char *b,*p;

	b = (char *)malloc(strlen(trigger->executable) + size);
	if (b == NULL)
		return -1;
	*buffer = b;
	for(p = trigger->executable; *p; p++) {
		if (!strncmp(p, "DATA", 4)) {
			memcpy(b, string, size);
			b += size;
			p += 3; /*  +1 at the end of the loop */
		} else {
			*b++ = *p;
		}
	}
	*b = '\0';
	return 0;
}

#ifdef SUPPORT_IPV6
static int SMC_resolv_host_ipv6(Host *host)
{
    if (host->is_ip_address_ipv6) {
        host->resolved_ipv6 = 1; 	/* Already resolved */
        return 0;
    }
    if (host->resolved_ipv6 != 0) {
        fon_critical("%s: Host already resolved IPv6. Go check your code", __FUNCTION__);
        return -1;
    }
    if (!stralloc_copyb(&arg, host->hostname, strlen(host->hostname))) {
        fon_critical("%s: Error calling stralloc_cats()", __FUNCTION__);
        return -1;
    }
    fon_debug("%s: About to call dns_ip6() for %s", __FUNCTION__, host->hostname);
    if (dns_ip6(&ip, &arg) == -1) {
        return -1;
    }
    memcpy(host->ip_address_ipv6, ip.s, 16);
    fon_debug("%s: %s resolved as IPv6 %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", __FUNCTION__, host->hostname,
         (unsigned char)host->ip_address_ipv6[0],(unsigned char)host->ip_address_ipv6[1],(unsigned char)host->ip_address_ipv6[2],
         (unsigned char)host->ip_address_ipv6[3],(unsigned char)host->ip_address_ipv6[4],(unsigned char)host->ip_address_ipv6[5],
         (unsigned char)host->ip_address_ipv6[6],(unsigned char)host->ip_address_ipv6[7],(unsigned char)host->ip_address_ipv6[8],
         (unsigned char)host->ip_address_ipv6[9],(unsigned char)host->ip_address_ipv6[10],(unsigned char)host->ip_address_ipv6[11],
         (unsigned char)host->ip_address_ipv6[12],(unsigned char)host->ip_address_ipv6[13],(unsigned char)host->ip_address_ipv6[14],
         (unsigned char)host->ip_address_ipv6[15]);
    host->resolved_ipv6 = 1;
    return 0;
}

static int SMC_send_buffer_ipv6(Fonsmcd *fonsmcd, Host *host, char *buffer, size_t buffer_size,
                                unsigned char *rbuffer, size_t *rbuffer_size, size_t rbuffer_max)
{
    int ret = 1;

    /* Let's go */
    if (!host->resolved_ipv6) {
        if (SMC_resolv_host_ipv6(host)) {
            fon_critical("%s: Error resolving host [%s]", __FUNCTION__, host->hostname);
            return 1;
        }
    }
    if (!stralloc_copyb(&domain, buffer, buffer_size)) {
        fon_warning("Error with stralloc_cats()");
        return 1;
    }
    if (SMC_dns_txt(fonsmcd, host, &answer, &domain) == -1) {
        goto free_answer;
    }
    *rbuffer_size = (size_t)(answer.len);
    if (*rbuffer_size > rbuffer_max) {
        fon_warning("%s: answer too big for the rbuffer size", __FUNCTION__);
        goto free_answer;
    }
    memcpy(rbuffer, answer.s, answer.len);
    ret = 0;
free_answer:
    return ret;
}

#endif

/*
==============================
= SMC_send_buffer 
==============================
*/
static int SMC_send_buffer_ipv4(Fonsmcd *fonsmcd, Host *host, char *buffer, size_t buffer_size,
	unsigned char *rbuffer, size_t *rbuffer_size, size_t rbuffer_max)
{
	int ret = 1;

	/* Let's go */
	if (!host->resolved) {
		if (SMC_resolv_host(host)) {
			fon_critical("%s: Error resolving host [%s]", __FUNCTION__, host->hostname);
			return 1;
		}
	}
	if (!stralloc_copyb(&domain, buffer, buffer_size)) {
		fon_warning("Error with stralloc_cats()");
		return 1;
	}
	if (SMC_dns_txt(fonsmcd, host, &answer, &domain) == -1) {
		goto free_answer;
	}
	*rbuffer_size = (size_t)(answer.len);
	if (*rbuffer_size > rbuffer_max) {
		fon_warning("%s: answer too big for the rbuffer size", __FUNCTION__);
		goto free_answer;
	}
	memcpy(rbuffer, answer.s, answer.len);
	ret = 0;
free_answer:
	return ret;
}

static int SMC_send_buffer(Fonsmcd *fonsmcd, Host *host, char *buffer, size_t buffer_size,
	unsigned char *rbuffer, size_t *rbuffer_size, size_t rbuffer_max)
{
    int ret = 1;

#ifdef SUPPORT_IPV6
    host->is_ipv6 = 1;
    ret = SMC_send_buffer_ipv6(fonsmcd, host, buffer, buffer_size, rbuffer, rbuffer_size, rbuffer_max);
    if(ret == 0)
        return ret;
    
    host->is_ipv6 = 0;
#endif

    ret = SMC_send_buffer_ipv4(fonsmcd, host, buffer, buffer_size, rbuffer, rbuffer_size, rbuffer_max);

    return ret;
}
/*
============================== 
= SMC_resolv_host 
==============================
*/
static int SMC_resolv_host(Host *host)
{
	if (host->is_ip_address) {
		host->resolved = 1; 	/* Already resolved */
		return 0;
	}
	if (host->resolved != 0) {
		fon_critical("%s: Host already resolved. Go check your code", __FUNCTION__);
		return -1;
	}
	if (!stralloc_copyb(&arg, host->hostname, strlen(host->hostname))) {
		fon_critical("%s: Error calling stralloc_cats()", __FUNCTION__);
		return -1;
	}
	fon_debug("%s: About to call dns_ip4() for %s", __FUNCTION__, host->hostname);
	if (dns_ip4(&ip, &arg) == -1) {
		return -1;
	}
	memcpy(host->ip_address, ip.s, 4);
	fon_debug("%s: %s resolved as %u.%u.%u.%u", __FUNCTION__, host->hostname, (unsigned char)host->ip_address[0],
		(unsigned char)host->ip_address[1], (unsigned char)host->ip_address[2],
		(unsigned char) host->ip_address[3]);
	host->resolved = 1;
	return 0;
}

static char *q = 0; 
struct dns_transmit g_dns_resolve_tx = {0};

/* This is a dns_txt() function, with a "twist" */ 
static int SMC_dns_txt(Fonsmcd *fonsmcd, Host *host, stralloc *out,const stralloc *fqdn)
{
    if (!dns_domain_fromdot(&q,fqdn->s,fqdn->len))
    {
        return -1;
    }
    if (SMC_dns_resolve(fonsmcd, host, q, DNS_T_TXT) == -1)
    {
        return -1;
    }
    if (dns_txt_packet(out,g_dns_resolve_tx.packet,g_dns_resolve_tx.packetlen) == -1)
    {
        return -1;
    }
    dns_transmit_free(&g_dns_resolve_tx);
    dns_domain_free(&q);
    return 0;
}

	
/* SMC_dns_resolve */
int SMC_dns_resolve(Fonsmcd *fonsmcd, Host *host, const char *q,const char qtype[2])
{
	struct taia stamp;
	struct taia deadline, sc_deadline;
	char servers[256];
	iopause_fd x[1];
	int r;
	int retry = 0;

        memset(servers, 0, sizeof(servers));

#ifdef SUPPORT_IPV6
        if(host->is_ipv6 == 1)
        {
            memcpy(servers, host->ip_address_ipv6, 16);
            if (dns_transmit_ipv6_start_at_port(&g_dns_resolve_tx,servers,1,q,qtype,V6any,host->port) == -1)
            {
		return -1;
            }
        }
        else
#endif
        {
            memcpy(servers, host->ip_address, 4);
            if (dns_transmit_start_at_port(&g_dns_resolve_tx,servers,1,q,qtype,V6any,host->port) == -1)
            {
		return -1;
            }
        }
#if 0
	for (retry = 0; retry < fonsmcd->retries; retry++) {
#else
        for (retry = 0; retry < 1; retry++) {
#endif
                taia_now(&stamp);
		taia_uint(&deadline, (unsigned int)fonsmcd->timeout);
		taia_add(&sc_deadline,&deadline,&stamp);
		dns_transmit_io(&g_dns_resolve_tx,x,&deadline);
		iopause(x,1,&sc_deadline,&stamp);
		r = dns_transmit_get(&g_dns_resolve_tx,x,&stamp);
 		if (r == -1) {
			fon_debug("%s: dns_transmit_get returns %d, retry %d, d->udploop %d", __FUNCTION__, r, retry, g_dns_resolve_tx.udploop);
			return -1;
		}
		if (r == 1) {
			fon_debug("%s: dns_transmit_get returns %d, retry %d, d->udploop %d", __FUNCTION__, r, retry, g_dns_resolve_tx.udploop);
			return 0;
		}
		fon_debug("%s: dns_transmit_get returns %d, retry %d, d->udploop %d", __FUNCTION__, r, retry, g_dns_resolve_tx.udploop);
	}
	return -1;
}

static int SMC_parsecmd(int *argc, char ***argv)
{
	OP_ERROR p_error;

	static OP_option options[] = {
		{ "title", 'X', OP_TYPE_TITLE, "fonsmcd", NULL },
		{ "kill", 'k', OP_TYPE_FLAG, "Kill already running daemon", &(global_options.killdaemon)},
		{ "reload", 'l', OP_TYPE_FLAG, "Reload an already running daemon", &(global_options.reloaddaemon)},
		{ "check", 'c', OP_TYPE_FLAG, "Check if the daemon is already running", &(global_options.check)},
#if ((defined FONERADEBUG) || (defined FONAP))
		{ "nodaemon", 'n', OP_TYPE_FLAG, "Do not fork in the background", &(global_options.nodaemon) },
		{ "printbd", 'b', OP_TYPE_FLAG, "Print board data", &(global_options.test) },
		{ "test", 't', OP_TYPE_FLAG, "Do a test run (and do not daemonize)", &(global_options.test) },
		{ "mac", 'm', OP_TYPE_STRING, "test mac address", &(global_options.mac)},
		{ "version", 'v', OP_TYPE_STRING, "test version", &(global_options.version)},
		{ "revision", 'r', OP_TYPE_STRING, "test revision", &(global_options.revision)},
		{ "status", 's', OP_TYPE_STRING, "test status", &(global_options.status)},
		{ "keyword", 'w', OP_TYPE_STRING, "test keyword", &(global_options.key)},
		{ "port", 'p', OP_TYPE_INT, "port number (default 53)", &(global_options.port) },
		{ "host", 'x', OP_TYPE_STRING, "host name", &(global_options.host)},
		{ "period_online", '\0', OP_TYPE_INT, "online period", &(global_options.period_online)},
		{ "period_offline", '\0', OP_TYPE_INT, "offline period", &(global_options.period_offline)},
		{ "period_fast", '\0', OP_TYPE_INT, "fast detection period", &(global_options.period_fastdetection)},
		{ "timeout", '\0', OP_TYPE_INT, "timeout", &(global_options.timeout)},
		{ "retries", '\0', OP_TYPE_INT, "retries", &(global_options.retries)},
		{ "suffix", '\0', OP_TYPE_STRING, "suffix", &(global_options.suffix)},
		{ "aespath", '\0', OP_TYPE_STRING, "aespath", &(global_options.aespath)},
		{ "rsapath", '\0', OP_TYPE_STRING, "rsapath", &(global_options.rsapath)},
		{ "trigger_online", '\0', OP_TYPE_STRING, "online trigger", &(global_options.trigger_online)},
		{ "trigger_offline", '\0', OP_TYPE_STRING, "offline trigger", &(global_options.trigger_offline)},
		
#endif
		{ NULL, '\0', OP_TYPE_FLAG, NULL, NULL }
        };

	memset(&global_options, 0, sizeof(global_options));
	p_error = OP_parse(options, *argc, *argv);
	if (p_error == OP_ERROR_HELP) {
		exit(0);
	} else if (p_error != OP_ERROR_OK) {
		fon_critical("Error parsing commandline");
		return -1;
	}
	return 0;
}

static int SMC_reload(Fonsmcd *fonsmcd)
{
	if (SMC_load_configuration(fonsmcd)) {
		fon_warning("Error loading configuration");
		SMC_free_configuration(fonsmcd);
		free(fonsmcd);
		return 1;
	}
	
	if (SMC_retrieve_query_data(fonsmcd, &(fonsmcd->query))) {
		fon_warning("%s: Error retrieving query data", __FUNCTION__);
		return -1;
	}
	if (SMC_reload_key(fonsmcd)) {
		fon_warning("%s: Error reloading AES256 key", __FUNCTION__);
		return -1;
	}
	return 0;
}

/*
 * Decrement all trigger counters and execute if neccesary
 */
static int SMC_refresh_triggers(Fonsmcd *fonsmcd)
{
	if (SMC_do_regular_query(fonsmcd) < 0) {
		fon_critical("%s: Critical error calling SMC_do_regular_query", __FUNCTION__);
		return 1;
	}
	return 0;
}

static int SMC_loop(Fonsmcd *fonsmcd)
{
	/* Prepare for selecting in the signal fd*/
	FD_ZERO(&fonsmcd->fds);
	FD_SET(fonsmcd->fd = daemon_signal_fd(), &fonsmcd->fds);

	if (global_options.test) {
		if (SMC_do_regular_query(fonsmcd) < 0) {
			fon_critical("%s: Critical error calling SMC_do_regular_query", __FUNCTION__);
		}
		return 0;
	}
#if 0
	alarm(1); 	/* The first ride is free */
#else
{
        int period_start = rand()%(fonsmcd->period_offline);
        alarm(period_start);
}
#endif
        fonsmcd->start = 1;
	while (!fonsmcd->quit) {
		fd_set fds2 = fonsmcd->fds;
		/* Wait for an incoming signal */
		if (select(FD_SETSIZE, &fds2, 0, 0, 0) < 0) {
			/* If we've been interrupted by an incoming signal, continue */
			if (errno == EINTR)
				continue;
			daemon_log(LOG_ERR, "select(): %s", strerror(errno));
			break;
		} 
		/* Check if a signal has been recieved */
		if (FD_ISSET(fonsmcd->fd, &(fonsmcd->fds))) {
			int sig;

			/* Get signal */
			if ((sig = daemon_signal_next()) <= 0) {
				daemon_log(LOG_ERR, "daemon_signal_next() failed.");
				break;
			}
			/* Dispatch signal */
			switch (sig) {
			case SIGINT:
			case SIGQUIT:
                        	fon_critical("Got SIGINT or SIGQUIT");
				fonsmcd->quit = 1;
				break;			
			case SIGHUP:
				fon_debug("Reloading...");
				SMC_free_configuration(fonsmcd);
				SMC_reload(fonsmcd);
				break;			
			case SIGALRM:
				SMC_refresh_triggers(fonsmcd);
				break;
			default:
				fon_debug("Unknown signal: %d", sig);
				break;
			}
		}
        }
	return 0;
}


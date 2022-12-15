#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
#ifdef SYSLOG
#include <syslog.h>
#include "log_api.h"
#endif
#ifdef __SC_BUILD__
#include "scutil.h"
#endif


#ifdef SYSLOG
# define LOG(level, str, args...) do { printf(str, ## args); \
				printf("\n"); \
				syslog(level, str, ## args); } while(0)
# define OPEN_LOG(name) openlog(name, 0, 0)
#define CLOSE_LOG() closelog()
#else
# define LOG_EMERG	"EMERGENCY!"
# define LOG_ALERT	"ALERT!"
# define LOG_CRIT	"critical!"
# define LOG_WARNING	"warning"
# define LOG_ERR	"error"
# define LOG_INFO	"info"
# define LOG_DEBUG	"debug"
# define LOG(level, str, args...) do { printf("%s, ", level); \
				printf(str, ## args); \
				printf("\n"); } while(0)
# define OPEN_LOG(name) do {;} while(0)
#define CLOSE_LOG() do {;} while(0)
#endif

#ifdef DEBUG
# undef DEBUG
# define DEBUG(level, str, args...) LOG(level, str, ## args)
# define DEBUGGING
#else
# define DEBUG(level, str, args...) do {;} while(0)
#endif


#define DEBUG_DHCPD     1
#define DEBUG_DHCPC     2
#define DEBUG_COMMON    (DEBUG_DHCPD|DEBUG_DHCPC)

#ifdef __SC_DEBUG__
#define SC_DEBUG(debug_type, format, args... ) _sc_debug(debug_type, format, ## args)
#else
#define SC_DEBUG(debug_type, format, args... )
#endif

#endif

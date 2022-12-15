/*
 *   stunnel       Universal SSL tunnel
 *   Copyright (C) 1998-2012 Michal Trojnara <Michal.Trojnara@mirt.net>
 *
 *   This program is free software; you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by the
 *   Free Software Foundation; either version 2 of the License, or (at your
 *   option) any later version.
 * 
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *   See the GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, see <http://www.gnu.org/licenses>.
 * 
 *   Linking stunnel statically or dynamically with other modules is making
 *   a combined work based on stunnel. Thus, the terms and conditions of
 *   the GNU General Public License cover the whole combination.
 * 
 *   In addition, as a special exception, the copyright holder of stunnel
 *   gives you permission to combine stunnel with free software programs or
 *   libraries that are released under the GNU LGPL and with code included
 *   in the standard release of OpenSSL under the OpenSSL License (or
 *   modified versions of such code, with unchanged license). You may copy
 *   and distribute such a system following the terms of the GNU GPL for
 *   stunnel and the licenses of the other code concerned.
 * 
 *   Note that people who make modified versions of stunnel are not obligated
 *   to grant this special exception for their modified versions; it is their
 *   choice whether to do so. The GNU General Public License gives permission
 *   to release a modified version without this exception; this exception
 *   also makes it possible to release a modified version which carries
 *   forward this exception.
 */

#include "common.h"
#include "prototypes.h"

#if !defined(OPENSSL_NO_TLS1)
#define DEFAULT_SSLVER_CLIENT "TLSv1"
#elif !defined(OPENSSL_NO_SSL3)
#define DEFAULT_SSLVER_CLIENT "SSLv3"
#elif !defined(OPENSSL_NO_SSL2)
#define DEFAULT_SSLVER_CLIENT "SSLv2"
#else /* OPENSSL_NO_TLS1, OPENSSL_NO_SSL3, OPENSSL_NO_SSL2 */
#error No supported SSL methods found
#endif /* OPENSSL_NO_TLS1, OPENSSL_NO_SSL3, OPENSSL_NO_SSL2 */
#define DEFAULT_SSLVER_SERVER "all"

#if defined(_WIN32_WCE) && !defined(CONFDIR)
#define CONFDIR "\\stunnel"
#endif

#ifdef USE_WIN32
#define CONFSEPARATOR "\\"
#else
#define CONFSEPARATOR "/"
#endif

#define CONFLINELEN (16*1024)

static void init_globals(void);
static int init_section(SERVICE_OPTIONS *);
#ifndef OPENSSL_NO_TLSEXT
static int init_sni(SERVICE_OPTIONS *);
#endif

static int parse_debug_level(char *);

static int parse_ssl_option(char *);

static int print_socket_options(void);
static char *print_option(int, OPT_UNION *);
static int parse_socket_option(char *);

#ifdef HAVE_OSSL_OCSP_H
static char *parse_ocsp_url(SERVICE_OPTIONS *, char *);
static unsigned long parse_ocsp_flag(char *);
#endif /* HAVE_OSSL_OCSP_H */

#ifdef HAVE_OSSL_ENGINE_H
static char *open_engine(const char *);
static char *ctrl_engine(const char *, const char *);
static char *init_engine(void);
static void close_engine(void);
static ENGINE *get_engine(int);
#endif

static void print_syntax(void);
static void config_error(int, const char *, const char *);
static void section_error(const char *, const char *);
#ifndef USE_WIN32
static char **argalloc(char *);
#endif

GLOBAL_OPTIONS global_options;
SERVICE_OPTIONS service_options;

static GLOBAL_OPTIONS new_global_options;
static SERVICE_OPTIONS new_service_options;

typedef enum {
    CMD_INIT, /* initialize */
    CMD_EXEC,
    CMD_DEFAULT,
    CMD_HELP
} CMD;

static char *option_not_found=
    "Specified option name is not valid here";

static char *stunnel_cipher_list=
    "ALL:!SSLv2:!aNULL:!EXP:!LOW:-MEDIUM:RC4:+HIGH";

/**************************************** global options */

static char *parse_global_option(CMD cmd, char *opt, char *arg) {
    char *tmpstr;
#ifndef USE_WIN32
    struct group *gr;
    struct passwd *pw;
#endif

    if(cmd==CMD_DEFAULT || cmd==CMD_HELP) {
        s_log(LOG_NOTICE, " ");
        s_log(LOG_NOTICE, "Global options:");
    }

    /* chroot */
#ifdef HAVE_CHROOT
    switch(cmd) {
    case CMD_INIT:
        new_global_options.chroot_dir=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "chroot"))
            break;
        new_global_options.chroot_dir=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = directory to chroot stunnel process", "chroot");
        break;
    }
#endif /* HAVE_CHROOT */

    /* compression */
#ifndef OPENSSL_NO_COMP
    switch(cmd) {
    case CMD_INIT:
        new_global_options.compression=COMP_NONE;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "compression"))
            break;
        if(SSLeay()>=0x00908051L && !strcasecmp(arg, "deflate"))
            new_global_options.compression=COMP_DEFLATE;
        else if(!strcasecmp(arg, "zlib"))
            new_global_options.compression=COMP_ZLIB;
        else if(!strcasecmp(arg, "rle"))
            new_global_options.compression=COMP_RLE;
        else
            return "Specified compression type is not available";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = compression type",
            "compression");
        break;
    }
#endif /* OPENSSL_NO_COMP */

    /* debug */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.debug_level=LOG_NOTICE;
#if !defined (USE_WIN32) && !defined (__vms)
        new_global_options.facility=LOG_DAEMON;
#endif
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "debug"))
            break;
        if(parse_debug_level(arg))
            return "Illegal debug argument";
        return NULL; /* OK */
    case CMD_DEFAULT:
#if !defined (USE_WIN32) && !defined (__vms)
        s_log(LOG_NOTICE, "%-15s = %s", "debug", "daemon.notice");
#else
        s_log(LOG_NOTICE, "%-15s = %s", "debug", "notice");
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = [facility].level (e.g. daemon.info)", "debug");
        break;
    }

    /* EGD */
    switch(cmd) {
    case CMD_INIT:
#ifdef EGD_SOCKET
        new_global_options.egd_sock=EGD_SOCKET;
#else
        new_global_options.egd_sock=NULL;
#endif
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "EGD"))
            break;
        new_global_options.egd_sock=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
#ifdef EGD_SOCKET
        s_log(LOG_NOTICE, "%-15s = %s", "EGD", EGD_SOCKET);
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = path to Entropy Gathering Daemon socket", "EGD");
        break;
    }

#ifdef HAVE_OSSL_ENGINE_H
    /* engine */
    switch(cmd) {
    case CMD_INIT:
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "engine"))
            break;
        return open_engine(arg);
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = auto|engine_id",
            "engine");
        break;
    }

    /* engineCtrl */
    switch(cmd) {
    case CMD_INIT:
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "engineCtrl"))
            break;
        tmpstr=strchr(arg, ':');
        if(tmpstr)
            *tmpstr++='\0';
        return ctrl_engine(arg, tmpstr);
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = cmd[:arg]",
            "engineCtrl");
        break;
    }
#endif

    /* fips */
#ifdef USE_FIPS
    switch(cmd) {
    case CMD_INIT:
        new_global_options.option.fips=1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "fips"))
            break;
        if(!strcasecmp(arg, "yes"))
            new_global_options.option.fips=1;
        else if(!strcasecmp(arg, "no"))
            new_global_options.option.fips=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no FIPS 140-2 mode",
            "fips");
        break;
    }
#endif /* USE_FIPS */

    /* foreground */
#ifndef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        new_global_options.option.foreground=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "foreground"))
            break;
        if(!strcasecmp(arg, "yes"))
            new_global_options.option.foreground=1;
        else if(!strcasecmp(arg, "no"))
            new_global_options.option.foreground=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no foreground mode (don't fork, log to stderr)",
            "foreground");
        break;
    }
#endif

    /* output */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.output_file=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "output"))
            break;
        new_global_options.output_file=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = file to append log messages", "output");
        break;
    }

    /* pid */
#ifndef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        new_global_options.pidfile=PIDFILE;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "pid"))
            break;
        if(arg[0]) /* is argument not empty? */
            new_global_options.pidfile=str_dup(arg);
        else
            new_global_options.pidfile=NULL; /* empty -> do not create a pid file */
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %s", "pid", PIDFILE);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = pid file (empty to disable creating)", "pid");
        break;
    }
#endif

    /* RNDbytes */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.random_bytes=RANDOM_BYTES;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "RNDbytes"))
            break;
        new_global_options.random_bytes=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal number of bytes to read from random seed files";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d", "RNDbytes", RANDOM_BYTES);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = bytes to read from random seed files", "RNDbytes");
        break;
    }

    /* RNDfile */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.rand_file=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "RNDfile"))
            break;
        new_global_options.rand_file=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
#ifdef RANDOM_FILE
        s_log(LOG_NOTICE, "%-15s = %s", "RNDfile", RANDOM_FILE);
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = path to file with random seed data", "RNDfile");
        break;
    }

    /* RNDoverwrite */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.option.rand_write=1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "RNDoverwrite"))
            break;
        if(!strcasecmp(arg, "yes"))
            new_global_options.option.rand_write=1;
        else if(!strcasecmp(arg, "no"))
            new_global_options.option.rand_write=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = yes", "RNDoverwrite");
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no overwrite seed datafiles with new random data",
            "RNDoverwrite");
        break;
    }

#ifndef USE_WIN32
    /* service */
    switch(cmd) {
    case CMD_INIT:
        new_service_options.servname=str_dup("stunnel");
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "service"))
            break;
        new_service_options.servname=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = service name", "service");
        break;
    }
#endif

#ifndef USE_WIN32
    /* setgid */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.gid=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "setgid"))
            break;
        gr=getgrnam(arg);
        if(gr) {
            new_global_options.gid=gr->gr_gid;
            return NULL; /* OK */
        }
        new_global_options.gid=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal GID";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = groupname for setgid()", "setgid");
        break;
    }
#endif

#ifndef USE_WIN32
    /* setuid */
    switch(cmd) {
    case CMD_INIT:
        new_global_options.uid=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "setuid"))
            break;
        pw=getpwnam(arg);
        if(pw) {
            new_global_options.uid=pw->pw_uid;
            return NULL; /* OK */
        }
        new_global_options.uid=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal UID";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = username for setuid()", "setuid");
        break;
    }
#endif

    /* socket */
    switch(cmd) {
    case CMD_INIT:
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "socket"))
            break;
        if(parse_socket_option(arg))
            return "Illegal socket option";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = a|l|r:option=value[:value]", "socket");
        s_log(LOG_NOTICE, "%18sset an option on accept/local/remote socket", "");
        break;
    }

    /* syslog */
#ifndef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        new_global_options.option.syslog=1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "syslog"))
            break;
        if(!strcasecmp(arg, "yes"))
            new_global_options.option.syslog=1;
        else if(!strcasecmp(arg, "no"))
            new_global_options.option.syslog=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no send logging messages to syslog",
            "syslog");
        break;
    }
#endif

    /* taskbar */
#ifdef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        new_global_options.option.taskbar=1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "taskbar"))
            break;
        if(!strcasecmp(arg, "yes"))
            new_global_options.option.taskbar=1;
        else if(!strcasecmp(arg, "no"))
            new_global_options.option.taskbar=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = yes", "taskbar");
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no enable the taskbar icon", "taskbar");
        break;
    }
#endif

    if(cmd==CMD_EXEC)
        return option_not_found;
    return NULL; /* OK */
}

/**************************************** service-level options */

static char *parse_service_option(CMD cmd, SERVICE_OPTIONS *section,
        char *opt, char *arg) {
    char *tmpstr;
    int tmpnum;

    if(cmd==CMD_DEFAULT || cmd==CMD_HELP) {
        s_log(LOG_NOTICE, " ");
        s_log(LOG_NOTICE, "Service-level options:");
    }

    /* accept */
    switch(cmd) {
    case CMD_INIT:
        section->option.accept=0;
        memset(&section->local_addr, 0, sizeof(SOCKADDR_UNION));
        section->local_addr.in.sin_family=AF_INET;
        section->fd=-1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "accept"))
            break;
        section->option.accept=1;
        if(!name2addr(&section->local_addr, arg, DEFAULT_ANY))
            return "Failed to resolve accepting address";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = [host:]port accept connections on specified host:port",
            "accept");
        break;
    }

    /* CApath */
    switch(cmd) {
    case CMD_INIT:
#if 0
        section->ca_dir=(char *)X509_get_default_cert_dir();
#endif
        section->ca_dir=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "CApath"))
            break;
        if(arg[0]) /* not empty */
            section->ca_dir=str_dup(arg);
        else
            section->ca_dir=NULL;
        return NULL; /* OK */
    case CMD_DEFAULT:
#if 0
        s_log(LOG_NOTICE, "%-15s = %s", "CApath",
            section->ca_dir ? section->ca_dir : "(none)");
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = CA certificate directory for 'verify' option",
            "CApath");
        break;
    }

    /* CAfile */
    switch(cmd) {
    case CMD_INIT:
#if 0
        section->ca_file=(char *)X509_get_default_certfile();
#endif
        section->ca_file=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "CAfile"))
            break;
        if(arg[0]) /* not empty */
            section->ca_file=str_dup(arg);
        else
            section->ca_file=NULL;
        return NULL; /* OK */
    case CMD_DEFAULT:
#if 0
        s_log(LOG_NOTICE, "%-15s = %s", "CAfile",
            section->ca_file ? section->ca_file : "(none)");
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = CA certificate file for 'verify' option",
            "CAfile");
        break;
    }

    /* cert */
    switch(cmd) {
    case CMD_INIT:
        section->cert=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "cert"))
            break;
        section->cert=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break; /* no default certificate */
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = certificate chain", "cert");
        break;
    }

    /* ciphers */
    switch(cmd) {
    case CMD_INIT:
        section->cipher_list=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "ciphers"))
            break;
        section->cipher_list=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
#ifdef USE_FIPS
        s_log(LOG_NOTICE, "%-15s = %s %s", "ciphers",
            "FIPS", "(with \"fips = yes\")");
        s_log(LOG_NOTICE, "%-15s = %s %s", "ciphers",
            stunnel_cipher_list, "(with \"fips = no\")");
#else
        s_log(LOG_NOTICE, "%-15s = %s", "ciphers", stunnel_cipher_list);
#endif /* USE_FIPS */
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = list of permitted SSL ciphers", "ciphers");
        break;
    }

    /* client */
    switch(cmd) {
    case CMD_INIT:
        section->option.client=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "client"))
            break;
        if(!strcasecmp(arg, "yes"))
            section->option.client=1;
        else if(!strcasecmp(arg, "no"))
            section->option.client=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no client mode (remote service uses SSL)",
            "client");
        break;
    }

    /* connect */
    switch(cmd) {
    case CMD_INIT:
        section->option.remote=0;
        section->connect_name=NULL;
        section->connect_addr.num=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "connect"))
            break;
        section->option.remote=1;
        section->connect_name=str_dup(arg);
        if(!section->option.delayed_lookup &&
                !name2addrlist(&section->connect_addr, arg, DEFAULT_LOOPBACK)) {
            s_log(LOG_INFO, "Cannot resolve '%s' - delaying DNS lookup", arg);
            section->option.delayed_lookup=1;
        }
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = [host:]port connect remote host:port",
            "connect");
        break;
    }

    /* CRLpath */
    switch(cmd) {
    case CMD_INIT:
        section->crl_dir=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "CRLpath"))
            break;
        if(arg[0]) /* not empty */
            section->crl_dir=str_dup(arg);
        else
            section->crl_dir=NULL;
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = CRL directory", "CRLpath");
        break;
    }

    /* CRLfile */
    switch(cmd) {
    case CMD_INIT:
        section->crl_file=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "CRLfile"))
            break;
        if(arg[0]) /* not empty */
            section->crl_file=str_dup(arg);
        else
            section->crl_file=NULL;
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = CRL file", "CRLfile");
        break;
    }

#ifndef OPENSSL_NO_ECDH

    /* curve */
#define DEFAULT_CURVE NID_X9_62_prime256v1
    switch(cmd) {
    case CMD_INIT:
        section->curve=DEFAULT_CURVE;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "curve"))
            break;
        section->curve=OBJ_txt2nid(arg);
        if(section->curve==NID_undef)
            return "Curve name not supported";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %s", "curve", OBJ_nid2ln(DEFAULT_CURVE));
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = ECDH curve name", "curve");
        break;
    }

#endif /* !OPENSSL_NO_ECDH */

    /* delay */
    switch(cmd) {
    case CMD_INIT:
        section->option.delayed_lookup=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "delay"))
            break;
        if(!strcasecmp(arg, "yes"))
            section->option.delayed_lookup=1;
        else if(!strcasecmp(arg, "no"))
            section->option.delayed_lookup=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no delay DNS lookup for 'connect' option",
            "delay");
        break;
    }

#ifdef HAVE_OSSL_ENGINE_H
    /* engineNum */
    switch(cmd) {
    case CMD_INIT:
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "engineNum"))
            break;
        tmpnum=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal engine number";
        section->engine=get_engine(tmpnum);
        if(!section->engine)
            return "Illegal engine number";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = number of engine to read the key from",
            "engineNum");
        break;
    }
#endif

    /* exec */
    switch(cmd) {
    case CMD_INIT:
        section->option.program=0;
        section->execname=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "exec"))
            break;
        section->option.program=1;
        section->execname=str_dup(arg);
#ifdef USE_WIN32
        section->execargs=str_dup(arg);
#else
        if(!section->execargs) {
            section->execargs=str_alloc(2*sizeof(char *));
            section->execargs[0]=section->execname;
            section->execargs[1]=NULL; /* to show that it's null-terminated */
        }
#endif
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = file execute local inetd-type program",
            "exec");
        break;
    }

    /* execargs */
    switch(cmd) {
    case CMD_INIT:
        section->execargs=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "execargs"))
            break;
#ifdef USE_WIN32
        section->execargs=str_dup(arg);
#else
        section->execargs=argalloc(arg);
#endif
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = arguments for 'exec' (including $0)",
            "execargs");
        break;
    }

    /* failover */
    switch(cmd) {
    case CMD_INIT:
        section->failover=FAILOVER_RR;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "failover"))
            break;
        if(!strcasecmp(arg, "rr"))
            section->failover=FAILOVER_RR;
        else if(!strcasecmp(arg, "prio"))
            section->failover=FAILOVER_PRIO;
        else
            return "Argument should be either 'rr' or 'prio'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = rr|prio failover strategy",
            "failover");
        break;
    }

    /* ident */
    switch(cmd) {
    case CMD_INIT:
        section->username=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "ident"))
            break;
        section->username=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = username for IDENT (RFC 1413) checking", "ident");
        break;
    }

    /* key */
    switch(cmd) {
    case CMD_INIT:
        section->key=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "key"))
            break;
        section->key=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = certificate private key", "key");
        break;
    }

#ifdef USE_LIBWRAP
    switch(cmd) {
    case CMD_INIT:
        section->option.libwrap=1; /* enable libwrap by default */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "libwrap"))
            break;
        if(!strcasecmp(arg, "yes"))
            section->option.libwrap=1;
        else if(!strcasecmp(arg, "no"))
            section->option.libwrap=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no use /etc/hosts.allow and /etc/hosts.deny",
            "libwrap");
        break;
    }
#endif /* USE_LIBWRAP */

    /* local */
    switch(cmd) {
    case CMD_INIT:
        section->option.local=0;
        memset(&section->source_addr, 0, sizeof(SOCKADDR_UNION));
        section->source_addr.in.sin_family=AF_INET;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "local"))
            break;
        section->option.local=1;
        if(!hostport2addr(&section->source_addr, arg, "0"))
            return "Failed to resolve local address";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = IP address to be used as source for remote"
            " connections", "local");
        break;
    }

#ifdef HAVE_OSSL_OCSP_H

    /* OCSP */
    switch(cmd) {
    case CMD_INIT:
        section->option.ocsp=0;
        memset(&section->ocsp_addr, 0, sizeof(SOCKADDR_UNION));
        section->ocsp_addr.in.sin_family=AF_INET;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "ocsp"))
            break;
        section->option.ocsp=1;
        return parse_ocsp_url(section, arg);
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = OCSP server URL", "ocsp");
        break;
    }

    /* OCSPflag */
    switch(cmd) {
    case CMD_INIT:
        section->ocsp_flags=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "OCSPflag"))
            break;
        tmpnum=parse_ocsp_flag(arg);
        if(!tmpnum)
            return "Illegal OCSP flag";
        section->ocsp_flags|=tmpnum;
        return NULL;
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = OCSP server flags", "OCSPflag");
        break;
    }

#endif /* HAVE_OSSL_OCSP_H */

    /* options */
    switch(cmd) {
    case CMD_INIT:
        section->ssl_options=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "options"))
            break;
        tmpnum=parse_ssl_option(arg);
        if(!tmpnum)
            return "Illegal SSL option";
        section->ssl_options|=tmpnum;
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = SSL option", "options");
        s_log(LOG_NOTICE, "%18sset an SSL option", "");
        break;
    }

    /* protocol */
    switch(cmd) {
    case CMD_INIT:
        section->protocol=-1;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "protocol"))
            break;
        section->protocol=find_protocol_id(arg);
        if(section->protocol<0)
            return "Unknown protocol";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = protocol to negotiate before SSL initialization",
            "protocol");
        s_log(LOG_NOTICE, "%18scurrently supported: cifs, connect, imap, nntp, pgsql, pop3, proxy, smtp", "");
        break;
    }

    /* protocolAuthentication */
    switch(cmd) {
    case CMD_INIT:
        section->protocol_authentication="basic";
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "protocolAuthentication"))
            break;
        section->protocol_authentication=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = authentication type for protocol negotiations",
            "protocolAuthentication");
        break;
    }

    /* protocolHost */
    switch(cmd) {
    case CMD_INIT:
        section->protocol_host=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "protocolHost"))
            break;
        section->protocol_host=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = host:port for protocol negotiations",
            "protocolHost");
        break;
    }

    /* protocolPassword */
    switch(cmd) {
    case CMD_INIT:
        section->protocol_password=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "protocolPassword"))
            break;
        section->protocol_password=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = password for protocol negotiations",
            "protocolPassword");
        break;
    }

    /* protocolUsername */
    switch(cmd) {
    case CMD_INIT:
        section->protocol_username=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "protocolUsername"))
            break;
        section->protocol_username=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = username for protocol negotiations",
            "protocolUsername");
        break;
    }

    /* pty */
#ifndef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        section->option.pty=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "pty"))
            break;
        if(!strcasecmp(arg, "yes"))
            section->option.pty=1;
        else if(!strcasecmp(arg, "no"))
            section->option.pty=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no allocate pseudo terminal for 'exec' option",
            "pty");
        break;
    }
#endif

    /* retry */
    switch(cmd) {
    case CMD_INIT:
        section->option.retry=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "retry"))
            break;
        if(!strcasecmp(arg, "yes"))
            section->option.retry=1;
        else if(!strcasecmp(arg, "no"))
            section->option.retry=0;
        else
            return "Argument should be either 'yes' or 'no'";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = yes|no retry connect+exec section",
            "retry");
        break;
    }

    /* session */
    switch(cmd) {
    case CMD_INIT:
        section->session_timeout=300L;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "session"))
            break;
        section->session_timeout=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal session timeout";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %ld seconds", "session", 300L);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = session cache timeout (in seconds)", "session");
        break;
    }

    /* sessiond */
    switch(cmd) {
    case CMD_INIT:
        section->option.sessiond=0;
        memset(&section->sessiond_addr, 0, sizeof(SOCKADDR_UNION));
        section->sessiond_addr.in.sin_family=AF_INET;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "sessiond"))
            break;
        section->option.sessiond=1;
#ifdef SSL_OP_NO_TICKET
        /* disable RFC4507 support introduced in OpenSSL 0.9.8f */
        /* this prevents session callbacks from beeing executed */
        section->ssl_options|=SSL_OP_NO_TICKET;
#endif
        if(!name2addr(&section->sessiond_addr, arg, DEFAULT_LOOPBACK))
            return "Failed to resolve sessiond server address";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = [host:]port use sessiond at host:port",
            "sessiond");
        break;
    }

#ifndef OPENSSL_NO_TLSEXT
    /* sni */
    switch(cmd) {
    case CMD_INIT:
        section->servername_list_head=NULL;
        section->servername_list_tail=NULL;
        section->option.sni=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "sni"))
            break;
        section->sni=str_dup(arg);
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = master_service:host_name for an SNI virtual service",
            "sni");
        break;
    }
#endif /* OPENSSL_NO_TLSEXT */

    /* sslVersion */
    switch(cmd) {
    case CMD_INIT:
        section->client_method=NULL;
        section->server_method=NULL;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "sslVersion"))
            break;
        if(!strcasecmp(arg, "all")) {
            section->client_method=(SSL_METHOD *)SSLv23_client_method();
            section->server_method=(SSL_METHOD *)SSLv23_server_method();
        } else if(!strcasecmp(arg, "SSLv2")) {
#if !defined(OPENSSL_NO_SSL2)
            section->client_method=(SSL_METHOD *)SSLv2_client_method();
            section->server_method=(SSL_METHOD *)SSLv2_server_method();
#else
            return "SSLv2 not supported";
#endif
        } else if(!strcasecmp(arg, "SSLv3")) {
#if !defined(OPENSSL_NO_SSL3)
            section->client_method=(SSL_METHOD *)SSLv3_client_method();
            section->server_method=(SSL_METHOD *)SSLv3_server_method();
#else
            return "SSLv3 not supported";
#endif
        } else if(!strcasecmp(arg, "TLSv1")) {
#if !defined(OPENSSL_NO_TLS1)
            section->client_method=(SSL_METHOD *)TLSv1_client_method();
            section->server_method=(SSL_METHOD *)TLSv1_server_method();
#else
            return "TLSv1 not supported";
#endif
        } else if(!strcasecmp(arg, "TLSv1.2")) {
#if !defined(OPENSSL_NO_TLS1)
            section->client_method=(SSL_METHOD *)TLSv1_2_client_method();
            section->server_method=(SSL_METHOD *)TLSv1_2_server_method();
#else
            return "TLSv1.2 not supported";
#endif
        } else
            return "Incorrect version of SSL protocol";
        return NULL; /* OK */
    case CMD_DEFAULT:
#ifdef USE_FIPS
        s_log(LOG_NOTICE, "%-15s = TLSv1 (with \"fips = yes\")",
                "sslVersion");
        s_log(LOG_NOTICE, "%-15s = " DEFAULT_SSLVER_CLIENT " for client, "
                DEFAULT_SSLVER_SERVER " for server (with \"fips = no\")",
                "sslVersion");
#else
        s_log(LOG_NOTICE, "%-15s = " DEFAULT_SSLVER_CLIENT " for client, "
                DEFAULT_SSLVER_SERVER " for server", "sslVersion");
#endif
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = all|SSLv2|SSLv3|TLSv1 SSL method", "sslVersion");
        break;
    }

#ifndef USE_FORK
    /* stack */
    switch(cmd) {
    case CMD_INIT:
        section->stack_size=DEFAULT_STACK_SIZE;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "stack"))
            break;
        section->stack_size=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal thread stack size";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d bytes", "stack", DEFAULT_STACK_SIZE);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = thread stack size (in bytes)", "stack");
        break;
    }
#endif

    /* TIMEOUTbusy */
    switch(cmd) {
    case CMD_INIT:
        section->timeout_busy=300; /* 5 minutes */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "TIMEOUTbusy"))
            break;
        section->timeout_busy=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal busy timeout";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d seconds", "TIMEOUTbusy", 300);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = seconds to wait for expected data", "TIMEOUTbusy");
        break;
    }

    /* TIMEOUTclose */
    switch(cmd) {
    case CMD_INIT:
        section->timeout_close=60; /* 1 minute */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "TIMEOUTclose"))
            break;
        section->timeout_close=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal close timeout";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d seconds", "TIMEOUTclose", 60);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = seconds to wait for close_notify"
            " (set to 0 for buggy MSIE)", "TIMEOUTclose");
        break;
    }

    /* TIMEOUTconnect */
    switch(cmd) {
    case CMD_INIT:
        section->timeout_connect=10; /* 10 seconds */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "TIMEOUTconnect"))
            break;
        section->timeout_connect=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal connect timeout";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d seconds", "TIMEOUTconnect", 10);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = seconds to connect remote host", "TIMEOUTconnect");
        break;
    }

    /* TIMEOUTidle */
    switch(cmd) {
    case CMD_INIT:
        section->timeout_idle=43200; /* 12 hours */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "TIMEOUTidle"))
            break;
        section->timeout_idle=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Illegal idle timeout";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = %d seconds", "TIMEOUTidle", 43200);
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE, "%-15s = seconds to keep an idle connection", "TIMEOUTidle");
        break;
    }

    /* transparent */
#ifndef USE_WIN32
    switch(cmd) {
    case CMD_INIT:
        section->option.transparent_src=0;
        section->option.transparent_dst=0;
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "transparent"))
            break;
        if(!strcasecmp(arg, "none") || !strcasecmp(arg, "no")) {
            section->option.transparent_src=0;
            section->option.transparent_dst=0;
        } else if(!strcasecmp(arg, "source") || !strcasecmp(arg, "yes")) {
            section->option.transparent_src=1;
            section->option.transparent_dst=0;
#ifdef SO_ORIGINAL_DST
        } else if(!strcasecmp(arg, "destination")) {
            section->option.transparent_src=0;
            section->option.transparent_dst=1;
        } else if(!strcasecmp(arg, "both")) {
            section->option.transparent_src=1;
            section->option.transparent_dst=1;
#endif
        } else
            return "Selected transparent proxy mode is not available";
        return NULL; /* OK */
    case CMD_DEFAULT:
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE,
            "%-15s = none|source|destination|both transparent proxy mode",
            "transparent");
        break;
    }
#endif

    /* verify */
    switch(cmd) {
    case CMD_INIT:
        section->verify_level=-1; /* do not even request a certificate */
        break;
    case CMD_EXEC:
        if(strcasecmp(opt, "verify"))
            break;
        section->verify_level=strtol(arg, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return "Bad verify level";
        if(section->verify_level<0 || section->verify_level>4)
            return "Bad verify level";
        return NULL; /* OK */
    case CMD_DEFAULT:
        s_log(LOG_NOTICE, "%-15s = none", "verify");
        break;
    case CMD_HELP:
        s_log(LOG_NOTICE,
            "%-15s = level of peer certificate verification", "verify");
        s_log(LOG_NOTICE,
            "%18slevel 0 - request and ignore peer certificate", "");
        s_log(LOG_NOTICE,
            "%18slevel 1 - only validate peer certificate if present", "");
        s_log(LOG_NOTICE,
            "%18slevel 2 - always require a valid peer certificate", "");
        s_log(LOG_NOTICE,
            "%18slevel 3 - verify peer with locally installed certificate", "");
        s_log(LOG_NOTICE,
            "%18slevel 4 - ignore CA chain and only verify peer certificate", "");
        break;
    }

    if(cmd==CMD_EXEC)
        return option_not_found;
    return NULL; /* OK */
}

/**************************************** parse commandline parameters */

int parse_commandline(char *name, char *parameter) {
    if(!name)
#ifdef CONFDIR
        name=CONFDIR CONFSEPARATOR "stunnel.conf";
#else
        name="stunnel.conf";
#endif

    if(!strcasecmp(name, "-help")) {
        parse_global_option(CMD_HELP, NULL, NULL);
        parse_service_option(CMD_HELP, NULL, NULL, NULL);
        log_flush(LOG_MODE_INFO);
        return 1;
    }

    if(!strcasecmp(name, "-version")) {
        parse_global_option(CMD_DEFAULT, NULL, NULL);
        parse_service_option(CMD_DEFAULT, NULL, NULL, NULL);
        log_flush(LOG_MODE_INFO);
        return 1;
    }

    if(!strcasecmp(name, "-sockets")) {
        print_socket_options();
        log_flush(LOG_MODE_INFO);
        return 1;
    }

#ifndef USE_WIN32
    if(!strcasecmp(name, "-fd")) {
        if(!parameter) {
            s_log(LOG_ERR, "No file descriptor specified");
            print_syntax();
            return 1;
        }
        if(parse_conf(parameter, CONF_FD))
            return 1;
    } else
#else
    (void)parameter; /* skip warning about unused parameter */
#endif
        if(parse_conf(name, CONF_FILE))
            return 1;
    apply_conf();
    return 0;
}

/**************************************** parse configuration file */

int parse_conf(char *name, CONF_TYPE type) {
    DISK_FILE *df;
    char line_text[CONFLINELEN], *errstr;
    char config_line[CONFLINELEN], *config_opt, *config_arg;
    int line_number, i;
    SERVICE_OPTIONS *section, *new_section;
    static char *filename=NULL; /* a copy of config file name for reloading */
#ifndef USE_WIN32
    int fd;
    char *tmpstr;
#endif

    if(name) /* not reload */
        filename=str_dup(name);

    s_log(LOG_NOTICE, "Reading configuration from %s %s",
        type==CONF_FD ? "descriptor" : "file", filename);
#ifndef USE_WIN32
    if(type==CONF_FD) { /* file descriptor */
        fd=strtol(filename, &tmpstr, 10);
        if(tmpstr==filename || *tmpstr) { /* not a number */
            s_log(LOG_ERR, "Invalid file descriptor number");
            print_syntax();
            return 1;
        }
        df=file_fdopen(fd);
    } else
#endif
        df=file_open(filename, 0);
    if(!df) {
        s_log(LOG_ERR, "Cannot read configuration");
        if(type!=CONF_RELOAD)
            print_syntax();
        return 1;
    }

    memset(&new_global_options, 0, sizeof(GLOBAL_OPTIONS)); /* reset global options */
    memset(&new_service_options, 0, sizeof(SERVICE_OPTIONS)); /* reset local options */
    new_service_options.next=NULL;
    section=&new_service_options;
    parse_global_option(CMD_INIT, NULL, NULL);
    parse_service_option(CMD_INIT, section, NULL, NULL);
    if(type!=CONF_RELOAD) { /* provide defaults for gui.c */
        memcpy(&global_options, &new_global_options, sizeof(GLOBAL_OPTIONS));
        memcpy(&service_options, &new_service_options, sizeof(SERVICE_OPTIONS));
    }

    line_number=0;
    while(file_getline(df, line_text, CONFLINELEN)>=0) {
        memcpy(config_line, line_text, CONFLINELEN);
        ++line_number;
        config_opt=config_line;
        while(isspace((unsigned char)*config_opt))
            ++config_opt; /* remove initial whitespaces */
        for(i=strlen(config_opt)-1; i>=0 && isspace((unsigned char)config_opt[i]); --i)
            config_opt[i]='\0'; /* remove trailing whitespaces */
        if(config_opt[0]=='\0' || config_opt[0]=='#' || config_opt[0]==';') /* empty or comment */
            continue;
        if(config_opt[0]=='[' && config_opt[strlen(config_opt)-1]==']') { /* new section */
            if(!new_service_options.next) {
                /* FIPS needs to be initialized as early as possible */
                if(ssl_configure(&new_global_options)) { /* configure global SSL settings */
                    file_close(df);
                    return 1;
                }
                init_globals(); /* defaults need to be set before other options are parsed */
            }
            ++config_opt;
            config_opt[strlen(config_opt)-1]='\0';
            new_section=str_alloc(sizeof(SERVICE_OPTIONS));
            memcpy(new_section, &new_service_options, sizeof(SERVICE_OPTIONS));
            new_section->servname=str_dup(config_opt);
            new_section->session=NULL;
            new_section->next=NULL;
            section->next=new_section;
            section=new_section;
            continue;
        }
        config_arg=strchr(config_line, '=');
        if(!config_arg) {
            config_error(line_number, line_text, "No '=' found");
            file_close(df);
            return 1;
        }
        *config_arg++='\0'; /* split into option name and argument value */
        for(i=strlen(config_opt)-1; i>=0 && isspace((unsigned char)config_opt[i]); --i)
            config_opt[i]='\0'; /* remove trailing whitespaces */
        while(isspace((unsigned char)*config_arg))
            ++config_arg; /* remove initial whitespaces */
        errstr=parse_service_option(CMD_EXEC, section, config_opt, config_arg);
        if(!new_service_options.next && errstr==option_not_found)
            errstr=parse_global_option(CMD_EXEC, config_opt, config_arg);
        if(errstr) {
            config_error(line_number, line_text, errstr);
            file_close(df);
            return 1;
        }
    }
    file_close(df);

    if(new_service_options.next) { /* daemon mode: initialize sections */
        for(section=new_service_options.next; section; section=section->next) {
            s_log(LOG_INFO, "Initializing service section [%s]", section->servname);
            if(init_section(section))
                return 1;
        }
    } else { /* inetd mode: need to initialize global options */
        if(ssl_configure(&new_global_options)) /* configure global SSL settings */
            return 1;
        init_globals();
        s_log(LOG_INFO, "Initializing inetd mode configuration");
        if(init_section(&new_service_options))
            return 1;
    }

    s_log(LOG_NOTICE, "Configuration successful");
    return 0;
}

void apply_conf() { /* can be used once the configuration was validated */
    /* FIXME: this operation may be unsafe, as client() threads use it */
    memcpy(&global_options, &new_global_options, sizeof(GLOBAL_OPTIONS));
    /* service_options are used for inetd mode and to enumerate services */
    memcpy(&service_options, &new_service_options, sizeof(SERVICE_OPTIONS));
#ifdef USE_WIN32
    PostMessage(hwnd, WM_VALID_CONFIG, 0, 0);
#endif
}

/**************************************** validate and initialize configuration */

static void init_globals() {
#ifdef HAVE_OSSL_ENGINE_H
    close_engine();
#endif

    /* prepare default SSL methods */
#ifdef USE_FIPS
    if(new_global_options.option.fips) {
        if(!new_service_options.cipher_list)
            new_service_options.cipher_list="FIPS";
        if(!new_service_options.client_method)
            new_service_options.client_method=(SSL_METHOD *)TLSv1_client_method();
        if(!new_service_options.server_method)
            new_service_options.server_method=(SSL_METHOD *)TLSv1_server_method();
        return;
    }
#endif /* USE_FIPS */
    if(!new_service_options.cipher_list)
        new_service_options.cipher_list=stunnel_cipher_list;
    if(!new_service_options.client_method)
#if !defined(OPENSSL_NO_TLS1)
        new_service_options.client_method=(SSL_METHOD *)TLSv1_client_method();
#elif !defined(OPENSSL_NO_SSL3)
        new_service_options.client_method=(SSL_METHOD *)SSLv3_client_method();
#elif !defined(OPENSSL_NO_SSL2)
        new_service_options.client_method=(SSL_METHOD *)SSLv2_client_method();
#else /* OPENSSL_NO_TLS1, OPENSSL_NO_SSL3, OPENSSL_NO_SSL2 */
#error No supported SSL methods found
#endif /* OPENSSL_NO_TLS1, OPENSSL_NO_SSL3, OPENSSL_NO_SSL2 */
    /* SSLv23_server_method() is an always available catch-all */
    if(!new_service_options.server_method)
        new_service_options.server_method=(SSL_METHOD *)SSLv23_server_method();
}

static int init_section(SERVICE_OPTIONS *section) {
#ifdef USE_FIPS
    if(new_global_options.option.fips &&
            ((section->option.client &&
                section->client_method!=(SSL_METHOD *)TLSv1_client_method()) ||
            (!section->option.client &&
                section->server_method!=(SSL_METHOD *)TLSv1_server_method()))) {
        section_error(section->servname, "sslVersion = TLSv1 is required in FIPS mode");
        return 1;
    }
#endif /* USE_FIPS */
    if(!section->option.client && !section->cert) {
        section_error(section->servname, "SSL server needs a certificate");
        return 1;
    }
#ifndef OPENSSL_NO_TLSEXT
    if(init_sni(section))
        return 1;
#endif
    if(context_init(section)) /* initialize SSL context */
        return 1;

    if(new_service_options.next) { /* daemon mode checks */
        if((unsigned int)section->option.accept
                + (unsigned int)section->option.program
                + (unsigned int)section->option.remote
#ifndef OPENSSL_NO_TLSEXT
                + (unsigned int)section->option.sni
#endif /* OPENSSL_NO_TLSEXT */
#ifndef USE_WIN32
                + (unsigned int)section->option.transparent_dst
#endif /* USE_WIN32 */
                !=2) {
            section_error(section->servname, "Each service must define two endpoints");
            return 1;
        }
    } else { /* inetd mode checks */
        if(section->option.accept) {
            s_log(LOG_ERR, "Accept option is not allowed in inetd mode");
            s_log(LOG_ERR, "Remove accept option or define a [section]");
            return 1;
        }
        if(!section->option.remote && !section->execname) {
            s_log(LOG_ERR, "Inetd mode must have 'connect' or 'exec' options");
            return 1;
        }
#if 0
        /* TODO: some additional checks could be useful */
        if((unsigned int)section->option.program +
                (unsigned int)section->option.remote != 1)
            section_error(section->servname, "Single endpoint is required in inetd mode");
#endif
    }
    return 0; /* all tests passed -- continue program execution */
}

#ifndef OPENSSL_NO_TLSEXT
static int init_sni(SERVICE_OPTIONS *section) {
    char *tmpstr;
    SERVICE_OPTIONS *tmpsrv;

    /* server mode: update servername_list based on SNI option */
    if(!section->option.client && section->sni) {
        tmpstr=strchr(section->sni, ':');
        if(!tmpstr) {
            section_error(section->servname, "Invalid SNI parameter format");
            return 1;
        }
        *tmpstr++='\0';
        for(tmpsrv=new_service_options.next; tmpsrv; tmpsrv=tmpsrv->next)
            if(!strcmp(tmpsrv->servname, section->sni))
                break;
        if(!tmpsrv) {
            section_error(section->servname, "SNI section name not found");
            return 1;
        }
        if(tmpsrv->option.client) {
            section_error(section->servname, "SNI master service is a TLS client");
            return 1;
        }
        if(tmpsrv->servername_list_tail) {
            tmpsrv->servername_list_tail->next=str_alloc(sizeof(SERVERNAME_LIST));
            tmpsrv->servername_list_tail=tmpsrv->servername_list_tail->next;
        } else { /* first virtual service */
            tmpsrv->servername_list_head=
                tmpsrv->servername_list_tail=
                str_alloc(sizeof(SERVERNAME_LIST));
            tmpsrv->ssl_options|=SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION;
        }
        tmpsrv->servername_list_tail->servername=str_dup(tmpstr);
        tmpsrv->servername_list_tail->opt=section;
        tmpsrv->servername_list_tail->next=NULL;
        section->option.sni=1;
        /* always negotiate a new session on renegotiation, as the SSL
         * context settings (including access control) may be different */
        section->ssl_options|=SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION;
    }

    /* client mode: setup SNI default based on 'protocolHost' and 'connect' options */
    if(section->option.client && !section->sni) {
        /* setup host_name for SNI, prefer SNI and protocolHost if specified */
        if(section->protocol_host) /* 'protocolHost' option */
            section->sni=str_dup(section->protocol_host);
        else if(section->connect_name) /* 'connect' option */
            section->sni=str_dup(section->connect_name);
        if(section->sni) { /* either 'protocolHost' or 'connect' specified */
            tmpstr=strrchr(section->sni, ':');
            if(tmpstr) { /* 'host:port' -> drop ':port' */
                *tmpstr='\0';
            } else { /* 'port' -> default to 'localhost' */
                str_free(section->sni);
                section->sni=str_dup("localhost");
            }
        }
    }
    return 0;
}
#endif /* OPENSSL_NO_TLSEXT */

/**************************************** facility/debug level */

typedef struct {
    char *name;
    int value;
} facilitylevel;

static int parse_debug_level(char *arg) {
    char *arg_copy;
    char *string;
    facilitylevel *fl;

/* facilities only make sense on unix */
#if !defined (USE_WIN32) && !defined (__vms)
    facilitylevel facilities[] = {
        {"auth", LOG_AUTH},     {"cron", LOG_CRON},     {"daemon", LOG_DAEMON},
        {"kern", LOG_KERN},     {"lpr", LOG_LPR},       {"mail", LOG_MAIL},
        {"news", LOG_NEWS},     {"syslog", LOG_SYSLOG}, {"user", LOG_USER},
        {"uucp", LOG_UUCP},     {"local0", LOG_LOCAL0}, {"local1", LOG_LOCAL1},
        {"local2", LOG_LOCAL2}, {"local3", LOG_LOCAL3}, {"local4", LOG_LOCAL4},
        {"local5", LOG_LOCAL5}, {"local6", LOG_LOCAL6}, {"local7", LOG_LOCAL7},

        /* some that are not on all unicies */
#ifdef LOG_AUTHPRIV
        {"authpriv", LOG_AUTHPRIV},
#endif
#ifdef LOG_FTP
        {"ftp", LOG_FTP},
#endif
#ifdef LOG_NTP
        {"ntp", LOG_NTP},
#endif
        {NULL, 0}
    };
#endif /* USE_WIN32, __vms */

    facilitylevel levels[] = {
        {"emerg", LOG_EMERG},     {"alert", LOG_ALERT},
        {"crit", LOG_CRIT},       {"err", LOG_ERR},
        {"warning", LOG_WARNING}, {"notice", LOG_NOTICE},
        {"info", LOG_INFO},       {"debug", LOG_DEBUG},
        {NULL, -1}
    };

    arg_copy=str_dup(arg);
    string=arg_copy;

/* facilities only make sense on Unix */
#if !defined (USE_WIN32) && !defined (__vms)
    if(strchr(string, '.')) { /* we have a facility specified */
        new_global_options.facility=-1;
        string=strtok(arg_copy, "."); /* break it up */

        for(fl=facilities; fl->name; ++fl) {
            if(!strcasecmp(fl->name, string)) {
                new_global_options.facility=fl->value;
                break;
            }
        }
        if(new_global_options.facility==-1)
            return 1; /* FAILED */
        string=strtok(NULL, ".");    /* set to the remainder */
    }
#endif /* USE_WIN32, __vms */

    /* time to check the syslog level */
    if(string && strlen(string)==1 && *string>='0' && *string<='7') {
        new_global_options.debug_level=*string-'0';
        return 0; /* OK */
    }
    new_global_options.debug_level=8;    /* illegal level */
    for(fl=levels; fl->name; ++fl) {
        if(!strcasecmp(fl->name, string)) {
            new_global_options.debug_level=fl->value;
            break;
        }
    }
    if(new_global_options.debug_level==8)
        return 1; /* FAILED */
    return 0; /* OK */
}

/**************************************** SSL options */

static int parse_ssl_option(char *arg) {
    struct {
        char *name;
        long value;
    } ssl_opts[] = {
        {"MICROSOFT_SESS_ID_BUG", SSL_OP_MICROSOFT_SESS_ID_BUG},
        {"NETSCAPE_CHALLENGE_BUG", SSL_OP_NETSCAPE_CHALLENGE_BUG},
#ifdef SSL_OP_LEGACY_SERVER_CONNECT
        {"LEGACY_SERVER_CONNECT", SSL_OP_LEGACY_SERVER_CONNECT},
#endif
        {"NETSCAPE_REUSE_CIPHER_CHANGE_BUG",
            SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG},
        {"SSLREF2_REUSE_CERT_TYPE_BUG", SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG},
        {"MICROSOFT_BIG_SSLV3_BUFFER", SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER},
        {"MSIE_SSLV2_RSA_PADDING", SSL_OP_MSIE_SSLV2_RSA_PADDING},
        {"SSLEAY_080_CLIENT_DH_BUG", SSL_OP_SSLEAY_080_CLIENT_DH_BUG},
        {"TLS_D5_BUG", SSL_OP_TLS_D5_BUG},
        {"TLS_BLOCK_PADDING_BUG", SSL_OP_TLS_BLOCK_PADDING_BUG},
#ifdef SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS
        {"DONT_INSERT_EMPTY_FRAGMENTS", SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS},
#endif
        {"ALL", SSL_OP_ALL},
#ifdef SSL_OP_NO_QUERY_MTU
        {"NO_QUERY_MTU", SSL_OP_NO_QUERY_MTU},
#endif
#ifdef SSL_OP_COOKIE_EXCHANGE
        {"COOKIE_EXCHANGE", SSL_OP_COOKIE_EXCHANGE},
#endif
#ifdef SSL_OP_NO_TICKET
        {"NO_TICKET", SSL_OP_NO_TICKET},
#endif
#ifdef SSL_OP_CISCO_ANYCONNECT
        {"CISCO_ANYCONNECT", SSL_OP_CISCO_ANYCONNECT},
#endif
#ifdef SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION
        {"NO_SESSION_RESUMPTION_ON_RENEGOTIATION",
            SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION},
#endif
#ifdef SSL_OP_NO_COMPRESSION
        {"NO_COMPRESSION", SSL_OP_NO_COMPRESSION},
#endif
#ifdef SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION
        {"ALLOW_UNSAFE_LEGACY_RENEGOTIATION",
            SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION},
#endif
#ifdef SSL_OP_SINGLE_ECDH_USE
        {"SINGLE_ECDH_USE", SSL_OP_SINGLE_ECDH_USE},
#endif
        {"SINGLE_DH_USE", SSL_OP_SINGLE_DH_USE},
        {"EPHEMERAL_RSA", SSL_OP_EPHEMERAL_RSA},
#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
        {"CIPHER_SERVER_PREFERENCE", SSL_OP_CIPHER_SERVER_PREFERENCE},
#endif
        {"TLS_ROLLBACK_BUG", SSL_OP_TLS_ROLLBACK_BUG},
        {"NO_SSLv2", SSL_OP_NO_SSLv2},
        {"NO_SSLv3", SSL_OP_NO_SSLv3},
        {"NO_TLSv1", SSL_OP_NO_TLSv1},
#ifdef SSL_OP_NO_TLSv1_2
        {"NO_TLSv1.2", SSL_OP_NO_TLSv1_2},
#endif
        {"PKCS1_CHECK_1", SSL_OP_PKCS1_CHECK_1},
        {"PKCS1_CHECK_2", SSL_OP_PKCS1_CHECK_2},
        {"NETSCAPE_CA_DN_BUG", SSL_OP_NETSCAPE_CA_DN_BUG},
        {"NETSCAPE_DEMO_CIPHER_CHANGE_BUG",
            SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG},
#ifdef SSL_OP_CRYPTOPRO_TLSEXT_BUG
        {"CRYPTOPRO_TLSEXT_BUG", SSL_OP_CRYPTOPRO_TLSEXT_BUG},
#endif
        {NULL, 0}
    }, *option;

    for(option=ssl_opts; option->name; ++option)
        if(!strcasecmp(option->name, arg))
            return option->value;
    return 0; /* FAILED */
}

/**************************************** socket options */

static int on=1;
#define DEF_ON ((void *)&on)

SOCK_OPT sock_opts[] = {
    {"SO_DEBUG",        SOL_SOCKET,  SO_DEBUG,        TYPE_FLAG,    {NULL, NULL, NULL}},
    {"SO_DONTROUTE",    SOL_SOCKET,  SO_DONTROUTE,    TYPE_FLAG,    {NULL, NULL, NULL}},
    {"SO_KEEPALIVE",    SOL_SOCKET,  SO_KEEPALIVE,    TYPE_FLAG,    {NULL, NULL, NULL}},
    {"SO_LINGER",       SOL_SOCKET,  SO_LINGER,       TYPE_LINGER,  {NULL, NULL, NULL}},
    {"SO_OOBINLINE",    SOL_SOCKET,  SO_OOBINLINE,    TYPE_FLAG,    {NULL, NULL, NULL}},
    {"SO_RCVBUF",       SOL_SOCKET,  SO_RCVBUF,       TYPE_INT,     {NULL, NULL, NULL}},
    {"SO_SNDBUF",       SOL_SOCKET,  SO_SNDBUF,       TYPE_INT,     {NULL, NULL, NULL}},
#ifdef SO_RCVLOWAT
    {"SO_RCVLOWAT",     SOL_SOCKET,  SO_RCVLOWAT,     TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef SO_SNDLOWAT
    {"SO_SNDLOWAT",     SOL_SOCKET,  SO_SNDLOWAT,     TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef SO_RCVTIMEO
    {"SO_RCVTIMEO",     SOL_SOCKET,  SO_RCVTIMEO,     TYPE_TIMEVAL, {NULL, NULL, NULL}},
#endif
#ifdef SO_SNDTIMEO
    {"SO_SNDTIMEO",     SOL_SOCKET,  SO_SNDTIMEO,     TYPE_TIMEVAL, {NULL, NULL, NULL}},
#endif
    {"SO_REUSEADDR",    SOL_SOCKET,  SO_REUSEADDR,    TYPE_FLAG,    {DEF_ON, NULL, NULL}},
#ifdef SO_BINDTODEVICE
    {"SO_BINDTODEVICE", SOL_SOCKET,  SO_BINDTODEVICE, TYPE_STRING,  {NULL, NULL, NULL}},
#endif
#ifdef TCP_KEEPCNT
    {"TCP_KEEPCNT",     SOL_TCP,     TCP_KEEPCNT,     TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef TCP_KEEPIDLE
    {"TCP_KEEPIDLE",    SOL_TCP,     TCP_KEEPIDLE,    TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef TCP_KEEPINTVL
    {"TCP_KEEPINTVL",   SOL_TCP,     TCP_KEEPINTVL,   TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef IP_TOS
    {"IP_TOS",          IPPROTO_IP,  IP_TOS,          TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef IP_TTL
    {"IP_TTL",          IPPROTO_IP,  IP_TTL,          TYPE_INT,     {NULL, NULL, NULL}},
#endif
#ifdef IP_MAXSEG
    {"TCP_MAXSEG",      IPPROTO_TCP, TCP_MAXSEG,      TYPE_INT,     {NULL, NULL, NULL}},
#endif
    {"TCP_NODELAY",     IPPROTO_TCP, TCP_NODELAY,     TYPE_FLAG,    {NULL, DEF_ON, DEF_ON}},
    {NULL,              0,           0,               TYPE_NONE,    {NULL, NULL, NULL}}
};

static int print_socket_options(void) {
    int fd;
    socklen_t optlen;
    SOCK_OPT *ptr;
    OPT_UNION val;
    char *ta, *tl, *tr, *td;

    fd=socket(AF_INET, SOCK_STREAM, 0);

    s_log(LOG_NOTICE, " ");
    s_log(LOG_NOTICE, "Socket option defaults:");
    s_log(LOG_NOTICE,
        "    Option Name     |  Accept  |   Local  |  Remote  |OS default");
    s_log(LOG_NOTICE,
        "    ----------------+----------+----------+----------+----------");
    for(ptr=sock_opts; ptr->opt_str; ++ptr) {
        /* get OS default value */
        optlen=sizeof val;
        if(getsockopt(fd, ptr->opt_level,
                ptr->opt_name, (void *)&val, &optlen)) {
            if(get_last_socket_error()!=S_ENOPROTOOPT) {
                s_log(LOG_ERR, "Failed to get %s OS default", ptr->opt_str);
                sockerror("getsockopt");
                return 1; /* FAILED */
            }
            td=str_dup("write-only");
        } else
            td=print_option(ptr->opt_type, &val);
        /* get stunnel default values */
        ta=print_option(ptr->opt_type, ptr->opt_val[0]);
        tl=print_option(ptr->opt_type, ptr->opt_val[1]);
        tr=print_option(ptr->opt_type, ptr->opt_val[2]);
        /* print collected data and fee the memory */
        s_log(LOG_NOTICE, "    %-16s|%10s|%10s|%10s|%10s",
            ptr->opt_str, ta, tl, tr, td);
        str_free(ta); str_free(tl); str_free(tr); str_free(td);
    }
    return 0; /* OK */
}

static char *print_option(int type, OPT_UNION *val) {
    if(!val)
        return str_dup("    --    ");
    switch(type) {
    case TYPE_FLAG:
        return str_printf("%s", val->i_val ? "yes" : "no");
    case TYPE_INT:
        return str_printf("%d", val->i_val);
    case TYPE_LINGER:
        return str_printf("%d:%d",
            val->linger_val.l_onoff, val->linger_val.l_linger);
    case TYPE_TIMEVAL:
        return str_printf("%d:%d",
            (int)val->timeval_val.tv_sec, (int)val->timeval_val.tv_usec);
    case TYPE_STRING:
        return str_printf("%s", val->c_val);
    }
    return str_dup("  Ooops?  "); /* internal error? */
}

static int parse_socket_option(char *arg) {
    int socket_type; /* 0-accept, 1-local, 2-remote */
    char *opt_val_str, *opt_val2_str, *tmpstr;
    SOCK_OPT *ptr;

    if(arg[1]!=':')
        return 1; /* FAILED */
    switch(arg[0]) {
    case 'a':
        socket_type=0; break;
    case 'l':
        socket_type=1; break;
    case 'r':
        socket_type=2; break;
    default:
        return 1; /* FAILED */
    }
    arg+=2;
    opt_val_str=strchr(arg, '=');
    if(!opt_val_str) /* no '='? */
        return 1; /* FAILED */
    *opt_val_str++='\0';
    ptr=sock_opts;
    for(;;) {
        if(!ptr->opt_str)
            return 1; /* FAILED */
        if(!strcmp(arg, ptr->opt_str))
            break; /* option name found */
        ++ptr;
    }
    ptr->opt_val[socket_type]=str_alloc(sizeof(OPT_UNION));
    switch(ptr->opt_type) {
    case TYPE_FLAG:
        if(!strcasecmp(opt_val_str, "yes") || !strcmp(opt_val_str, "1")) {
            ptr->opt_val[socket_type]->i_val=1;
            return 0; /* OK */
        }
        if(!strcasecmp(opt_val_str, "no") || !strcmp(opt_val_str, "0")) {
            ptr->opt_val[socket_type]->i_val=0;
            return 0; /* OK */
        }
        return 1; /* FAILED */
    case TYPE_INT:
        ptr->opt_val[socket_type]->i_val=strtol(opt_val_str, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return 1; /* FAILED */
        return 0; /* OK */
    case TYPE_LINGER:
        opt_val2_str=strchr(opt_val_str, ':');
        if(opt_val2_str) {
            *opt_val2_str++='\0';
            ptr->opt_val[socket_type]->linger_val.l_linger=
                (u_short)strtol(opt_val2_str, &tmpstr, 10);
            if(tmpstr==arg || *tmpstr) /* not a number */
                return 1; /* FAILED */
        } else {
            ptr->opt_val[socket_type]->linger_val.l_linger=0;
        }
        ptr->opt_val[socket_type]->linger_val.l_onoff=
            (u_short)strtol(opt_val_str, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return 1; /* FAILED */
        return 0; /* OK */
    case TYPE_TIMEVAL:
        opt_val2_str=strchr(opt_val_str, ':');
        if(opt_val2_str) {
            *opt_val2_str++='\0';
            ptr->opt_val[socket_type]->timeval_val.tv_usec=strtol(opt_val2_str, &tmpstr, 10);
            if(tmpstr==arg || *tmpstr) /* not a number */
                return 1; /* FAILED */
        } else {
            ptr->opt_val[socket_type]->timeval_val.tv_usec=0;
        }
        ptr->opt_val[socket_type]->timeval_val.tv_sec=strtol(opt_val_str, &tmpstr, 10);
        if(tmpstr==arg || *tmpstr) /* not a number */
            return 1; /* FAILED */
        return 0; /* OK */
    case TYPE_STRING:
        if(strlen(opt_val_str)+1>sizeof(OPT_UNION))
            return 1; /* FAILED */
        strcpy(ptr->opt_val[socket_type]->c_val, opt_val_str);
        return 0; /* OK */
    default:
        ; /* ANSI C compiler needs it */
    }
    return 1; /* FAILED */
}

/**************************************** OCSP */

#ifdef HAVE_OSSL_OCSP_H

static char *parse_ocsp_url(SERVICE_OPTIONS *section, char *arg) {
    char *host, *port, *path;
    int ssl;

    if(!OCSP_parse_url(arg, &host, &port, &path, &ssl))
        return "Failed to parse OCSP URL";
    if(ssl)
        return "SSL not supported for OCSP"
            " - additional stunnel service needs to be defined";
    if(!hostport2addr(&section->ocsp_addr, host, port))
        return "Failed to resolve OCSP server address";
    section->ocsp_path=str_dup(path);
    if(host)
        OPENSSL_free(host);
    if(port)
        OPENSSL_free(port);
    if(path)
        OPENSSL_free(path);
    return NULL; /* OK! */
}

static unsigned long parse_ocsp_flag(char *arg) {
    struct {
        char *name;
        unsigned long value;
    } ocsp_opts[] = {
        {"NOCERTS", OCSP_NOCERTS},
        {"NOINTERN", OCSP_NOINTERN},
        {"NOSIGS", OCSP_NOSIGS},
        {"NOCHAIN", OCSP_NOCHAIN},
        {"NOVERIFY", OCSP_NOVERIFY},
        {"NOEXPLICIT", OCSP_NOEXPLICIT},
        {"NOCASIGN", OCSP_NOCASIGN},
        {"NODELEGATED", OCSP_NODELEGATED},
        {"NOCHECKS", OCSP_NOCHECKS},
        {"TRUSTOTHER", OCSP_TRUSTOTHER},
        {"RESPID_KEY", OCSP_RESPID_KEY},
        {"NOTIME", OCSP_NOTIME},
        {NULL, 0}
    }, *option;

    for(option=ocsp_opts; option->name; ++option)
        if(!strcasecmp(option->name, arg))
            return option->value;
    return 0; /* FAILED */
}

#endif /* HAVE_OSSL_OCSP_H */

/**************************************** engine */

#ifdef HAVE_OSSL_ENGINE_H

#define MAX_ENGINES 256
static ENGINE *engines[MAX_ENGINES]; /* table of engines */
static int current_engine=0;
static int engine_initialized;

static char *open_engine(const char *name) {
    s_log(LOG_DEBUG, "Enabling support for engine '%s'", name);
    if(!strcasecmp(name, "auto")) {
        ENGINE_register_all_complete();
        s_log(LOG_DEBUG, "Auto engine support enabled");
        return NULL; /* OK */
    }

    close_engine(); /* close the previous one (if specified) */
    engines[current_engine]=ENGINE_by_id(name);
    engine_initialized=0;
    if(!engines[current_engine]) {
        sslerror("ENGINE_by_id");
        return "Failed to open the engine";
    }
    return NULL; /* OK */
}

static char *ctrl_engine(const char *cmd, const char *arg) {
    if(!strcasecmp(cmd, "INIT")) { /* special control command */
        return init_engine();
    }
    if(arg)
        s_log(LOG_DEBUG, "Executing engine control command %s:%s", cmd, arg);
    else
        s_log(LOG_DEBUG, "Executing engine control command %s", cmd);
    if(!ENGINE_ctrl_cmd_string(engines[current_engine], cmd, arg, 0)) {
        sslerror("ENGINE_ctrl_cmd_string");
        return "Failed to execute the engine control command";
    }
    return NULL; /* OK */
}

static char *init_engine(void) {
    if(engine_initialized)
        return NULL; /* OK */
    engine_initialized=1;
    s_log(LOG_DEBUG, "Initializing engine %d", current_engine+1);
    if(!ENGINE_init(engines[current_engine])) {
        if(ERR_peek_last_error()) /* really an error */
            sslerror("ENGINE_init");
        else
            s_log(LOG_ERR, "Engine %d not initialized", current_engine+1);
        return "Engine initialization failed";
    }
    if(!ENGINE_set_default(engines[current_engine], ENGINE_METHOD_ALL)) {
        sslerror("ENGINE_set_default");
        return "Selecting default engine failed";
    }
    s_log(LOG_DEBUG, "Engine %d initialized", current_engine+1);
    return NULL; /* OK */
}

static void close_engine(void) {
    if(!engines[current_engine])
        return; /* no engine was opened -> nothing to do */
    init_engine();
    ++current_engine;
#if 0
    ENGINE_finish(e);
    ENGINE_free(e);
    e=NULL;
    s_log(LOG_DEBUG, "Engine closed");
#endif
}

static ENGINE *get_engine(int i) {
    if(i<1 || i>current_engine)
        return NULL;
    return engines[i-1];
}

#endif /* HAVE_OSSL_ENGINE_H */

/**************************************** fatal error */

static void print_syntax(void) {
    s_log(LOG_NOTICE, " ");
    s_log(LOG_NOTICE, "Syntax:");
    s_log(LOG_NOTICE, "stunnel "
#ifdef USE_WIN32
#ifndef _WIN32_WCE
        "[ [-install | -uninstall] "
#endif
        "[-quiet] "
#endif
        "[<filename>] ] "
#ifndef USE_WIN32
        "-fd <n> "
#endif
        "| -help | -version | -sockets");
    s_log(LOG_NOTICE, "    <filename>  - use specified config file");
#ifdef USE_WIN32
#ifndef _WIN32_WCE
    s_log(LOG_NOTICE, "    -install    - install NT service");
    s_log(LOG_NOTICE, "    -uninstall  - uninstall NT service");
#endif
    s_log(LOG_NOTICE, "    -quiet      - don't display a message box on success");
#else
    s_log(LOG_NOTICE, "    -fd <n>     - read the config file from a file descriptor");
#endif
    s_log(LOG_NOTICE, "    -help       - get config file help");
    s_log(LOG_NOTICE, "    -version    - display version and defaults");
    s_log(LOG_NOTICE, "    -sockets    - display default socket options");
}

/**************************************** various supporting functions */

static void config_error(int num, const char *line, const char *str) {
    s_log(LOG_ERR, "Line %d: \"%s\": %s", num, line, str);
}

static void section_error(const char *name, const char *str) {
    s_log(LOG_ERR, "Section %s: %s", name, str);
}

#ifndef USE_WIN32

static char **argalloc(char *str) { /* allocate 'exec' argumets */
    int max_arg, i;
    char *ptr, **retval;

    max_arg=strlen(str)/2+1;
    ptr=str_dup(str);
    retval=str_alloc((max_arg+1)*sizeof(char *));
    i=0;
    while(*ptr && i<max_arg) {
        retval[i++]=ptr;
        while(*ptr && !isspace((unsigned char)*ptr))
            ++ptr;
        while(*ptr && isspace((unsigned char)*ptr))
            *ptr++='\0';
    }
    retval[i]=NULL; /* to show that it's null-terminated */
    return retval;
}
#endif

/* end of options.c */

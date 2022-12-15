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

/**************************************** prototypes */

/* SNI */
#ifndef OPENSSL_NO_TLSEXT
static int servername_cb(SSL *, int *, void *);
#endif

/* DH/ECDH initialization */
#ifndef OPENSSL_NO_DH
static int init_dh(SERVICE_OPTIONS *);
static DH *read_dh(char *);
static DH *get_dh2048(void);
#endif /* OPENSSL_NO_DH */
#ifndef OPENSSL_NO_ECDH
static int init_ecdh(SERVICE_OPTIONS *);
#endif /* USE_ECDH */

/* loading certificate */
static int load_certificate(SERVICE_OPTIONS *);
#if defined(USE_WIN32) || OPENSSL_VERSION_NUMBER>=0x0090700fL
#ifndef _SC_BUILD_
static int password_cb(char *, int, int, void *);
#else
#define TR064_PEM_PASSPHRASE "/tmp/tr64_server_password"
static int password_cb(char *buf, int num, int verify);
static char *get_pem_passphase(char *file);
#endif
#endif

/* session cache callbacks */
static int sess_new_cb(SSL *, SSL_SESSION *);
static SSL_SESSION *sess_get_cb(SSL *, unsigned char *, int, int *);
static void sess_remove_cb(SSL_CTX *, SSL_SESSION *);
static void cache_transfer(SSL_CTX *, const unsigned int, const unsigned,
    const unsigned char *, const unsigned int,
    const unsigned char *, const unsigned int,
    unsigned char **, unsigned int *);

/* info callbacks */
static void info_callback(
#if OPENSSL_VERSION_NUMBER>=0x0090700fL
    const
#endif
    SSL *, int, int);

static void sslerror_queue(void);
static void sslerror_log(unsigned long, char *);

/**************************************** initialize section->ctx */

int context_init(SERVICE_OPTIONS *section) { /* init SSL context */
    /* create SSL context */
    if(section->option.client)
        section->ctx=SSL_CTX_new(section->client_method);
    else /* server mode */
        section->ctx=SSL_CTX_new(section->server_method);
    if(!section->ctx) {
        sslerror("SSL_CTX_new");
        return 1; /* FAILED */
    }
    SSL_CTX_set_ex_data(section->ctx, opt_index, section); /* for callbacks */

    /* initialize certificate verification */
    if(load_certificate(section))
        return 1; /* FAILED */
    if(verify_init(section))
        return 1; /* FAILED */

    /* initialize DH/ECDH server mode */
    if(!section->option.client) {
#ifndef OPENSSL_NO_TLSEXT
        SSL_CTX_set_tlsext_servername_arg(section->ctx, section);
        SSL_CTX_set_tlsext_servername_callback(section->ctx, servername_cb);
#endif /* OPENSSL_NO_TLSEXT */
#ifndef OPENSSL_NO_DH
        init_dh(section); /* ignore the result (errors are not critical) */
#endif /* OPENSSL_NO_DH */
#ifndef OPENSSL_NO_ECDH
        init_ecdh(section); /* ignore the result (errors are not critical) */
#endif /* OPENSSL_NO_ECDH */
    }

    /* setup session cache */
    if(!section->option.client) {
        unsigned int servname_len=strlen(section->servname);
        if(servname_len>SSL_MAX_SSL_SESSION_ID_LENGTH)
            servname_len=SSL_MAX_SSL_SESSION_ID_LENGTH;
        if(!SSL_CTX_set_session_id_context(section->ctx,
                (unsigned char *)section->servname, servname_len)) {
            sslerror("SSL_CTX_set_session_id_context");
            return 1; /* FAILED */
        }
    }
    SSL_CTX_set_session_cache_mode(section->ctx, SSL_SESS_CACHE_BOTH);
    SSL_CTX_set_timeout(section->ctx, section->session_timeout);
    if(section->option.sessiond) {
        SSL_CTX_sess_set_new_cb(section->ctx, sess_new_cb);
        SSL_CTX_sess_set_get_cb(section->ctx, sess_get_cb);
        SSL_CTX_sess_set_remove_cb(section->ctx, sess_remove_cb);
    }

    /* set info callback */
    if(global_options.debug_level==LOG_DEBUG) /* performance optimization */
        SSL_CTX_set_info_callback(section->ctx, info_callback);

    /* ciphers, options, mode */
    if(section->cipher_list)
        if(!SSL_CTX_set_cipher_list(section->ctx, section->cipher_list)) {
            sslerror("SSL_CTX_set_cipher_list");
            return 1; /* FAILED */
        }
    s_log(LOG_DEBUG, "SSL options set: 0x%08lX",
        SSL_CTX_set_options(section->ctx, section->ssl_options));
#ifdef SSL_MODE_RELEASE_BUFFERS
    SSL_CTX_set_mode(section->ctx,
        SSL_MODE_ENABLE_PARTIAL_WRITE |
        SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER |
        SSL_MODE_RELEASE_BUFFERS);
#else
    SSL_CTX_set_mode(section->ctx,
        SSL_MODE_ENABLE_PARTIAL_WRITE |
        SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
#endif
    return 0; /* OK */
}

/**************************************** SNI callback */

#ifndef OPENSSL_NO_TLSEXT

static int servername_cb(SSL *ssl, int *ad, void *arg) {
    SERVICE_OPTIONS *section=(SERVICE_OPTIONS *)arg;
    const char *servername=SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
    SERVERNAME_LIST *list;
    CLI *c;
#ifdef USE_LIBWRAP
    char *accepted_address;
#endif /* USE_LIBWRAP */

    /* leave the alert type at SSL_AD_UNRECOGNIZED_NAME */
    (void)ad; /* skip warning about unused parameter */
    if(!section->servername_list_head) /* no virtual services defined */
        return SSL_TLSEXT_ERR_OK;
    if(!servername) /* no SNI extension received from the client */
        return SSL_TLSEXT_ERR_NOACK;

    for(list=section->servername_list_head; list; list=list->next)
        if(!strcasecmp(servername, list->servername)) {
            c=SSL_get_ex_data(ssl, cli_index);
            c->opt=list->opt;
            SSL_set_SSL_CTX(ssl, c->opt->ctx);
            SSL_set_verify(ssl, SSL_CTX_get_verify_mode(c->opt->ctx),
                SSL_CTX_get_verify_callback(c->opt->ctx));
            s_log(LOG_NOTICE, "SNI: switched to section %s",
                c->opt->servname);
#ifdef USE_LIBWRAP
            accepted_address=s_ntop(&c->peer_addr, c->peer_addr_len);
            libwrap_auth(c, accepted_address); /* retry on a service switch */
            str_free(accepted_address);
#endif /* USE_LIBWRAP */
            return SSL_TLSEXT_ERR_OK;
        }
    s_log(LOG_ERR, "SNI: no service defined for server %s", servername);
    return SSL_TLSEXT_ERR_ALERT_FATAL;
}
/* TLSEXT callback return codes:
 *  - SSL_TLSEXT_ERR_OK
 *  - SSL_TLSEXT_ERR_ALERT_WARNING
 *  - SSL_TLSEXT_ERR_ALERT_FATAL
 *  - SSL_TLSEXT_ERR_NOACK */

#endif /* OPENSSL_NO_TLSEXT */

/**************************************** DH initialization */

#ifndef OPENSSL_NO_DH

static int init_dh(SERVICE_OPTIONS *section) {
    DH *dh;

    dh=read_dh(section->cert);
    if(!dh)
        dh=get_dh2048();
    if(!dh) {
        s_log(LOG_NOTICE, "DH initialization failed");
        return 1; /* FAILED */
    }
    SSL_CTX_set_tmp_dh(section->ctx, dh);
    s_log(LOG_DEBUG, "DH initialized with %d-bit key", 8*DH_size(dh));
    DH_free(dh);
    return 0; /* OK */
}

static DH *read_dh(char *cert) {
    DH *dh;
    BIO *bio;

    if(!cert) {
        s_log(LOG_DEBUG, "No certificate available to load DH parameters");
        return NULL; /* FAILED */
    }

    bio=BIO_new_file(cert, "r");
    if(!bio) {
        sslerror("BIO_new_file");
        return NULL; /* FAILED */
    }
    dh=PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if(!dh) {
        while(ERR_get_error())
            ; /* OpenSSL error queue cleanup */
        s_log(LOG_DEBUG, "Could not load DH parameters from %s", cert);
        return NULL; /* FAILED */
    }
    s_log(LOG_DEBUG, "Using DH parameters from %s", cert);
    return dh;
}

static DH *get_dh2048() {
    static unsigned char dh2048_p[]={ /* OpenSSL DH parameters */
        0xED,0x92,0x89,0x35,0x82,0x45,0x55,0xCB,0x3B,0xFB,0xA2,0x76,
        0x5A,0x69,0x04,0x61,0xBF,0x21,0xF3,0xAB,0x53,0xD2,0xCD,0x21,
        0xDA,0xFF,0x78,0x19,0x11,0x52,0xF1,0x0E,0xC1,0xE2,0x55,0xBD,
        0x68,0x6F,0x68,0x00,0x53,0xB9,0x22,0x6A,0x2F,0xE4,0x9A,0x34,
        0x1F,0x65,0xCC,0x59,0x32,0x8A,0xBD,0xB1,0xDB,0x49,0xED,0xDF,
        0xA7,0x12,0x66,0xC3,0xFD,0x21,0x04,0x70,0x18,0xF0,0x7F,0xD6,
        0xF7,0x58,0x51,0x19,0x72,0x82,0x7B,0x22,0xA9,0x34,0x18,0x1D,
        0x2F,0xCB,0x21,0xCF,0x6D,0x92,0xAE,0x43,0xB6,0xA8,0x29,0xC7,
        0x27,0xA3,0xCB,0x00,0xC5,0xF2,0xE5,0xFB,0x0A,0xA4,0x59,0x85,
        0xA2,0xBD,0xAD,0x45,0xF0,0xB3,0xAD,0xF9,0xE0,0x81,0x35,0xEE,
        0xD9,0x83,0xB3,0xCC,0xAE,0xEA,0xEB,0x66,0xE6,0xA9,0x57,0x66,
        0xB9,0xF1,0x28,0xA5,0x3F,0x22,0x80,0xD7,0x0B,0xA6,0xF6,0x71,
        0x93,0x9B,0x81,0x0E,0xF8,0x5A,0x90,0xE6,0xCC,0xCA,0x6F,0x66,
        0x5F,0x7A,0xC0,0x10,0x1A,0x1E,0xF0,0xFC,0x2D,0xB6,0x08,0x0C,
        0x62,0x28,0xB0,0xEC,0xDB,0x89,0x28,0xEE,0x0C,0xA8,0x3D,0x65,
        0x94,0x69,0x16,0x69,0x53,0x3C,0x53,0x60,0x13,0xB0,0x2B,0xA7,
        0xD4,0x82,0x87,0xAD,0x1C,0x72,0x9E,0x41,0x35,0xFC,0xC2,0x7C,
        0xE9,0x51,0xDE,0x61,0x85,0xFC,0x19,0x9B,0x76,0x60,0x0F,0x33,
        0xF8,0x6B,0xB3,0xCA,0x52,0x0E,0x29,0xC3,0x07,0xE8,0x90,0x16,
        0xCC,0xCC,0x00,0x19,0xB6,0xAD,0xC3,0xA4,0x30,0x8B,0x33,0xA1,
        0xAF,0xD8,0x8C,0x8D,0x9D,0x01,0xDB,0xA4,0xC4,0xDD,0x7F,0x0B,
        0xBD,0x6F,0x38,0xC3,};
    static unsigned char dh2048_g[]={0x02,};
    DH *dh;

    dh=DH_new();
    if(!dh)
        return NULL;
    dh->p=BN_bin2bn(dh2048_p, sizeof dh2048_p, NULL);
    dh->g=BN_bin2bn(dh2048_g, sizeof dh2048_g, NULL);
    if(!dh->p || !dh->g) {
        DH_free(dh);
        return NULL;
    }
    s_log(LOG_DEBUG, "Using hardcoded DH parameters");
    return dh;
}

#endif /* OPENSSL_NO_DH */

/**************************************** ECDH initialization */

#ifndef OPENSSL_NO_ECDH
static int init_ecdh(SERVICE_OPTIONS *section) {
    EC_KEY *ecdh;

    ecdh=EC_KEY_new_by_curve_name(section->curve);
    if(!ecdh) {
        s_log(LOG_ERR, "Unable to create curve %s",
            OBJ_nid2ln(section->curve));
        return 1; /* FAILED */
    }
    SSL_CTX_set_tmp_ecdh(section->ctx, ecdh);
    EC_KEY_free(ecdh);
    s_log(LOG_DEBUG, "ECDH initialized with curve %s",
        OBJ_nid2ln(section->curve));
    return 0; /* OK */
}
#endif /* OPENSSL_NO_ECDH */

/**************************************** loading certificate */

static int cache_initialized=0;

static int load_certificate(SERVICE_OPTIONS *section) {
    int i, reason;
    UI_DATA ui_data;
#ifdef HAVE_OSSL_ENGINE_H
    EVP_PKEY *pkey;
    UI_METHOD *ui_method;
#endif
    struct stat st; /* buffer for stat */

    /* check if certificate exists */
    if(!section->key) /* key file not specified */
        section->key=section->cert;
#ifdef HAVE_OSSL_ENGINE_H
    if(!section->engine)
#endif
    if(section->key) {
        if(stat(section->key, &st)) {
            ioerror(section->key);
            return 1; /* FAILED */
        }
#if !defined(USE_WIN32) && !defined(USE_OS2)
        if(st.st_mode & 7)
            s_log(LOG_WARNING, "Insecure file permissions on %s",
                section->key);
#endif /* defined USE_WIN32 */
    }

    if(!section->cert) /* no certificate specified */
        return 0; /* OK */

    ui_data.section=section; /* setup current section for callbacks */

    s_log(LOG_DEBUG, "Certificate: %s", section->cert);
    if(!SSL_CTX_use_certificate_chain_file(section->ctx, section->cert)) {
        s_log(LOG_ERR, "Error reading certificate file: %s", section->cert);
        sslerror("SSL_CTX_use_certificate_chain_file");
        return 1; /* FAILED */
    }
    s_log(LOG_DEBUG, "Certificate loaded");

    s_log(LOG_DEBUG, "Key file: %s", section->key);
#if defined(USE_WIN32) || OPENSSL_VERSION_NUMBER>=0x0090700fL
    SSL_CTX_set_default_passwd_cb(section->ctx, password_cb);
#endif
#ifdef HAVE_OSSL_ENGINE_H
#ifdef USE_WIN32
    ui_method=UI_create_method("stunnel WIN32 UI");
    UI_method_set_reader(ui_method, pin_cb);
#else /* USE_WIN32 */
    ui_method=UI_OpenSSL();
#endif /* USE_WIN32 */
    if(section->engine)
        for(i=1; i<=3; i++) {
            pkey=ENGINE_load_private_key(section->engine, section->key,
                ui_method, &ui_data);
            if(!pkey) {
                reason=ERR_GET_REASON(ERR_peek_error());
                if(i<=2 && (reason==7 || reason==160)) { /* wrong PIN */
                    sslerror_queue(); /* dump the error queue */
                    s_log(LOG_ERR, "Wrong PIN: retrying");
                    continue;
                }
                sslerror("ENGINE_load_private_key");
                return 1; /* FAILED */
            }
            if(SSL_CTX_use_PrivateKey(section->ctx, pkey))
                break; /* success */
            sslerror("SSL_CTX_use_PrivateKey");
            return 1; /* FAILED */
        }
    else
#endif /* HAVE_OSSL_ENGINE_H */
        for(i=0; i<=3; i++) {
            if(!i && !cache_initialized)
                continue; /* there is no cached value */
#ifndef _SC_BUILD_
            SSL_CTX_set_default_passwd_cb_userdata(section->ctx,
                i ? &ui_data : NULL); /* try the cached password first */
#else
            SSL_CTX_set_default_passwd_cb_userdata(section->ctx, get_pem_passphase(TR064_PEM_PASSPHRASE));
#endif
            if(SSL_CTX_use_PrivateKey_file(section->ctx, section->key,
                    SSL_FILETYPE_PEM))
                break;
            reason=ERR_GET_REASON(ERR_peek_error());
            if(i<=2 && reason==EVP_R_BAD_DECRYPT) {
                sslerror_queue(); /* dump the error queue */
                s_log(LOG_ERR, "Wrong pass phrase: retrying");
                continue;
            }
            sslerror("SSL_CTX_use_PrivateKey_file");
            return 1; /* FAILED */
        }
    if(!SSL_CTX_check_private_key(section->ctx)) {
        sslerror("Private key does not match the certificate");
        return 1; /* FAILED */
    }
    s_log(LOG_DEBUG, "Private key loaded");
    return 0; /* OK */
}

#if defined(USE_WIN32) || OPENSSL_VERSION_NUMBER>=0x0090700fL
#ifndef _SC_BUILD_
static int password_cb(char *buf, int size, int rwflag, void *userdata) {
    static char cache[PEM_BUFSIZE];
    int len;

    if(size>PEM_BUFSIZE)
        size=PEM_BUFSIZE;

    if(userdata) { /* prompt the user */
#ifdef USE_WIN32
        len=passwd_cb(buf, size, rwflag, userdata);
#else
        /* PEM_def_callback is defined in OpenSSL 0.9.7 and later */
        len=PEM_def_callback(buf, size, rwflag, NULL);
#endif
        memcpy(cache, buf, size); /* save in cache */
        cache_initialized=1;
    } else { /* try the cached value */
        strncpy(buf, cache, size);
        buf[size-1]='\0';
        len=strlen(buf);
    }
    return len;
}
#else
static char *get_pem_passphase(char *file)
{
    FILE *fp=NULL;
    static char buf[256];
    
    fp=fopen(file, "r");
    if(fp==NULL)
        return NULL;
    
    fgets(buf,256,fp);
    fclose(fp);

    return buf;
}

static int password_cb(char *buf, int num, int verify)
{
	static char global_passwd[64]={0};
	
	size_t len = strlen(get_pem_passphase(TR064_PEM_PASSPHRASE));
	
        if(len < sizeof(global_passwd))
		memcpy(global_passwd, get_pem_passphase(TR064_PEM_PASSPHRASE), len+1);
  if(verify)
    fprintf(stderr, "%s\n", buf);
  else {
    if(num > (int)strlen((char *)global_passwd)) {
      strcpy(buf, global_passwd);
      return (int)strlen(buf);
    }
  }
  return 0;
}
#endif
#endif

/**************************************** session cache callbacks */

#define CACHE_CMD_NEW     0x00
#define CACHE_CMD_GET     0x01
#define CACHE_CMD_REMOVE  0x02
#define CACHE_RESP_ERR    0x80
#define CACHE_RESP_OK     0x81

static int sess_new_cb(SSL *ssl, SSL_SESSION *sess) {
    unsigned char *val, *val_tmp;
    int val_len;

    val_len=i2d_SSL_SESSION(sess, NULL);
    val_tmp=val=str_alloc(val_len);
    i2d_SSL_SESSION(sess, &val_tmp);

    cache_transfer(ssl->ctx, CACHE_CMD_NEW, SSL_SESSION_get_timeout(sess),
        sess->session_id, sess->session_id_length, val, val_len, NULL, NULL);
    str_free(val);
    return 1; /* leave the session in local cache for reuse */
}

static SSL_SESSION *sess_get_cb(SSL *ssl,
        unsigned char *key, int key_len, int *do_copy) {
    unsigned char *val, *val_tmp=NULL;
    unsigned int val_len=0;
    SSL_SESSION *sess;

    *do_copy = 0; /* allow the session to be freed autmatically */
    cache_transfer(ssl->ctx, CACHE_CMD_GET, 0,
        key, key_len, NULL, 0, &val, &val_len);
    if(!val)
        return NULL;
    val_tmp=val;
    sess=d2i_SSL_SESSION(NULL,
#if OPENSSL_VERSION_NUMBER>=0x0090800fL
        (const unsigned char **)
#endif /* OpenSSL version >= 0.8.0 */
        &val_tmp, val_len);
    str_free(val);
    return sess;
}

static void sess_remove_cb(SSL_CTX *ctx, SSL_SESSION *sess) {
    cache_transfer(ctx, CACHE_CMD_REMOVE, 0,
        sess->session_id, sess->session_id_length, NULL, 0, NULL, NULL);
}

#define MAX_VAL_LEN 512
typedef struct {
    u_char version, type;
    u_short timeout;
    u_char key[SSL_MAX_SSL_SESSION_ID_LENGTH];
    u_char val[MAX_VAL_LEN];
} CACHE_PACKET;

static void cache_transfer(SSL_CTX *ctx, const unsigned int type,
        const unsigned int timeout,
        const unsigned char *key, const unsigned int key_len,
        const unsigned char *val, const unsigned int val_len,
        unsigned char **ret, unsigned int *ret_len) {
    char session_id_txt[2*SSL_MAX_SSL_SESSION_ID_LENGTH+1];
    const char hex[16]="0123456789ABCDEF";
    const char *type_description[]={"new", "get", "remove"};
    unsigned int i;
    int s, len;
    struct timeval t;
    CACHE_PACKET *packet;
    SERVICE_OPTIONS *section;

    if(ret) /* set error as the default result if required */
        *ret=NULL;

    /* log the request information */
    for(i=0; i<key_len && i<SSL_MAX_SSL_SESSION_ID_LENGTH; ++i) {
        session_id_txt[2*i]=hex[key[i]>>4];
        session_id_txt[2*i+1]=hex[key[i]&0x0f];
    }
    session_id_txt[2*i]='\0';
    s_log(LOG_INFO,
        "cache_transfer: request=%s, timeout=%u, id=%s, length=%d",
        type_description[type], timeout, session_id_txt, val_len);

    /* allocate UDP packet buffer */
    if(key_len>SSL_MAX_SSL_SESSION_ID_LENGTH) {
        s_log(LOG_ERR, "cache_transfer: session id too big (%d bytes)",
            key_len);
        return;
    }
    if(val_len>MAX_VAL_LEN) {
        s_log(LOG_ERR, "cache_transfer: encoded session too big (%d bytes)",
            key_len);
        return;
    }
    packet=str_alloc(sizeof(CACHE_PACKET));

    /* setup packet */
    packet->version=1;
    packet->type=type;
    packet->timeout=htons((u_short)(timeout<64800?timeout:64800));/* 18 hours */
    memcpy(packet->key, key, key_len);
    memcpy(packet->val, val, val_len);

    /* create the socket */
    s=s_socket(AF_INET, SOCK_DGRAM, 0, 0, "cache_transfer: socket");
    if(s<0) {
        str_free(packet);
        return;
    }

    /* retrieve pointer to the section structure of this ctx */
    section=SSL_CTX_get_ex_data(ctx, opt_index);
    if(sendto(s, (void *)packet, sizeof(CACHE_PACKET)-MAX_VAL_LEN+val_len, 0,
            &section->sessiond_addr.sa, addr_len(&section->sessiond_addr))<0) {
        sockerror("cache_transfer: sendto");
        closesocket(s);
        str_free(packet);
        return;
    }

    if(!ret || !ret_len) { /* no response is required */
        closesocket(s);
        str_free(packet);
        return;
    }

    /* set recvfrom timeout to 200ms */
    t.tv_sec=0;
    t.tv_usec=200;
    if(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (void *)&t, sizeof t)<0) {
        sockerror("cache_transfer: setsockopt SO_RCVTIMEO");
        closesocket(s);
        str_free(packet);
        return;
    }

    /* retrieve response */
    len=recv(s, (void *)packet, sizeof(CACHE_PACKET), 0);
    closesocket(s);
    if(len<0) {
        if(get_last_socket_error()==S_EWOULDBLOCK ||
                get_last_socket_error()==S_EAGAIN)
            s_log(LOG_INFO, "cache_transfer: recv timeout");
        else
            sockerror("cache_transfer: recv");
        str_free(packet);
        return;
    }

    /* parse results */
    if(len<(int)sizeof(CACHE_PACKET)-MAX_VAL_LEN || /* too short */
            packet->version!=1 || /* wrong version */
            memcmp(packet->key, key, key_len)) { /* wrong session id */
        s_log(LOG_DEBUG, "cache_transfer: malformed packet received");
        str_free(packet);
        return;
    }
    if(packet->type!=CACHE_RESP_OK) {
        s_log(LOG_INFO, "cache_transfer: session not found");
        str_free(packet);
        return;
    }
    *ret_len=len-(sizeof(CACHE_PACKET)-MAX_VAL_LEN);
    *ret=str_alloc(*ret_len);
    s_log(LOG_INFO, "cache_transfer: session found");
    memcpy(*ret, packet->val, *ret_len);
    str_free(packet);
}

/**************************************** informational callback */

static void info_callback(
#if OPENSSL_VERSION_NUMBER>=0x0090700fL
        const
#endif
        SSL *ssl, int where, int ret) {
    if(where & SSL_CB_LOOP) {
        s_log(LOG_DEBUG, "SSL state (%s): %s",
            where & SSL_ST_CONNECT ? "connect" :
            where & SSL_ST_ACCEPT ? "accept" :
            "undefined", SSL_state_string_long(ssl));
    } else if(where & SSL_CB_ALERT) {
        s_log(LOG_DEBUG, "SSL alert (%s): %s: %s",
            where & SSL_CB_READ ? "read" : "write",
            SSL_alert_type_string_long(ret),
            SSL_alert_desc_string_long(ret));
    } else if(where==SSL_CB_HANDSHAKE_DONE) {
        s_log(LOG_DEBUG, "%4ld items in the session cache",
            SSL_CTX_sess_number(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld client connects (SSL_connect())",
            SSL_CTX_sess_connect(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld client connects that finished",
            SSL_CTX_sess_connect_good(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld client renegotiations requested",
            SSL_CTX_sess_connect_renegotiate(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld server connects (SSL_accept())",
            SSL_CTX_sess_accept(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld server connects that finished",
            SSL_CTX_sess_accept_good(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld server renegotiations requested",
            SSL_CTX_sess_accept_renegotiate(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld session cache hits",
            SSL_CTX_sess_hits(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld external session cache hits",
            SSL_CTX_sess_cb_hits(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld session cache misses",
            SSL_CTX_sess_misses(ssl->ctx));
        s_log(LOG_DEBUG, "%4ld session cache timeouts",
            SSL_CTX_sess_timeouts(ssl->ctx));
    }
}

/**************************************** SSL error reporting */

void sslerror(char *txt) { /* OpenSSL error handler */
    unsigned long err;

    err=ERR_get_error();
    if(err) {
        sslerror_queue();
        sslerror_log(err, txt);
    } else {
        s_log(LOG_ERR, "%s: Peer suddenly disconnected", txt);
    }
}

static void sslerror_queue(void) { /* recursive dump of the error queue */
    unsigned long err;

    err=ERR_get_error();
    if(err) {
        sslerror_queue();
        sslerror_log(err, "error queue");
    }
}

static void sslerror_log(unsigned long err, char *txt) {
    char *error_string;

    error_string=str_alloc(120);
    ERR_error_string(err, error_string);
    s_log(LOG_ERR, "%s: %lX: %s", txt, err, error_string);
    str_free(error_string);
}

/* end of ctx.c */

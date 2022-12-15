/*
 *  Copyright (C) 2007 FON Wireless Limited. All rights reserved
 */

#include "../coova/config.h"
#include "chilli.h"
#include "chilli_module.h"
#include "chillout.h"

#define CHILLOUT_NO_RADAUTH (1)
#define CHILLOUT_NO_RADACCT (2)
static char chillout_options = 0;

static char *chillout_socket = 0;
static select_ctx *selectctx = 0;
static chillout_t chillout = NULL;

static int ascii_to_nibble(char c);
static int callback_default(chillout_t co, void *data, int argc, char **argv);
static int callback_dhcp(chillout_t co, void *data, int argc, char **argv);
static int callback_show(chillout_t co, void *data, int argc, char **argv);
static int callback_authorize(chillout_t co, void *data, int argc, char **argv);
static int convert_mac_string_to_six_bytes(unsigned char *array, char *mac_address);

static struct callback chilli_callbacks[] = {
  { "chilli", "dhcp", 0, callback_dhcp },
  { "chilli", "authorize", 0, callback_authorize },
  { "chilli", "show", 0, callback_show },
  { "chilli", "default", 0, callback_default },
  { "", "", 0, NULL }
};

static struct callback redir_callbacks[] = {
  { "redir", "default", 0, callback_default },
  { "", "", 0, NULL }
};

static chillout_t chillout_new(char *cmd, struct callback *cbs) {
  chillout_t co = chillout_init(chillout_socket, cmd, NULL);
  char buffer[MAX_ANSWER];
  
  if (co == NULL) {
    log_err(errno, "could not start chillout");
  } else {
    log_warn(0, "chillout started");
    chillout_write(co, CHILLOUT_WRITE_SOCK, "show version");
    co->callbacks = cbs;
    if (chillout_read(co, CHILLOUT_WRITE_SOCK, buffer)) {
      log_err(errno, "error reading from chillout");
    }
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0';
    }
    log_warn(0, "chilloutd version reported: %s", buffer); 
    chillout_read(co, CHILLOUT_WRITE_SOCK, buffer);
  }
  
  return co;
}

static inline chillout_t chillout_get() {
  if (!chillout) 
    chillout = chillout_new("chilli", chilli_callbacks);
  return chillout;
}

static void chillout_del(char final) {
  if (chillout) {
    log_warn(0, "shutting down chillout");
    if (selectctx) {
      if (final)
	net_select_dereg(selectctx, chillout->readsock);
      else
	net_select_rereg(selectctx, chillout->readsock, 0);
    }
    chillout_finish(chillout);
    chillout = NULL;
  }
}

static int handle_chillout(void *nullData, int sock) {
  int ret;
  
  if (sock == -1) {
    select_fd * sfd = (select_fd *) nullData;
    
    chillout_del(0);
    if (chillout_get())
      sfd->fd = chillout->readsock;
    
  } else {
    if (chillout) {
      ret  = chillout_accept(chillout);
      
      if (ret != 0) {
	log_err(0, "chillout_accept() failed");
	if (ret == CHILLOUT_DISCONNECTED) {
	  chillout_del(0);
	}
      }
    } else {
      log_err(0, "chillout not connected");
    }
  }
  
  return 0;
}

static int module_initialize(char *conf, char isReload) {
  char *sc;
  
  sc = strchr(conf, ';');
  if (!sc) sc = strchr(conf, ':');
  if (sc) {
    *sc++ = 0;
    if (strstr(sc, "noradauth")) {
      chillout_options |= CHILLOUT_NO_RADAUTH;
    }
    if (strstr(sc, "noradacct")) {
      chillout_options |= CHILLOUT_NO_RADACCT;
    }
  }
  
  chillout_socket = conf;  
  chillout = chillout_get();

  return CHILLI_MOD_OK;
}

static int module_net_select(select_ctx *sctx) {

  if (selectctx == 0) {
    log_dbg("%s", __FUNCTION__);

    selectctx = sctx;
    
    net_select_reg(sctx, chillout ? chillout->readsock : 0, 
		   SELECT_READ | SELECT_RESET, 
		   (select_callback) handle_chillout, 0, 0);
  }

  return CHILLI_MOD_OK;
}

static int module_redir_login(struct redir_t *redir, 
			      struct redir_conn_t *conn,
			      struct redir_socket_t *sock) {
  chillout_t co = NULL;
  unsigned char chap_password[REDIR_MD5LEN + 2];
  unsigned char chap_challenge[REDIR_MD5LEN];
  unsigned char user_password[RADIUS_PWSIZE+1];
  MD5_CTX context;
  char buffer[256];
  char error_string[256];
  int in_error = 0;
  int m, n;

  int opt = 0;

  if (chillout_options & CHILLOUT_NO_RADAUTH) 
    opt = CHILLI_MOD_REDIR_SKIP_RADIUS;
  
  log_dbg("entering %s", __FUNCTION__);
  
  co = chillout_new("redir", redir_callbacks);
  if (co == NULL) {
    log_err(errno, "chillout_init() failed");
    return -1;
  } 

  if (redir->secret && *redir->secret) {
    MD5Init(&context);
    MD5Update(&context, conn->s_state.redir.uamchal, REDIR_MD5LEN);
    MD5Update(&context, (uint8_t*) redir->secret, strlen(redir->secret));
    MD5Final(chap_challenge, &context);
  } else {
    memcpy(chap_challenge, conn->s_state.redir.uamchal, REDIR_MD5LEN);
  }
  
  switch (conn->authdata.type) {
  case REDIR_AUTH_PAP:

    for (m=0; m < RADIUS_PWSIZE;) {
      for (n=0; n < REDIR_MD5LEN; m++, n++) {
	user_password[m] = conn->authdata.v.papmsg.password[m] ^ chap_challenge[n];
      }
    }

    user_password[conn->authdata.v.papmsg.len] = 0;
    
    log_dbg("Chillout user password %d [%s]", conn->authdata.v.papmsg.len, user_password);
    
    break;
    
  case REDIR_AUTH_CHAP:
    chap_password[0] = conn->authdata.v.chapmsg.identity;
    memcpy(chap_password+1, conn->authdata.v.chapmsg.password, REDIR_MD5LEN);
    /*
     *  chap_challenge holds the challenge (length RADIUS_ATTR_CHAP_CHALLENGE)
     *  chap_password holds the password   (length RADIUS_ATTR_CHAP_PASS
     *  TODO: LOGIN WITH CHAP
     */
    break;
  }
  
  error_string[0] = '\0';
  if (chillout_write(co, CHILLOUT_WRITE_SOCK ,
		     "login %s %s %s", inet_ntoa(conn->hisip), 
		     conn->s_state.redir.username, user_password)) {
    log_err(errno, "Error calling chillout_write");
    in_error = 1;
  }
  
  if ((!in_error) && (chillout_read(co, CHILLOUT_WRITE_SOCK, buffer))) {
    log_err(errno, "Error calling chillout_read");
  }
  
  if ((!in_error) && (!strncmp(buffer, "error", 5))) {
    if (strlen(buffer) < 7) {
      log_err(errno, "Too short answer received");
      in_error = 1;
    } else {
      strcpy(error_string, buffer + 6);
      if (error_string[strlen(error_string) - 1] == '\n') {
	error_string[strlen(error_string) - 1] = '\0';
	in_error = 1;
      }
    }
  }
  
  if ((in_error) || (strncmp(buffer, "ok", 2))) {
    /* pmm this isn't an abort, exactly */
    /* appconn->uamabort = 1; */ /* Next login will be aborted */
    /* appconn->uamtime = 0; */  /* Force generation of new challenge */
    /* dhcpconn->authstate = DHCP_AUTH_DNAT; */
    /* TODO */
    /* terminate_appconn(appconn, RADIUS_TERMINATE_CAUSE_USER_REQUEST); */
    
    log_err(errno, "chillout_write returned error (reason \"%s\") applying as reply", error_string);
    
    redir_reply(redir, sock, conn, REDIR_FAILED_REJECT, NULL, 0, 
		NULL, NULL, conn->s_state.redir.userurl, error_string,
		(char *)conn->s_params.url, conn->hismac, &conn->hisip, 0);
    
    chillout_finish(co);
    log_dbg("exiting %s", __FUNCTION__);

    return CHILLI_MOD_ERROR | opt;
  } else {
    log_warn(0, "chilloutd reports success. going on...");
  }

  chillout_finish(co);
  log_dbg("exiting %s", __FUNCTION__);

  conn->response = REDIR_CHALLENGE;
  safe_snprintf((char *)conn->s_params.url,
		sizeof(conn->s_params.url),
		"http://%s:%d/www/wait.html", 
		inet_ntoa(redir->addr), redir->port);

  return CHILLI_MOD_OK | opt;
}

static int module_dhcp_connect(struct app_conn_t *appconn, 
			       struct dhcp_conn_t *dhcpconn) {
  log_dbg("entering %s", __FUNCTION__);

  if (chillout_get())
    chillout_write(chillout, CHILLOUT_WRITE_SOCK, 
		   "dhcp lease %.2X:%.2X:%.2X:%.2X:%.2X:%.2X %s",
		   dhcpconn->hismac[0], dhcpconn->hismac[1], dhcpconn->hismac[2], 
		   dhcpconn->hismac[3], dhcpconn->hismac[4], dhcpconn->hismac[5], 
		   inet_ntoa(appconn->hisip));

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_dhcp_disconnect(struct app_conn_t *appconn, 
				  struct dhcp_conn_t *dhcpconn) {
  log_dbg("entering %s", __FUNCTION__);

  if (chillout_get())
    chillout_write(chillout, CHILLOUT_WRITE_SOCK, 
		   "dhcp release %.2X:%.2X:%.2X:%.2X:%.2X:%.2X %s",
		   dhcpconn->hismac[0], dhcpconn->hismac[1], dhcpconn->hismac[2], 
		   dhcpconn->hismac[3], dhcpconn->hismac[4], dhcpconn->hismac[5],
		   inet_ntoa(dhcpconn->hisip));

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_session_start(struct app_conn_t *appconn) {
  /*  log_dbg("noop %s", __FUNCTION__); */
  return CHILLI_MOD_OK;
}

static int module_session_update(struct app_conn_t *appconn) {
  /*  log_dbg("noop %s", __FUNCTION__); */
  return CHILLI_MOD_OK;
}

static int module_session_stop(struct app_conn_t *appconn) {
  log_dbg("entering %s", __FUNCTION__);

  if (chillout_get()) {
    char cout[256];

    safe_snprintf(cout, sizeof(cout), "logout %s %s user", 
		  inet_ntoa(appconn->hisip), appconn->s_state.redir.username);
    
    if (chillout_write(chillout, CHILLOUT_WRITE_SOCK, "%s", cout)) {
      log_err(errno, "%s Error notifing chillout (exiting)", __FUNCTION__);
      return 1;
    }
  }

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_destroy(char isReload) {
  chillout_del(1);
  return CHILLI_MOD_OK;
}

struct chilli_module chillout_module = {
  CHILLI_MODULE_INIT,
  module_initialize, 
  module_net_select,
  module_redir_login,
  module_dhcp_connect,
  module_dhcp_disconnect,
  module_session_start,
  module_session_update,
  module_session_stop,
  module_destroy,
};



/** module functions **/

static int callback_default(chillout_t co, void *data, int argc, char **argv)
{
  log_err(0, "callback_default(): error unknown token %s", argv[0]);
  chillout_write(co, 0, "error unknown token %s", argv[0]);
  return 1;
}

static int callback_show(chillout_t co, void *data, int argc, char **argv)
{
  if (argc < 2) {
    chillout_write(co, 0, "error argc %d?", argc);
    return 1;
  }
  if (!strcmp(argv[1], "version")) {
    chillout_write(co, 0, "%s", VERSION);
    return 0;
  }
  chillout_write(co, 0, "error %s?", argv[1]);
  return 1;
}

static int callback_dhcp(chillout_t co, void *data, int argc, char **argv)
{
  unsigned char mac[PKT_ETH_ALEN];
  bstring s = 0;

  if (argc < 2) {
    chillout_write(co, 0, "error argc %d?", argc);
    return 1;
  }
  log_dbg("callback_dhcpi(): called");
  if (!strcmp(argv[1], "list")) {
    if (!dhcp) {
      chillout_write(co, 0, "error no dhcp");
      return 1;
    }

    s = bfromcstr("");
    dhcp_list(dhcp, s, 0, 0, LIST_SHORT_FMT);
    chillout_write(co, CHILLOUT_READ_SOCK, (char *)s->data);
    bdestroy(s);
    return 0;
  } else if (!strcmp(argv[1], "authorize")) {

    if (argc < 3) {
      chillout_write(co, CHILLOUT_READ_SOCK, "error argument missing");
      return 1;
    }

    if (convert_mac_string_to_six_bytes(mac, argv[2])) {
      chillout_write(co, CHILLOUT_READ_SOCK, "error bad formed mac address");
      return 1;
    }

    {
      struct session_params params;
      memset(&params, 0, sizeof(params));

      if (chillout_options & CHILLOUT_NO_RADACCT) 
	params.flags |= NO_ACCOUNTING;

#ifdef ENABLE_MULTIROUTE
      if (argc == 4) {
	extern struct tun_t *tun;
	params.routeidx = tun_name2idx(tun, argv[3]);
      }
#endif

      dhcp_authorize_mac(dhcp, mac, &params);
      dhcp_reset_tcp_mac(dhcp, mac);
    }

    chillout_write(co, CHILLOUT_READ_SOCK, "ok");
    return 0;
  } else if (!strcmp(argv[1], "release")) {
    if (!dhcp) {
      chillout_write(co, CHILLOUT_READ_SOCK, "error no dhcp");
      return 1;
    }
    if (argc != 3) {
      chillout_write(co, CHILLOUT_READ_SOCK, "error argument missing");
      return 1;
    }
    if (convert_mac_string_to_six_bytes(mac, argv[2])) {
      chillout_write(co, CHILLOUT_READ_SOCK, "error bad formed mac address");
      return 1;
    }
    dhcp_release_mac(dhcp, mac, 1);
    chillout_write(co, CHILLOUT_READ_SOCK, "ok");
    /* this serialization of the release answer is a workaround */
    chillout_write(chillout, CHILLOUT_WRITE_SOCK, 
		   "dhcp release %s unset", argv[2]);
    return CHILLOUT_NOOK;
  } else if (!strcmp(argv[1], "show")) {
    chillout_write(co, CHILLOUT_READ_SOCK, "error todo");
    return 1;
  }
  chillout_write(co, CHILLOUT_READ_SOCK, "error %s?", argv[1]);
  return 1;
}

static int convert_mac_string_to_six_bytes(unsigned char *array, char *mac_address)
{
  int nib0, nib1, byte;
  char *p = mac_address;
  int i = 0;

  while(1) {
    nib0 = ascii_to_nibble(*p);
    nib1 = ascii_to_nibble(*(p + 1));
    if ((nib0 == -1) || (nib1 == -1)) {
      log_err(0, "%s(): Error decoding mac address. Invalid caracters", __FUNCTION__);
      return -1;
    }
    byte = (nib0*16) + nib1;
    if ((byte < 0) || (byte > 255)) {
      log_err(0, "%s(): Error decoding mac address. byte", __FUNCTION__);
      return -1;
    }
    array[i] = (unsigned char)byte;

    if (*(p+2) == '\0')
      break;
    p+=3;
    if (i == 5) {
      log_err(0, "%s(): Error decoding mac address", __FUNCTION__);
      return -1;
    }
    i++;
  }
  return 0;
}

static int ascii_to_nibble(char c)
{
  if ((c >= 'A') && (c <= 'F'))
    return c - 'A' + 10;
  else if ((c >= 'a') && (c <= 'f'))
    return c - 'a' + 10;
  else if ((c >= '0') && (c <= '9'))
    return c - '0';
  else
    return -1;

  return 0;
}

static int callback_authorize(chillout_t co, void *data, int argc, char **argv)
{
  if (argc < 2) {
    chillout_write(co, 0, "error argc");
    return 1;
  }
  chillout_write(co, 0, "error todo");
  return 1;
}


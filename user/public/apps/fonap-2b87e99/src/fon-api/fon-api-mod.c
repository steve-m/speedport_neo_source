/*
 *  Copyright (C) 2011 FON Wireless Limited. 
 */

#include "../coova/config.h"
#include "chilli.h"
#include "chilli_module.h"

#define FON_API "/usr/sbin/fon-api"

static char api_program[512];
static char waitForLogin = 1;

static char turnOnRadius = 0;
static char turnOffAccounting = 1;

static int run_fon_api(char *cmd, 
		       struct app_conn_t *appconn) {
  int cpid;
  uint32_t sessiontime;

  if ((cpid = chilli_fork(CHILLI_PROC_SCRIPT, cmd)) < 0) {
    log_err(errno, "forking %s", api_program);
    return 0;
  }
  
  if (cpid > 0) { /* Parent */
    return 0; 
  } 
  
  if (appconn) {
    set_env("USER_NAME", VAL_STRING, appconn->s_state.redir.username, 0);
    set_env("FRAMED_IP_ADDRESS", VAL_IN_ADDR, &appconn->hisip, 0);
    set_env("CUI", VAL_STRING, appconn->s_state.redir.cuibuf, appconn->s_state.redir.cuilen);
    set_env("SESSION_TIMEOUT", VAL_ULONG64, &appconn->s_params.sessiontimeout, 0);
    set_env("IDLE_TIMEOUT", VAL_ULONG, &appconn->s_params.idletimeout, 0);
    set_env("CALLING_STATION_ID", VAL_MAC_ADDR, appconn->hismac, 0);
    set_env("CALLED_STATION_ID", VAL_MAC_ADDR, dhcp_nexthop(dhcp), 0);
    set_env("NAS_ID", VAL_STRING, _options.radiusnasid, 0);
    set_env("ACCT_SESSION_ID", VAL_STRING, appconn->s_state.sessionid, 0);
    set_env("ACCT_INTERIM_INTERVAL", VAL_USHORT, &appconn->s_params.interim_interval, 0);
    set_env("WISPR_LOCATION_ID", VAL_STRING, _options.radiuslocationid, 0);
    set_env("WISPR_LOCATION_NAME", VAL_STRING, _options.radiuslocationname, 0);
    set_env("WISPR_BANDWIDTH_MAX_UP", VAL_ULONG, &appconn->s_params.bandwidthmaxup, 0);
    set_env("WISPR_BANDWIDTH_MAX_DOWN", VAL_ULONG, &appconn->s_params.bandwidthmaxdown, 0);
    set_env("CHILLISPOT_MAX_INPUT_OCTETS", VAL_ULONG64, &appconn->s_params.maxinputoctets, 0);
    set_env("CHILLISPOT_MAX_OUTPUT_OCTETS", VAL_ULONG64, &appconn->s_params.maxoutputoctets, 0);
    set_env("CHILLISPOT_MAX_TOTAL_OCTETS", VAL_ULONG64, &appconn->s_params.maxtotaloctets, 0);
    set_env("INPUT_OCTETS", VAL_ULONG64, &appconn->s_state.input_octets, 0);
    set_env("OUTPUT_OCTETS", VAL_ULONG64, &appconn->s_state.output_octets, 0);
    sessiontime = mainclock_diffu(appconn->s_state.start_time);
    set_env("SESSION_TIME", VAL_ULONG, &sessiontime, 0);
    sessiontime = mainclock_diffu(appconn->s_state.last_sent_time);
    set_env("IDLE_TIME", VAL_ULONG, &sessiontime, 0);
    if (appconn->s_state.terminate_cause)
      set_env("TERMINATE_CAUSE", VAL_ULONG, 
	      &appconn->s_state.terminate_cause, 0);
  }

  if (execl(api_program, api_program, cmd, (char *) 0) != 0) {
    log_err(errno, "exec %s failed", api_program);
    exit(-1);
  }
  
  return 0;
}

static int run_fon_login(char *cmd, 
			 struct redir_t *redir, 
			 struct redir_conn_t *conn,
			 char *password) {
  int cpid;
  int p[2];

  if (waitForLogin) {
    if (pipe(p)) {
      log_err(errno, "pipe()");
      return 0;
    }
  }
  
  if ((cpid = chilli_fork(CHILLI_PROC_SCRIPT, cmd)) < 0) {
    log_err(errno, "forking %s", api_program);
    return 0;
  }
  
  if (cpid > 0) { 
    /* 
     *  Parent process
     */
    
    if (waitForLogin) {
      /*
       *  When we wait for the login handler, we will check 
       *  the process return code and stdout (for a reply-message)
       */
      int result=REDIR_FAILED_OTHER;
      int status;
      char msg[1024];
      
      msg[0]=0;
      close(p[1]);
      
      if (waitpid(cpid, &status, 0) == -1) {
	status = REDIR_FAILED_OTHER;
	log_err(errno, "waitpid()");
      } else {
	int len = read(p[0], msg, sizeof(msg)-1);
	if (len > 0) {
	  log_dbg("read %d from login handler", len);
	  msg[len]=0;
	} else {
	  msg[0]=0;
	}
	close(p[0]);
	
	result = WEXITSTATUS(status);
	log_dbg("login exit result %d", result);
      }
      
      if (status == 0) {
	conn->response = REDIR_SUCCESS;
      } else if (status > 0) {
	conn->response = result;
	if (msg[0]) {
	  strncpy(conn->replybuf, msg, sizeof(conn->replybuf));
	  conn->reply = conn->replybuf;
	}
      } else {
	conn->response = REDIR_CHALLENGE;
	safe_snprintf((char *)conn->s_params.url,
		      sizeof(conn->s_params.url),
		      msg[0] ? msg : "http://%s:%d/www/wait.html", 
		      inet_ntoa(redir->addr), redir->port);
      }
      
      log_dbg("login response %d", conn->response);

      switch(conn->response) {
      case REDIR_SUCCESS:
	session_param_defaults(&conn->s_params);
	break;
      }

    } else {
      /*
       *  When not waiting for login, go to polling "wait" page
       */
      conn->response = REDIR_CHALLENGE;
      safe_snprintf((char *)conn->s_params.url,
		    sizeof(conn->s_params.url),
		    "http://%s:%d/www/wait.html", 
		    inet_ntoa(redir->addr), redir->port);
    }

    if (turnOffAccounting)
      conn->s_params.flags |= NO_ACCOUNTING;
       
    return 0; 
  } 
  
  if (waitForLogin) {
    close(p[0]);
    dup2(p[1], STDOUT_FILENO);
    close(p[1]);
  }
  
  set_env("USER_NAME", VAL_STRING, conn->s_state.redir.username, 0);
  setenv("PASSWORD", password, 1);
  
  set_env("FRAMED_IP_ADDRESS", VAL_IN_ADDR, &conn->hisip, 0);
  set_env("CALLING_STATION_ID", VAL_MAC_ADDR, conn->hismac, 0);
  set_env("CALLED_STATION_ID", VAL_MAC_ADDR, dhcp_nexthop(dhcp), 0);
  set_env("NAS_ID", VAL_STRING, _options.radiusnasid, 0);
  set_env("ACCT_SESSION_ID", VAL_STRING, conn->s_state.sessionid, 0);
  set_env("WISPR_LOCATION_ID", VAL_STRING, _options.radiuslocationid, 0);
  set_env("WISPR_LOCATION_NAME", VAL_STRING, _options.radiuslocationname, 0);

  if (execl(api_program, api_program, cmd, (char *) 0) != 0) {
    log_err(errno, "exec %s failed", api_program);
    exit(-1);
  }
  
  return 0;
}

static int module_initialize(char *conf, char isReload) {
  char *api = FON_API;
  int api_length = strlen(api);
  char *sc;
  
  if (conf) {
    sc = strchr(conf, ';');
    if (!sc) sc = strchr(conf, ':');
    if (sc) {
      api_length = (int) (sc - conf);
      if (strstr(sc, "doradauth")) {
	turnOnRadius = 1;
      }
      if (strstr(sc, "noradacct")) {
	turnOffAccounting = 1;
      }
    } else {
      api_length = strlen(conf);
    }
    api = conf;
  }

  memset(api_program, 0, sizeof(api_program));
  strncpy(api_program, api, api_length);
  
  if (!isReload)
    run_fon_api("fon-startup", 0);
  
  return CHILLI_MOD_OK;
}

static int module_redir_login(struct redir_t *redir, 
			      struct redir_conn_t *conn,
			      struct redir_socket_t *sock) {
  unsigned char chap_password[REDIR_MD5LEN + 2];
  unsigned char chap_challenge[REDIR_MD5LEN];
  unsigned char user_password[RADIUS_PWSIZE+1];
  MD5_CTX context;
  int m, n;

  log_dbg("entering %s", __FUNCTION__);
  
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
  
  log_dbg("exiting %s", __FUNCTION__);

  run_fon_login("login", redir, conn, (char *)user_password);

  return CHILLI_MOD_OK | 
    (turnOnRadius ? 0 : CHILLI_MOD_REDIR_SKIP_RADIUS);
}

static int module_dhcp_connect(struct app_conn_t *appconn, 
			       struct dhcp_conn_t *dhcpconn) {
  log_dbg("entering %s", __FUNCTION__);

  run_fon_api("dhcp-lease", appconn);

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_dhcp_disconnect(struct app_conn_t *appconn, 
				  struct dhcp_conn_t *dhcpconn) {
  log_dbg("entering %s", __FUNCTION__);

  run_fon_api("dhcp-release", appconn);

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_session_start(struct app_conn_t *appconn) {
  /*  log_dbg("noop %s", __FUNCTION__); */

  run_fon_api("session-start", appconn);

  return CHILLI_MOD_OK;
}

static int module_session_update(struct app_conn_t *appconn) {
  /*  log_dbg("noop %s", __FUNCTION__); */

  run_fon_api("session-update", appconn);

  return CHILLI_MOD_OK;
}

static int module_session_stop(struct app_conn_t *appconn) {
  log_dbg("entering %s", __FUNCTION__);

  run_fon_api("session-stop", appconn);

  log_dbg("exiting %s", __FUNCTION__);
  return CHILLI_MOD_OK;
}

static int module_destroy(char isReload) {

  if (!isReload)
    run_fon_api("fon-shutdown", 0);
  
  return CHILLI_MOD_OK;
}

struct chilli_module fon_api_module = {
  CHILLI_MODULE_INIT,
  module_initialize, 
  0,
  module_redir_login,
  module_dhcp_connect,
  module_dhcp_disconnect,
  module_session_start,
  module_session_update,
  module_session_stop,
  module_destroy,
};


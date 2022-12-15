#ifndef _VOIP_MSG_Q_H_
#define _VOIP_MSG_Q_H_

#ifndef MSG_R
#define MSG_R		0x100
#endif

#ifndef MSG_W
#define MSG_W		0x80
#endif

#define CGIMSG_PATH		"/etc/default"
#define PROVMSG_PATH	"/etc/rcS"
#define CGI_PROJ_ID		3
#define CGIMSG_LEN		128


#define MSG_SPY_CLEAR 			4100
#define MSG_SPY_UPDATE 			4101
#define MSG_SIPTRACE_UPDATE		4102
#define MSG_SIPTRACE_CLEAR	 	4103
#define MSG_SPY_LOGLEVEL	    4104
#define MSG_INNER_STATUS        4105
#define MSG_DIAGNOSE_ALL        4106

struct CgiMsgbuff{
    long    mtype;
    char    mtext[CGIMSG_LEN];
};

int CGISendMsgq(char *msg,long msgtyp, int msgflg);
int CGIRecvMsgq(long msgtyp, int msgflg,char *message);
int CGISendSigUser1(char *msg);

#endif


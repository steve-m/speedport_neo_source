#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "byte.h"
#include "socket.h"
#include "ip6.h"
#include "error.h"
#include "uint32.h"

int socket_connect6(int s,const char ip[16],uint16 port,uint32 scope_id)
{
  struct sockaddr_in6 sa;

  byte_zero(&sa,sizeof sa);
  sa.sin6_family = PF_INET6;
  uint16_pack_big((char *) &sa.sin6_port,port);
  sa.sin6_flowinfo = 0;
  sa.sin6_scope_id = scope_id;
  byte_copy((char *) &sa.sin6_addr,16,ip);

  return connect(s,(struct sockaddr *) &sa,sizeof sa);
}

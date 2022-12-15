#include <sys/param.h>
#include "sockaddr_in6.h"
#include "byte.h"
#include "socket.h"
#include "ip6.h"
#include "error.h"

int socket_bind6(int s,const char ip[16],uint16 port,uint32 scope_id)
{
  struct sockaddr_in6 sa;

  byte_zero(&sa,sizeof sa);
  sa.sin6_family = AF_INET6;
  uint16_pack_big((char *) &sa.sin6_port,port);
/*  implicit: sa.sin6_flowinfo = 0; */
  byte_copy((char *) &sa.sin6_addr,16,ip);
  sa.sin6_scope_id=scope_id;

  return bind(s,(struct sockaddr *) &sa,sizeof sa);
}

int socket_bind6_reuse(int s,const char ip[16],uint16 port,uint32 scope_id)
{
  int opt = 1;
  setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof opt);
  return socket_bind6(s,ip,port,scope_id);
}


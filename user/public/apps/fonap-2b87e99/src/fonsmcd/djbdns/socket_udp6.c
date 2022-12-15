#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include "ndelay.h"
#include "socket.h"
#include "error.h"

int socket_udp6(void)
{
  int s;

  s = socket(PF_INET6,SOCK_DGRAM,0);
  if (s == -1) {
    return -1;
  }
  if (ndelay_on(s) == -1) { close(s); return -1; }
#ifdef IPV6_V6ONLY
  {
    int zero=0;
    setsockopt(s,IPPROTO_IPV6,IPV6_V6ONLY,(void*)&zero,sizeof(zero));
  }
#endif
  return s;
}

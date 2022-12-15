#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

#include "sal_route.h"
#define _PATH_PROCNET_ROUTE  "/proc/net/route"

#ifndef RTF_UP
/* Keep this in sync with /usr/src/linux/include/linux/route.h */
#define RTF_UP          0x0001	/* route usable                 */
#define RTF_GATEWAY     0x0002	/* destination is a gateway     */
#define RTF_HOST        0x0004	/* host entry (net otherwise)   */
#define RTF_REINSTATE   0x0008	/* reinstate route after tmout  */
#define RTF_DYNAMIC     0x0010	/* created dyn. (by redirect)   */
#define RTF_MODIFIED    0x0020	/* modified dyn. (by redirect)  */
#define RTF_MTU         0x0040	/* specific MTU for this route  */
#ifndef RTF_MSS
#define RTF_MSS         RTF_MTU	/* Compatibility :-(            */
#endif
#define RTF_WINDOW      0x0080	/* per route window clamping    */
#define RTF_IRTT        0x0100	/* Initial round trip time      */
#define RTF_REJECT      0x0200	/* Reject route                 */
#endif

static const unsigned int flagvals[] = { /* Must agree with flagchars[]. */
	RTF_GATEWAY,
	RTF_HOST,
	RTF_REINSTATE,
	RTF_DYNAMIC,
	RTF_MODIFIED,
#ifdef CONFIG_FEATURE_IPV6
	RTF_DEFAULT,
	RTF_ADDRCONF,
	RTF_CACHE
#endif
};

#define IPV4_MASK (RTF_GATEWAY|RTF_HOST|RTF_REINSTATE|RTF_DYNAMIC|RTF_MODIFIED)
#define IPV6_MASK (RTF_GATEWAY|RTF_HOST|RTF_DEFAULT|RTF_ADDRCONF|RTF_CACHE)

static const char flagchars[] =		/* Must agree with flagvals[]. */
	"GHRDM"
#ifdef CONFIG_FEATURE_IPV6
	"DAC"
#endif
;

static void set_flags(char *flagstr, int flags)
{
	int i;

	*flagstr++ = 'U';

	for (i = 0; (*flagstr = flagchars[i]) != 0; i++) {
		if (flags & flagvals[i]) {
			++flagstr;
		}
	}
}
int sal_route_get_route_entry(sal_route** route_info)
{
	unsigned long int d, g, m;
	int flgs, ref, use, metric, mtu, win, ir;
	struct in_addr tmp;
	FILE *fp = NULL;
	static sal_route route[SAL_ROUTE_MAX_ENTRY];
    int r = 0, i = 0;
    
    
	fp = fopen(_PATH_PROCNET_ROUTE, "r");
    if (!fp)
        return 0;
	if (fscanf(fp, "%*[^\n]\n") < 0)
    {   
        fclose(fp);
        return 0;
    }   
	for (i=0; i<SAL_ROUTE_MAX_ENTRY; i++) 
	{
		r = fscanf(fp, "%63s%lx%lx%X%d%d%d%lx%d%d%d\n",
				   route[i].dev, &d, &g, &flgs, &ref, &use, &metric, &m,
				   &mtu, &win, &ir);
				   
		//printf("fscanf.r=%d\n", r);		   
		if (r != 11)
		    goto end;
		    
		tmp.s_addr = d;
		if (d == INADDR_ANY)
		    snprintf(route[i].dst, sizeof(route[i].dst), "*");
		else
		    snprintf(route[i].dst, sizeof(route[i].dst), inet_ntoa(tmp));

        tmp.s_addr = g;
        if (g == INADDR_ANY)
            snprintf(route[i].gw, sizeof(route[i].gw), "*");
        else
		    snprintf(route[i].gw, sizeof(route[i].gw), inet_ntoa(tmp));

		tmp.s_addr = m;		
		snprintf(route[i].mask, sizeof(route[i].mask), inet_ntoa(tmp));
		
		set_flags(route[i].flags, (flgs & IPV4_MASK));
		
		snprintf(route[i].metric, sizeof(route[i].metric), "%d", metric);
		snprintf(route[i].ref, sizeof(route[i].ref), "%d", ref);
		snprintf(route[i].use, sizeof(route[i].use), "%d", use);	
	}
end:
    fclose(fp);	
	*route_info = route;
	return i;
}

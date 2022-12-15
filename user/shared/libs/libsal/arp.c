#include <stdio.h>
#include "sal_arp.h"

#define _PATH_PROCNET_ARP "/proc/net/arp"

int sal_arp_get_arp_entry(sal_arp ** arp_info)
{
	FILE *fp = NULL;
	static sal_arp arp[SAL_ARP_MAX_ENTRY];	
	char line[512] = "";
	int tmp_num = 0;
	int cnt = 0;

	fp = fopen(_PATH_PROCNET_ARP, "r");
	if (!fp)
		return 0;
	
	if (fgets(line, sizeof(line), fp) == NULL)
		goto end;
	for (; fgets(line, sizeof(line), fp) && (cnt < SAL_ARP_MAX_ENTRY);)
	{
		tmp_num = sscanf(line, "%s 0x%x 0x%x %100s %100s %100s\n",
			arp[cnt].ip, &(arp[cnt].type),&(arp[cnt].flags),
			 arp[cnt].hwa, arp[cnt].mask, arp[cnt].dev);
		if (tmp_num < 4)
			goto end;
		cnt ++;	
	}
	
end:
	fclose(fp);
	*arp_info = arp;
	return cnt;		
}

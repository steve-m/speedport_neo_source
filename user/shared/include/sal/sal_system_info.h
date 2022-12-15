#ifndef _SAL_SYSTEM_INFO_H
#define _SAL_SYSTEM_INFO_H

double sal_get_mem_utilization(void);

/* interval means  time interval of cpu utilization test*/
double sal_get_cpu_utilization(int interval);

#endif

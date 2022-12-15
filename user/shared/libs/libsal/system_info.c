#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#ifdef BASE_ON_MPSTAT

#define SHOW_CPU_FILE "/var/run/show_cpu"
static double get_cpu_utilization(void)
{
    FILE *fp = NULL;
    double ret = 0.0;
    char buf[16]="";
    
    SYSTEM("/usr/sbin/mpstat > "SHOW_CPU_FILE);
    fp = fopen(SHOW_CPU_FILE, "r");
    if (!fp)
        goto end;        
    fseek(fp, -6, SEEK_END);
    fread(buf, 6, 1, fp);
    fclose(fp);    
    ret = 100 - atof(buf);
    unlink(SHOW_CPU_FILE);
end:
    return ret;
}
#else

#define STAT "/proc/stat"

struct stats_cpu 
{
	unsigned long long cpu_user	__attribute__ ((aligned (16)));
	unsigned long long cpu_nice	__attribute__ ((aligned (16)));
	unsigned long long cpu_sys	__attribute__ ((aligned (16)));
	unsigned long long cpu_idle	__attribute__ ((aligned (16)));
	unsigned long long cpu_iowait	__attribute__ ((aligned (16)));
	unsigned long long cpu_steal	__attribute__ ((aligned (16)));
	unsigned long long cpu_hardirq	__attribute__ ((aligned (16)));
	unsigned long long cpu_softirq	__attribute__ ((aligned (16)));
};

static int get_cpu_count(int *total, int *idle)
{
    FILE *fp = NULL;
    char line[8192] = "";
    struct stats_cpu st_cpu;
    if ((fp = fopen(STAT, "r")) == NULL)
        return -1; 
        
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
		if (!strncmp(line, "cpu ", 4)) 
		{
			memset(&st_cpu, 0, sizeof(struct stats_cpu ));	
			sscanf(line + 5, "%llu %llu %llu %llu %llu %llu %llu %llu",
			       &(st_cpu.cpu_user),
			       &(st_cpu.cpu_nice),
			       &(st_cpu.cpu_sys),
			       &(st_cpu.cpu_idle),
			       &(st_cpu.cpu_iowait),
			       &(st_cpu.cpu_hardirq),
			       &(st_cpu.cpu_softirq),
			       &(st_cpu.cpu_steal));
			break;
        }
    }
    *idle  = st_cpu.cpu_idle;
    *total = st_cpu.cpu_user + st_cpu.cpu_nice + st_cpu.cpu_sys + st_cpu.cpu_idle
            + st_cpu.cpu_iowait + st_cpu.cpu_hardirq + st_cpu.cpu_softirq + st_cpu.cpu_steal;
    
    fclose(fp);
    return 0;   
}
static int alarm_flag = 0;
void alarm_handle(int sig)
{
    alarm_flag = 1;
}
double sal_get_cpu_utilization(int interval)
{
    double ret = 0.0;
    int last_total = 0, last_idle = 0, now_total = 0, now_idle = 0;
    if (0 != get_cpu_count(&last_total, &last_idle))
        goto end;
    signal(SIGALRM, alarm_handle);
	alarm(interval);
    pause();
	if (0 != get_cpu_count(&now_total, &now_idle))
	    goto end;
	ret = 100.0 - (double)(now_idle - last_idle) * 100.0 /(double)(now_total - last_total);
	return ret;
end:
    return -1;
}
#endif

double sal_get_mem_utilization(void)
{
    FILE *fp = NULL;
    char buf[128] = "";
    char mem_free[64] = "";
    char mem_total[64] = "";
    double ret = 0.0, mem = 0.0, total = 0.0;
    
    if ((fp = fopen("/proc/meminfo", "r")))
    {
        while (fgets(buf, sizeof(buf), fp))
        {
            if (strstr(buf, "MemFree:"))
            {
                snprintf(mem_free, sizeof(mem_free), "%s", (buf + sizeof("MemFree:")));
            }
            else if (strstr(buf, "MemTotal:"))
            {
                snprintf(mem_total, sizeof(mem_total), "%s", (buf + sizeof("MemTotal:")));
            }
        }
        fclose(fp);
    }
    else
        goto end;
    
    mem = atoi(mem_free)*100;
    total = atoi(mem_total);
    
    ret = 100 - mem / total;
    
end:    
    return ret;
}


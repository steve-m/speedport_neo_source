#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>
#include <linux/netfilter.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_timestamp.h>
#include <net/netfilter/nf_conntrack.h>

#if defined(CONFIG_BCM_KF_RUNNER)
#if defined(CONFIG_BCM_RDPA) || defined(CONFIG_BCM_RDPA_MODULE)
#include <net/bl_ops.h>
#endif /* CONFIG_BCM_RUNNER */
#endif /* CONFIG_BCM_KF_RUNNER */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FLUSH_CONNTARCK");

static u_int8_t protonum_nat = 0;
static __u32 dst_ip_nat = 0;
static __u16 start_port_nat = 0;
static __u16 end_port_nat = 0;
static int flag_nat = 0;

extern void (*pnf_conntrack_flush)(struct net *net);
extern void death_by_timeout(unsigned long ul_conntrack);
extern struct nf_conn * get_next_corpse(struct net *net, 
                int (*iter)(struct nf_conn *i, void *data),
		void *data, unsigned int *bucket);

static struct proc_dir_entry *conn_clear_file = NULL;

void clear_nfconntrack(u_int8_t protonum, __u32 dst_ip, 
             __u16 start_port, __u16 end_port,int flag);
int conn_clear_read_proc(struct file *filp,char *buf,
                         size_t count,loff_t *offp);
int conn_clear_write_proc(struct file *filp,const char *buf,
                          size_t count , loff_t *offp);

static void nf_ct_iterate_cleanup_nat(struct net *net,
			   int (*iter)(struct nf_conn *i, void *data),
			   void *data)
{
	struct nf_conn *ct;
	unsigned int bucket = 0;

	if(flag_nat == 0)
		return;

	while ((ct = get_next_corpse(net, iter, data, &bucket)) != NULL) {
		/* Time to push up daises... */
			if (del_timer(&ct->timeout))
				death_by_timeout((unsigned long)ct);
			/* ... else the timer will get him soon. */

			nf_ct_put(ct);
	}
}

static int kill_nat_port(struct nf_conn *i, void *data)
{
	__u16 udp_port = i->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.udp.port;
	__u16 tcp_port = i->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.tcp.port;
	__u32 dst_ip = i->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.in.s_addr;
	u_int8_t protonum = i->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;

	if(protonum == protonum_nat)
	{
		if(((ntohs(udp_port) >= start_port_nat && ntohs(udp_port) <= end_port_nat)
					|| (ntohs(tcp_port) >= start_port_nat && ntohs(tcp_port) <= end_port_nat))
				&& dst_ip == htonl(dst_ip_nat))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

static void nf_conntrack_flush(struct net *net)
{
    if (flag_nat == 1)
    {
        nf_ct_iterate_cleanup_nat(net, kill_nat_port, NULL);
        flag_nat = 0;
    }
}

void clear_nfconntrack(u_int8_t protonum, __u32 dst_ip, __u16 start_port, __u16 end_port,int flag)
{
	protonum_nat = protonum;
	dst_ip_nat = dst_ip;
	start_port_nat = start_port;
	end_port_nat = end_port;
	flag_nat = flag;
}

static struct file_operations conn_clear_fops={
    read : conn_clear_read_proc,
    write: conn_clear_write_proc,
};

int conn_clear_read_proc(struct file *filp,char *buf,
                         size_t count, loff_t *offp)
{
	int len=0;
	
	if(*offp!=0) return 0;
	len=sprintf(buf, "0\n");
	*offp=len;
	return len;
}

int conn_clear_write_proc(struct file *filp,const char *buf,
                          size_t count , loff_t *offp)
{
    int do_clear=0;
    __u32 protonum = 0;
    __u32 dst_ip = 0;
    __u32 start_port = 0;
    __u32 end_port = 0;
    sscanf(buf, "%u,%u,%u,%u\n", &protonum,&dst_ip,
           &start_port,&end_port);
    if (protonum && dst_ip && start_port && end_port)
        do_clear = 1;
    else 
    	return count;
    if (do_clear==1)
        clear_nfconntrack((u_int8_t)protonum,dst_ip,
                          (__u16)start_port,(__u16)end_port,
                          do_clear);
    return count;
}

int init_flush_conntrack(void)
{

    conn_clear_file = create_proc_entry("flush_conntrack",
                                        0666,NULL);
    if (conn_clear_file == NULL)
    {
        pnf_conntrack_flush = NULL;
        printk(KERN_INFO"flush_conntrack create failed\n");
        return -ENOMEM;
    }
    conn_clear_file->proc_fops = &conn_clear_fops;
    pnf_conntrack_flush = nf_conntrack_flush;
    printk(KERN_INFO"flush_conntrack Module loaded\n");
    return 0;
}

void cleanup_flush_conntrack(void)
{
    pnf_conntrack_flush = NULL;
    flag_nat = 0;
    remove_proc_entry("flush_conntrack",NULL);
    printk(KERN_INFO"flush_conntrack Module unloaded\n");
}

module_init( init_flush_conntrack );
module_exit( cleanup_flush_conntrack );


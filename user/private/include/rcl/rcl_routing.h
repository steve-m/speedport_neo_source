#ifndef __RCL_ROUTING_H__
#define __RCL_ROUTING_H__


int rcl_add_dynamic_routing_per_interface(char *inf, int wan);
int rcl_del_dynamic_routing_per_interface(char *inf, int wan);
int rcl_start_policy_routing(int wan);
int rcl_stop_policy_routing(int wan);

#endif

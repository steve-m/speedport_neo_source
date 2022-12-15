#ifndef __CML_PUBLIC_API_H_
#define __CML_PUBLIC_API_H_

/****************************************************************************
Function name : cm_value_get
Description:
	Get the value of target URI node, it will return an allocated buffer directly(no need given buffer).
	Remember, you have to free the returned buffer by yourself
Input :
	uri => location of target URI node
Example:
	
Return:
	If the target URI is not exist, return an NULL pointer. Otherwise, return an allocated buffer of target URI.
*****************************************************************************/
char* cm_value_get(const char *format, ...);

/****************************************************************************
Function name : cm_value_set
Return:
	0(success) or other value
*****************************************************************************/
int cm_value_set(char *value, const char *format, ...);
int cm_virtual_value_set(char *value, const char *format, ...);

/****************************************************************************
Function name : cm_commit
Description:
	Save configurations into flash
Return:
	0(success) or other value
*****************************************************************************/
int cm_commit(void);

/****************************************************************************
Function name : cm_instance_add
Input : 
 	URI => the uri of instance you want to create without instance number. For exampe, if you wanna to look up "LANDevice", the uri is "InternetGatwayDevice.LANDevice."
	index => the instance number to be created
	For example, if you wanna to add "InternetGatewayDevice.LANDevice.1.Hosts.Host.3.".
	The parameters will be 
		URI = InternetGatewayDevice.LANDevice.1.Hosts.Host.
		index = 3
		
This function is based on TR069 specification. Applications can add an object node at an instansible node.

Definitions:

1. The first node is always there. 
If AP would like to remove the first node, this lib wouldn't acturally remove it. (Set disabled flag)
It will set NumberOfEntries to 0, remove the value of instance 1, and then, keep the structure

So, when we try to add instance and fiind the NumberOfEntries is 0, we should set up the first instance, and update NumberOfEntries to 1.

2. The all instances must be connected together.
The structure of linked list should be look like this 

"other data" -> "instance.1." -> "intstance.2." -> ..... -> "instance N" -> " other data"


3. The order of those instance may not be sequentail, but must be ascending sort. For example,

"instance.1." -> "intstance.2." -> "intstance.7." -> "intstance.8." -> "intstance.10." (OK)
"instance.1." -> "intstance.2." -> "intstance.8." -> "intstance.7." -> "intstance.10." (Wrong)

*****************************************************************************/
int cm_instance_add(int index, const char *format, ...);
int cm_virtual_instance_add(int index, const char *format, ...);

/****************************************************************************
Function name : cm_instance_del
Description:
	Opposite to function  "CM_AddInstance", if will delete an instance node
Input :
	uri => location of target instance without instance number. For exampe, if you wanna to look up "LANDevice", the uri is "InternetGatwayDevice.LANDevice."
	index => target instance number you want to delete
	
Result in buffer:
	Intance list in ascending sort is formated by comma-seperated.
*****************************************************************************/
int cm_instance_del(int index, const char *format, ...);
int cm_virtual_instance_del(int index, const char *format, ...);

/****************************************************************************
Function name : cm_instance_get
Description:
	Get a comma-seperated string of existing instances.
Input :
	uri => location of target instance without instance number. For exampe, if you wanna to look up "LANDevice", the uri is "InternetGatwayDevice.LANDevice."
	buffer => an string array to get data
	buffer_len => the length of buffer
	For example, if you wanna to the instance list of "InternetGatewayDevice.LANDevice.1.Hosts.Host.{i}.".
	The inputted uri should be "InternetGatewayDevice.LANDevice.1.Hosts.Host.".
	
Result in buffer:
	Intance list in ascending sort is formated by comma-seperated.
*****************************************************************************/
char* cm_instance_get(const char *format, ...);

/****************************************************************************
Function name : cm_instance_get_array
Description:
	Get a comma-seperated string of existing instances.
Input :
	array: index context
return:
       return index num.
*****************************************************************************/

int cm_instance_get_array(int **array, const char *format, ...);


/****************************************************************************
Function name : cm_instance_get_new
Description:
	Get the smallest instance index which able to be added.
Input :
	uri => location of target instance without instance number. For exampe, if you wanna to look up "LANDevice", the uri is "InternetGatwayDevice.LANDevice."
	min_index => obtain the smallest index
	For example, if the number of existing instances are 1, 2, 4, and 5, the min_index will be 3.
	
Return:

*****************************************************************************/
int cm_instance_get_new(int* min_index, char* format, ...);

/****************************************************************************
Function name : cm_instance_insert
Description:
	Insert a new instance node 
Input :
	uri => The location you want to insert ( Without instance number )
	index => Instance number
Example:
	There are some instance at "AAA.BBB.CCC.{i}.", and the instance list is "1,2,3,4,5,"

	If we wanna to insert a new instance at index 3

	After the command finish, the instance list will be "1,2,3(inserted),4,5,6,"
	
Return:
	Status code defined in cml_type.h
*****************************************************************************/
int cm_instance_insert(int index, const char *format, ...);
int cm_virtual_instance_insert(int index, const char *format, ...);

int cm_config_export(char *file_out);
int cm_config_import(char *file_in);
int cm_config_import_nodecrypt(char *file_in);
int cm_config_default(void);

#endif // __CML_PUBLIC_API_H_


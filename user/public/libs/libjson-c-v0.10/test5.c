/*
 * gcc -o utf8 utf8.c -I/home/y/include -L./.libs -ljson
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "config.h"

#include "json_inttypes.h"
#include "json_object.h"
#include "json_tokener.h"

int main() {
    int retval = 0;
    json_object *my_object,  *my_array, *my_string, *my_object2;
    int i;
    int file_obj_len = 0;

    if (access("Login.json", F_OK) == 0)
        printf("<%s,%d>file_obj\n",__FILE__,__LINE__);
    struct json_object *file_obj = json_object_from_file("Login.json");
    printf("<%s,%d>file_obj\n",__FILE__,__LINE__);
    if (!file_obj)
    {
        printf("<%s,%d>file_obj NULL\n",__FILE__,__LINE__);
        return 0;
    }
    
    file_obj_len = json_object_array_length(file_obj);
    printf("<%s,%d>file_obj_len=%d\n",__FILE__,__LINE__,file_obj_len);
   
    for(i=0; i<file_obj_len; i++)
    {
        struct json_object *val;
        struct json_object *o;

        val = json_object_array_get_idx(file_obj, i);
        if (val)
        {
            printf("val[%d] = %s\n",i,json_object_to_json_string(val));
            o = json_object_object_get(val,"varid");
            printf("json_object_get_string()=%s\n",json_object_get_string(o));
            if (strcmp(json_object_get_string(o),"loginstate")==0)
            {
                json_object_object_del(val,"varvalue");
                json_object_object_add(val,"varvalue",json_object_new_string("1"));
            }
        }
    }
    
    my_object = json_object_new_object();
    json_object_object_add(my_object, "vartype", json_object_new_string("status"));
    json_object_object_add(my_object, "varid", json_object_new_string("loginstatus"));
    //json_object_object_add(my_object, "varvalue", json_object_new_string("1"));
    //json_object_object_add(my_object, "varvalue", json_object_new_string("2"));

    my_array = json_object_new_array();
    json_object_array_add(my_array, json_object_new_int(1));
    json_object_array_add(my_array, json_object_new_int(2));
    json_object_array_add(my_array, json_object_new_int(3));
    printf("my_array len2 =%d\n", json_object_array_length(my_array));
    //json_object_array_add(file_obj, my_array);

    json_object_object_add(my_object, "varvalue", my_array);

    
    printf("my_object.to_string()=%s\n", json_object_to_json_string(my_object));
    //json_object_array_add(file_obj, my_object);
    

    int my_array_len;
    my_array_len = json_object_array_length(file_obj);
    printf("my_array len =%d\n",my_array_len);
    json_object_array_put_idx(file_obj, 2, my_object);


#if 0
    /* get my_object = Array[i]*/
    my_object = json_object_array_get_idx(file_obj,3);
    printf("my_object = %s\n",json_object_to_json_string(my_object));
  
    struct json_object *o = json_object_object_get(my_object,"varid");
    enum json_type o_type = json_object_get_type(o);
    printf("json_object_get_type()=%s\n",json_type_to_name(o_type));
    printf("json_object_get_string()=%s\n",json_object_get_string(o));
    o = json_object_object_get(my_object,"varvalue");
    o_type = json_object_get_type(o);
    printf("json_object_get_type()=%s\n",json_type_to_name(o_type));
    printf("json_object_get_string()=%s\n",json_object_get_string(o));
    printf("json_object_get_int()=%d\n",json_object_get_int(o));
    json_object_object_add(my_object,"jessie",json_object_new_string("hello"));
//    json_object_object_del(my_object,"jessie");

 
    /* get Array Len, add Obj to Array[i] */
    int my_array_len;
    my_array_len = json_object_array_length(file_obj);
    printf("my_array len =%d\n",my_array_len);
    json_object_array_put_idx(file_obj, my_array_len, json_object_new_string("hi jessie"));


#if 0
    struct array_list *my_array_list;
    my_array_list = json_object_get_array(file_obj);
    printf("array_obj = %s\n", json_object_array_to_json_string());
#endif 

#endif
    const char *file_json = json_object_get_string(file_obj);
//    printf("file_json: %s\n", file_json);
    int ret =json_object_to_file("aaa.json", file_obj);
    printf("ret=%d\n",ret);


	json_object_put(file_obj);
	return retval;
}

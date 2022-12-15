/**
 * @file   
 * @author 
 * @date   2010-08-30
 * @brief  
 *
 * Copyright - 2009 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
#ifndef __LIST_H__
#define __LIST_H__
char* del_list(char *list,char token,int n);
char* ins_list(char *list,char *word,char token,int n);
char* get_list_entry(char *list,char token,int n);
char* move_list_entry(char *list,char token,int from,int dest);
int get_entry_num(char * str,char token);

#endif

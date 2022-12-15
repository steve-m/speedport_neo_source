/** 
* @file   cli_vty.h. 
* @module SERCOMM CLI
* @author Miracle Wang
* @version V1.00 
*
* 
* @copyright 2011 SerComm Corporation. All Rights Reserved. */

#ifndef _CLI_VTY_H
#define _CLI_VTY_H

void cli_vty_create(void);
void cli_vty_set_perm(int);

void cli_vty_set(void);
void cli_vty_prompt (void);
void cli_vty_next_line(void);
void cli_vty_previous_line(void);
void cli_vty_backward_char(void);
void cli_vty_forward_char(void);
void cli_vty_backspace_char(void);
void cli_vty_delete_char (void);
void cli_vty_self_insert (char);

void cli_vty_init_command(void);
void cli_vty_execute_command(void);
void cli_vty_complete_command(void);
void cli_vty_describe_command(void);

#endif

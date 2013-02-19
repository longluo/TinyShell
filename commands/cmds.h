/************************************************************************************
** File: - Z:\code\c\tSH\cmd_ls.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_ls.h - Implement the "ls" command
** 
** Version: 1.0
** Date created: 10:14:53,14/11/2012
** Author: long.luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __CMD_LS_H__
#define __CMD_LS_H__


//
int do_ls(char * dir, char * filename, int lflag);
int ls_prepare(char * w, int aflag, int lflag);


#endif // __CMD_LS_H__


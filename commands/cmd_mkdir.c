/************************************************************************************
** File: - Z:\code\c\tSH\cmd_mkdir.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_mkdir.c
** 
** Version: 1.1
** Date created: 22:54:01,15/01/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "cmds.h"

//
//
//
int Cmd_mkdir(int argc, char *argv[])
{ 
    int rt; 

    if ((rt = mkdir(argv[1],10705)) == -1)
    { 
        fprintf(stderr, "Cann't mkdir"); 
    }

    return 0; 
} 


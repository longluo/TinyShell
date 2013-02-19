/************************************************************************************
** File: - Z:\code\c\tSH\cmd_rm.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_rm.c
** 
** Version: 1.1
** Date created: 22:53:41,15/01/2013
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
int Cmd_rm(int argc, char *argv[])
{
    int rt; 
    
    if(argc != 2)
    { 
        exit(2);   
    }
    else
    { 
        if((rt = unlink(argv[1])) !=  0)
        { 
            fprintf(stderr,"error."); 
            exit(3); 
        } 
    } 

    return 0; 
} 


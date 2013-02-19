/************************************************************************************
** File: - Z:\code\c\tSH\cmd_exit.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_quit.c
** 
** Version: 1.0
** Date created: 22:48:36,15/01/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "cmds.h"


//
// This function implements the "quit" command.  It will quit the CMD UI Shell.
//
int Cmd_quit(int argc, char *argv[])
{
    exit(0);
}


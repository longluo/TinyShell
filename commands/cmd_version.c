/************************************************************************************
** File: - Z:\code\c\tSH\cmd_version.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_version.c
** 
** Version: 1.0
** Date created: 22:41:30,15/01/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include ""

//
// This function implements the "v" command. It prints the version of this program. 
//
int Cmd_version(int argc, char *argv[])
{
	printf("Program Version: %f\n", PROG_VERSION);
	printf("Created By long.luo, 13/11/2012.");
	
	return(0);
}


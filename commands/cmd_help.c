/************************************************************************************
** File: - Z:\code\c\tSH\cmd_help.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_help.c
** 
** Version: 1.0
** Date created: 22:49:59,15/01/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "cmds.h"


//
// This function implements the "help" command.  It prints a simple list
// of the available commands with a brief description.
//
int Cmd_help(int argc, char *argv[])
{
    tCmdLineEntry *pEntry;

    // Print some header text.
    printf("\nAvailable commands\n");
    printf("------------------\n");

    // Point at the beginning of the command table.
    pEntry = &g_sCmdTable[0];	
	
    // Enter a loop to read each entry from the command table.  The
    // end of the table has been reached when the command name is NULL.
    while(pEntry->pcCmd) {
        // Print the command name and the brief description.
        printf("%s%s\n", pEntry->pcCmd, pEntry->pcHelp);

        // Advance to the next entry in the table.
        pEntry++;
    }

    // Return success.
    return(0);
}


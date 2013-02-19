/************************************************************************************
** File: - Z:\work\code\c\longluo\cmdline.c
** VENDOR_EDIT
** Copyright (C), 2008-2012, OPPO Mobile Comm Corp., Ltd
** 
** Description: 
**      cmdline.c - Functions to help with processing command lines.
** 
** Version: 1.0
** Date created: 09:47:02,14/11/2012
** Author: long.luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include <string.h>
#include "cmdline.h"


//*****************************************************************************
//
// Defines the maximum number of arguments that can be parsed.
//
//*****************************************************************************
#ifndef CMDLINE_MAX_ARGS
#define CMDLINE_MAX_ARGS        8
#endif

//*****************************************************************************
//
//! Process a command line string into arguments and execute the command.
//!
//! \param pcCmdLine points to a string that contains a command line that was
//! obtained by an application by some means.
//!
//! This function will take the supplied command line string and break it up
//! into individual arguments.  The first argument is treated as a command and
//! is searched for in the command table.  If the command is found, then the
//! command function is called and all of the command line arguments are passed
//! in the normal argc, argv form.
//!
//! The command table is contained in an array named <tt>g_sCmdTable</tt> which
//! must be provided by the application.
//!
//! \return Returns \b CMDLINE_BAD_CMD if the command is not found,
//! \b CMDLINE_TOO_MANY_ARGS if there are more arguments than can be parsed.
//! Otherwise it returns the code that was returned by the command function.
//
//*****************************************************************************
int CmdLineProcess(char *pcCmdLine)
{
    static char *argv[CMDLINE_MAX_ARGS + 1];
    char *pcChar;
    int argc;
    int bFindArg = 1;
    tCmdLineEntry *pCmdEntry;

    //
    // Initialize the argument counter, and point to the beginning of the
    // command line string.
    //
    argc = 0;
    pcChar = pcCmdLine;

	
	//printf("CmdLineProcess: %s\n", pcCmdLine);
	
    //
    // Advance through the command line until a zero character is found.
    //
    while (*pcChar)
    {
        //
        // If there is a space, then replace it with a zero, and set the flag
        // to search for the next argument.
        //
        if(*pcChar == ' ')
        {
            *pcChar = 0;
            bFindArg = 1;
        }

        //
        // Otherwise it is not a space, so it must be a character that is part
        // of an argument.
        //
        else
        {
            //
            // If bFindArg is set, then that means we are looking for the start
            // of the next argument.
            //
            if(bFindArg)
            {
                //
                // As long as the maximum number of arguments has not been
                // reached, then save the pointer to the start of this new arg
                // in the argv array, and increment the count of args, argc.
                //
                if(argc < CMDLINE_MAX_ARGS)
                {
					//printf("\nargc=%d, argv=%s ", argc, argv);
					//printf("   pcChar=%c ", *pcChar);
					
                    argv[argc] = pcChar;
					
					//printf("\nargc=%d, argv=%s ", argc, argv);
					
                    argc++;
                    bFindArg = 0;
                }

                //
                // The maximum number of arguments has been reached so return
                // the error.
                //
                else
                {
                    return(CMDLINE_TOO_MANY_ARGS);
                }
            }
        }

        //
        // Advance to the next character in the command line.
        //
        pcChar++;
    }

	
	//printf("argc=%d, argv=%s ", argc, argv);
	
    //
    // If one or more arguments was found, then process the command.
    //
    if(argc)
    {
        //
        // Start at the beginning of the command table, to look for a matching
        // command.
        //
        pCmdEntry = &g_sCmdTable[0];
		
		//printf("pCmdEntry->pcCmd=%s \n", pCmdEntry->pcCmd);

        //
        // Search through the command table until a null command string is
        // found, which marks the end of the table.
        //
        while(pCmdEntry->pcCmd)
        {
			//printf("while: pCmdEntry->pcCmd=%s, argv[0]=%s \n", pCmdEntry->pcCmd, argv[0]);
			//printf("while: pCmdEntry->pfnCmd=0x%x \n", pCmdEntry->pfnCmd);		
		
            //
            // If this command entry command string matches argv[0], then call
            // the function for this command, passing the command line
            // arguments.
            //
            if(!strcmp(argv[0], pCmdEntry->pcCmd))
            {
				//printf("Define: pCmdEntry->pcCmd=%s, argv[0]=%s \n", pCmdEntry->pcCmd, argv[0]);
				//printf("***pCmdEntry->pfnCmd=0x%x \n", pCmdEntry->pfnCmd);
				
                return(pCmdEntry->pfnCmd(argc, argv));
            }

            //
            // Not found, so advance to the next entry.
            //
            pCmdEntry++;
        }
    }

    //
    // Fall through to here means that no matching command was found, so return
    // an error.
    //
    return(CMDLINE_BAD_CMD);
}

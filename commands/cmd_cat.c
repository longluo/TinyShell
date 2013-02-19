/************************************************************************************
** File: - cmd_cat.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_cat.c
** 
** Version: 1.1
** Date created: 22:52:04,15/01/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "cmds.h"

//
// This function implements the "cat" command.  It reads the contents of
// a file and prints it to the console.  This should only be used on
// text files.  If it is used on a binary file, then a bunch of garbage
// is likely to printed on the console.
//
int Cmd_cat(int argc, char *argv[])
{
    FILE *fp = NULL;
    unsigned short usBytesRead;
    int fr;

    //
    // First, check to make sure that the current path (CWD), plus
    // the file name, plus a separator and trailing null, will all
    // fit in the temporary buffer that will be used to hold the
    // file name.  The file name must be fully specified, with path,
    // to FatFs.
    //
    if(strlen(g_cCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_cTmpBuf))
    {
        printf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_cTmpBuf, g_cCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_cCwdBuf))
    {
        strcat(g_cTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_cTmpBuf, argv[1]);

    //
    // Open the file for reading.
    //
    fp = fopen("g_cTmpBuf", 'a+');
    //fresult = f_open(&g_sFileObject, g_cTmpBuf, FA_READ)

    //
    // If there was some problem opening the file, then return
    // an error.
    //
	/*
    if(fresult != FR_OK)
    {
        return(fresult);
    }
	*/

    //
    // Enter a loop to repeatedly read data from the file and display it,
    // until the end of the file is reached.
    //
    do
    {
        //
        // Read a block of data from the file.  Read as much as can fit
        // in the temporary buffer, including a space for the trailing null.
        //
        //fresult = f_read(&g_sFileObject, g_cTmpBuf, sizeof(g_cTmpBuf) - 1,
        //                &usBytesRead);

        //
        // If there was an error reading, then print a newline and
        // return the error to the user.
        //
		/*
        if(fresult != FR_OK)
        {
            fprintf("\n");
            return(fresult);
        }
		*/

        // Null terminate the last block that was read to make it a
        // null terminated string that can be used with printf.
        g_cTmpBuf[usBytesRead] = 0;

        // Print the last chunk of the file that was received.
        fprintf("%s", g_cTmpBuf);

    // Continue reading until less than the full number of bytes are
    // read.  That means the end of the buffer was reached.
    }
    while(usBytesRead == sizeof(g_cTmpBuf) - 1);

    // Return success.
    return(0);
}


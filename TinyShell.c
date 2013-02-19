/************************************************************************************
** File: - Z:\code\c\tSH\tinySHELL.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      main file
** 
** Version: 1.2
** Date created: 09:41:39,14/11/2012
** Author: long.luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include "cmdline.h"
#include "cmd_ls.h"
#include "cmd_ui_shell.h"


//*****************************************************************************
//
// Defines the size of the buffers that hold the path, or temporary
// data from the SD card.  There are two buffers allocated of this size.
// The buffer size must be large enough to hold the longest expected
// full path name, including the file name, and a trailing null character.
//
//*****************************************************************************
#define PATH_BUF_SIZE   80

//*****************************************************************************
//
// Defines the size of the buffer that holds the command line.
//
//*****************************************************************************
#define CMD_BUF_SIZE    64

//*****************************************************************************
//
// This buffer holds the full path to the current working directory.
// Initially it is root ("/").
//
//*****************************************************************************
static char g_cCwdBuf[PATH_BUF_SIZE] = "/";

//*****************************************************************************
//
// A temporary data buffer used when manipulating file paths, or reading data
// from the SD card.
//
//*****************************************************************************
static char g_cTmpBuf[PATH_BUF_SIZE];

//*****************************************************************************
//
// The buffer that holds the command line.
//
//*****************************************************************************
static char g_cCmdBuf[CMD_BUF_SIZE];



//
// This is the table that holds the command names, implementing functions,
// and brief description.
//
tCmdLineEntry g_sCmdTable[] =
{
    { "help",   Cmd_help,      " : Display list of commands" },
    { "h",      Cmd_help,   "    : alias for help" },
    { "?",      Cmd_help,   "    : alias for help" },
	{ "v", 		Cmd_version, "    : show program version" },
    { "ls",     Cmd_ls,      "   : Display list of files" },
    { "chdir",  Cmd_cd,         ": Change directory" },
    { "cd",     Cmd_cd,      "   : alias for chdir" },
    { "pwd",    Cmd_pwd,      "  : Show current working directory" },
    { "cat",    Cmd_cat,      "  : Show contents of a text file" },
	{ "q",    Cmd_quit,      "    : Quit the program." },
    { 0, 0, 0 }
};





//
// This function implements the "ls" command.  It opens the current
// directory and enumerates through the contents, and prints a line for
// each item it finds.  It shows details such as file attributes, time and
// date, and the file size, along with the name.  It shows a summary of
// file sizes at the end along with free space.
//
int Cmd_ls(int argc, char *argv[])
{
	int aflag =0;
	int lflag =0;
	char c;
	int i;
	
	// 解析命令行参数，即-/--后面的字符串和给定的字符串匹配，
	// 有未解析字母返回字母或问号（取决于第3个参数），否则返回-1
	while((c = getopt(argc, argv, "al")) != -1)	 {
	    // Only support the parameters of 'a' and 'l'.
		switch(c)		
		{
		case 'a':
			aflag =1;
			break;
		case 'l':
			lflag =1;
			break;
		default:
			break;
		}
	}
	
	//optind系统变量，执行命令参数的个数（不包括命令，奇怪的是无参情况下他为1），判断argc是否为1，是则取当前路径，让我们显得更专业点
	if (argc == optind) {
		ls_prepare("./", aflag, lflag);
	} else {
	    //所有目录都传进去 
		for(i = optind; i < argc; i++)		
		    ls_prepare(argv[i],aflag,lflag);
	}
	printf("\n");
	
	return 0;
} 




//
// This function implements the "pwd" command.  It simply prints the
// current working directory.
//
int Cmd_pwd(int argc, char *argv[])
{
    // Print the CWD to the console.
    printf("%s\n", g_cCwdBuf);
	
    // Return success.
    return(0);
}





//
// The main routine.
//
int main(int argc, char *argv[])
{
    int nStatus, nStrLen;
	
	fprintf(stderr, "Hello, CMD UI Program...");
	
    // Enter an infinite loop for reading and processing commands from the user.
    while (1) {
        // Print a prompt to the console. Show the CWD.
        printf("\n%s> ", g_cCwdBuf);

        // Get a line of text from the user.
        fgets(g_cCmdBuf, CMD_BUF_SIZE, stdin);

        // Remove the char '\n'.
		nStrLen = strlen(g_cCmdBuf);
		if ('\n' == g_cCmdBuf[nStrLen - 1]) {
			g_cCmdBuf[nStrLen - 1] = '\0';
		}
			
        // Pass the line from the user to the command processor.
        // It will be parsed and valid commands executed.
        nStatus = CmdLineProcess(g_cCmdBuf);

        // Handle the case of bad command.
        if(nStatus == CMDLINE_BAD_CMD) {
			printf("Bad command!\n");
        }
        // Handle the case of too many arguments.
        else if(nStatus == CMDLINE_TOO_MANY_ARGS) {
			printf("Too many arguments for command processor!\n");
        }
        // Otherwise the command was executed. Print the error
        // code if one was returned.
        else if(nStatus != 0) {
			printf("Command returned error code.\n");
        }
    }
	
	return 0;
}



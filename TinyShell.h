/************************************************************************************
** File: - Z:\code\c\tSH\TinyShell.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      TinyShell.h - Header file of the main
** 
** Version: 1.1
** Date created: 09:40:21,14/11/2012
** Author: long.luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __TINY_SHELL_H__
#define __TINY_SHELL_H__


//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif


//
#define PROG_VERSION	(1.2)


// Prototypes for the APIs.
int Cmd_ls(int argc, char *argv[]);
int Cmd_pwd(int argc, char *argv[]);
int Cmd_cd(int argc, char *argv[]);
int Cmd_cat(int argc, char *argv[]);
int Cmd_help(int argc, char *argv[]);
int Cmd_version(int argc, char *argv[]);
int Cmd_quit(int argc, char *argv[]);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __TINY_SHELL_H__


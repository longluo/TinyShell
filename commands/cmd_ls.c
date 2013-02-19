/************************************************************************************
** File: - Z:\code\c\tSH\cmd_ls.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      cmd_ls.c - The implement of the Linux Like "ls" command.
** 
** Version: 1.0
** Date created: 10:20:56,14/11/2012
** Author: long.luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

int do_ls(char *dir,char *filename,int lflag)
{
	int n;
	struct stat buf;
	char out[100];
	struct passwd *pw;
	struct group *gr;
	struct tm *t;

    //如果不带l参数，直接显示文件/目录名
	if (lflag == 0)		
	{
		printf("%s\t", filename);
		return 0;
	}
		
	if(lstat(dir,&buf)<0)
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}

    //获取字符串的属性：普通文件-、目录d、字符设备c、块设备b、
    //管道文件p、连接文件l、套接字文件s
	switch(buf.st_mode & S_IFMT)		
	{
	case S_IFREG:	
		printf("-");
		break;
	case S_IFDIR:	
		printf("d");
		break;
	case S_IFCHR:	
		printf("c");
		break;
	case S_IFBLK:	
		printf("b");
		break;
	case S_IFIFO:	
		printf("p");
		break;
	case S_IFLNK:	
		printf("l");
		break;
	case S_IFSOCK:	
		printf("s");
		break;
	}

    //打印文件的读写属性：读r、写w、执行x、无权限-
	for(n=8;n>=0;n--)		
	{
		if(buf.st_mode&(1<<n))
		{
			switch(n%3)
			{
			case 2:
				printf("r");
				break;
			case 1:
				printf("w");
				break;
			case 0:
				printf("x");
					break;
			default:
				break;
			}
		}
		else
		{
			printf("-");
		}
	}

	//硬链接数，此链接非彼链接，指（包含）目录的个数，
	//文件为1，目录起始为2，再加上目录里包含的目录个数（不递归，只一层）
	printf(" %d",buf.st_nlink);		
	
	pw = getpwuid(buf.st_uid);		//所属用户名
	printf(" %s",pw->pw_name);		

	gr = getgrgid(buf.st_gid);		//所属组名
	printf(" %s",gr->gr_name);

	printf(" %ld",buf.st_size);		//字节计总大小

	t = localtime(&buf.st_atime);	//最后一次访问时间
	printf(" %d-%d-%d %d:%d"
		,t->tm_year+1900
		,t->tm_mon+1
		,t->tm_mday
		,t->tm_hour
		,t->tm_min);
   	printf(" %s ",filename);	

	//判断是否为链接，是返回真   
	if(S_ISLNK(buf.st_mode))		
	{
		printf(" -> ");
		if(readlink(filename,out,100)==-1)
		{
			//printf("readlink error\n");
		}
		printf("%s",out);
	}
	printf("\n");
	
	return 0;
}


// ls的准备工作
int ls_prepare(char *w,int aflag,int lflag)		
{
	struct stat buf;		//man lstat可以看到此结构
	char name[100];	
	DIR *dir;		//类似打开文件的fd描述符
	struct dirent *pdr;		//man readdir可以看到此结构

    //获取文件/目录属性并赋值给buf，该函数和lstat一样，
    //只是当w为链接时，指代他本身，并不存在文件
	if(lstat(w,&buf)<0)		
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}
	
	if(S_ISDIR(buf.st_mode))	//判断是否为目录，是返回真
	{
		dir = opendir(w);		//打开目录
		while ((pdr = readdir(dir))!=NULL)	//读/遍历目录
		{
			if(aflag==0)	//如果不带a参数，越过以.开头的所有文件/目录
			{ 
				if(pdr->d_name[0]=='.')
					continue;
				memset(name,0,100);		
				strcpy(name,w);			//拷贝
				strcat(name,"/");		//追加
				strcat(name,pdr->d_name);
				do_ls(name,pdr->d_name,lflag);
			}
			//有a参数显示所有
			else		
			{
				memset(name,0,100);
				strcpy(name,w);
				strcat(name,"/");
				strcat(name,pdr->d_name);
				do_ls(name,pdr->d_name,lflag);
			}
		}
		closedir(dir);
	}
	//为文件则直接显示
	else	
	{
		do_ls(w,w,lflag);
	}
	
	return 0;
}



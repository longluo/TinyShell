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

    //�������l������ֱ����ʾ�ļ�/Ŀ¼��
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

    //��ȡ�ַ��������ԣ���ͨ�ļ�-��Ŀ¼d���ַ��豸c�����豸b��
    //�ܵ��ļ�p�������ļ�l���׽����ļ�s
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

    //��ӡ�ļ��Ķ�д���ԣ���r��дw��ִ��x����Ȩ��-
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

	//Ӳ�������������ӷǱ����ӣ�ָ��������Ŀ¼�ĸ�����
	//�ļ�Ϊ1��Ŀ¼��ʼΪ2���ټ���Ŀ¼�������Ŀ¼���������ݹ飬ֻһ�㣩
	printf(" %d",buf.st_nlink);		
	
	pw = getpwuid(buf.st_uid);		//�����û���
	printf(" %s",pw->pw_name);		

	gr = getgrgid(buf.st_gid);		//��������
	printf(" %s",gr->gr_name);

	printf(" %ld",buf.st_size);		//�ֽڼ��ܴ�С

	t = localtime(&buf.st_atime);	//���һ�η���ʱ��
	printf(" %d-%d-%d %d:%d"
		,t->tm_year+1900
		,t->tm_mon+1
		,t->tm_mday
		,t->tm_hour
		,t->tm_min);
   	printf(" %s ",filename);	

	//�ж��Ƿ�Ϊ���ӣ��Ƿ�����   
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


// ls��׼������
int ls_prepare(char *w,int aflag,int lflag)		
{
	struct stat buf;		//man lstat���Կ����˽ṹ
	char name[100];	
	DIR *dir;		//���ƴ��ļ���fd������
	struct dirent *pdr;		//man readdir���Կ����˽ṹ

    //��ȡ�ļ�/Ŀ¼���Բ���ֵ��buf���ú�����lstatһ����
    //ֻ�ǵ�wΪ����ʱ��ָ�����������������ļ�
	if(lstat(w,&buf)<0)		
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}
	
	if(S_ISDIR(buf.st_mode))	//�ж��Ƿ�ΪĿ¼���Ƿ�����
	{
		dir = opendir(w);		//��Ŀ¼
		while ((pdr = readdir(dir))!=NULL)	//��/����Ŀ¼
		{
			if(aflag==0)	//�������a������Խ����.��ͷ�������ļ�/Ŀ¼
			{ 
				if(pdr->d_name[0]=='.')
					continue;
				memset(name,0,100);		
				strcpy(name,w);			//����
				strcat(name,"/");		//׷��
				strcat(name,pdr->d_name);
				do_ls(name,pdr->d_name,lflag);
			}
			//��a������ʾ����
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
	//Ϊ�ļ���ֱ����ʾ
	else	
	{
		do_ls(w,w,lflag);
	}
	
	return 0;
}



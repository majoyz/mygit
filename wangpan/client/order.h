#ifndef __ORDER_H__
#define __ORDER_H__
#include "head.h"
#include "dosql.h"
#include "tran_n.h"
#define OLEN 128

struct order{//命令结构体
	short oid;//命令id，通过判断buf得到
	char buf[OLEN];
};
struct ls_data{//ls命令用结构体
	char mod;
	char name[128];
	long len;
};

short judge_order(char*,struct order*);
int c_gets(int,char*,int);
int c_puts(int,char*);
//int send_n(int,void *,size_t);
//int recv_n(int,void *,size_t);
int getmd(char *,char *);
#endif

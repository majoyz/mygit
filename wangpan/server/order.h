#ifndef __ORDER_H__
#define __ORDER_H__
#include "head.h"
#include "dosql.h"
#define OLEN 128

struct order{//命令结构体
	short oid;//命令id，通过判断buf得到
	char buf[OLEN];
};

int send_n(int,void *,size_t);
int recv_n(int,void *,size_t);
int s_gets(int,char*);
int s_puts(int,char*,char*,off_t*);
int s_cd(int,int*,char*,char*,char*);

#endif

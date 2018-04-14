#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "order.h"
#define FILENAME "file"

typedef void* (*pfunc)(void*);
typedef struct{
	pthread_t *pthid;//线程id存储的起始地址
	pthread_cond_t cond;//线程同步用的条件变量
	que_t que;
	int pthread_num;//线程数目
	int start_flag;//这类线程启动标志
	pfunc thread_func;//线程函数
}fac,*pfac;
typedef struct{
	int len;
	char buf[1000];
}train;

void factory_init(pfac,pfunc,int);
void factory_start(pfac);
int send_n(int,void*,size_t);
int recv_n(int,void*,size_t);
int tran_file(int);
int sock_init(char*,char*,int*,int);

#endif

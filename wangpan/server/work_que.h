#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"

typedef struct tag_node{//队列元素
	int new_fd;
	struct tag_node *pNext;
}node_t,*pnode_t;
typedef struct{
	pnode_t que_head,que_tail;//队首队尾
	int que_capacity;//队列能力
	int que_size;//队列当前大小
	pthread_mutex_t que_mutex;//队列操作锁
}que_t,*pque_t;

void que_init(pque_t,int);
void que_set(pque_t,pnode_t);
void que_get(pque_t,pnode_t*);

#endif

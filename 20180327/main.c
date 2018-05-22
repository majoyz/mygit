#include "factory.h"

void* thread_handle(void *p){
	pfac pf=(pfac)p;
	pque_t pq=&pf->que;
	pnode_t pcur;
	while(1){
		pthread_mutex_lock(&pq->que_mutex);
		//printf("locked,que_size=%d\n",pq->que_size);
		if(!pq->que_size){
			//printf("I'm waiting\n");
			pthread_cond_wait(&pf->cond,&pq->que_mutex);
		}
		que_get(pq,&pcur);
		pthread_mutex_unlock(&pq->que_mutex);
		//printf("I'll send fill to %d\n",pcur->new_fd);
		tran_file(pcur->new_fd);
		free(pcur);
		//sleep(3);
		//printf("child bye\n");
	}
}

int main(int argc,char *argv[]){
	if(argc!=5){
		printf("./server IP PORT THREAD_NUM CAPACITY\n");
		return -1;
	}
	fac f;
	bzero(&f,sizeof(fac));
	f.pthread_num=atoi(argv[3]);
	int capacity=atoi(argv[4]);
	factory_init(&f,thread_handle,capacity);
	int sfd;
	int ret=sock_init(argv[1],argv[2],&sfd,100);
	//尝试封装socket的一系列函数
	if(ret==-1){
		printf("error sock_init\n");
		return -1;
	}
	factory_start(&f);//申请所有子线程
	
	int new_fd;
	pnode_t pnew;
	pque_t pq=&f.que;//
	while(1){
		printf("I'm waiting customers\n");
		new_fd=accept(sfd,NULL,NULL);
		printf("I got a %d\n",new_fd);
		pnew=(pnode_t)calloc(1,sizeof(node_t));
		pnew->new_fd=new_fd;
		pthread_mutex_lock(&pq->que_mutex);
		que_set(pq,pnew);
		pthread_mutex_unlock(&pq->que_mutex);
		pthread_cond_signal(&f.cond);
	}
}

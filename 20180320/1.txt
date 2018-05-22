#include "func.h"

struct data{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

void *threadfunc(void *p){
	struct data *x=(struct data *)p;
	printf("I'll wait\n");
	pthread_mutex_lock(&x->mutex);
	long ret=pthread_cond_wait(&x->cond,&x->mutex);
	pthread_mutex_unlock(&x->mutex);
	printf("I have waked\n");
	pthread_exit((void *)ret);
}

int main(){
	struct data user;
	pthread_t pthid;
	long get;
	pthread_mutex_init(&user.mutex,NULL);
	pthread_cond_init(&user.cond,NULL);
	pthread_create(&pthid,NULL,threadfunc,&user);
	sleep(1);
	printf("I'll wake up child\n");
	pthread_cond_signal(&user.cond);
	pthread_join(pthid,(void **)&get);
	printf("I get %ld from child\n",(long)get);
	return 0;
}

#include "func.h"
#define N 20000000

pthread_mutex_t mutex;

void* threadfunc(void *p){
	long *l=(long *)p;
	int i;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&mutex);
		*l+=1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main(){
	long l=0;
	pthread_t pthid;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&pthid,NULL,threadfunc,(void *)&l);
	int i;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&mutex);
		l+=1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_join(pthid,NULL);
	printf("%ld\n",l);
	pthread_mutex_destroy(&mutex);
	return 0;
}

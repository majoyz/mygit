#include "func.h"

pthread_mutex_t lock;

void *pthfunc(void *args){
	pthread_mutex_lock(&lock);
	pthread_mutex_trylock(&lock);
	printf("hello\n");
	sleep(1);
	pthread_exit(NULL);
}

int main(){
	pthread_t pthid=0;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&pthid,NULL,pthfunc,NULL);
	pthread_join(pthid,NULL);
	pthread_mutex_destroy(&lock);
}

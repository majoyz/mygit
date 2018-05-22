#include "func.h"

void threadclean(void *p){
	printf("I'm cleaner\n");
	free(p);
	return;
}

void* threadfunc(){
	char *a=(char *)malloc(32);
	pthread_cleanup_push(threadclean,a);
	char buf[128];
	read(0,buf,sizeof(buf));
    pthread_exit((void*)5);
	pthread_cleanup_pop(0);
}

int main(){
	int x;
	pthread_t pthid;
	pthread_create(&pthid,NULL,threadfunc,NULL);
	pthread_cancel(pthid);
	pthread_join(pthid,(void**)&x);
	printf("join's get=%d\n",x);
	return 0;
}

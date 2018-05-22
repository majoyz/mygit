#include "func.h"

void *threadfunc(void *p){
	printf("child\n");
	int i=7;
	pthread_exit((void *)7);
}

int main(){
	pthread_t pthid;
	int ret=pthread_create(&pthid,NULL,threadfunc,NULL);
	printf("main\n");
//	sleep(0);
	int i;
	pthread_join(pthid,(void**)&i);
	printf("get=%d\n",i);
	return 0;
}

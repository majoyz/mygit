#include "func.h"

void* threadfunc(void *p){
	printf("%ld\n",(long)p);
	pthread_exit((void *)2);
}

int main(){
	long p;
	pthread_t pthid;
	pthread_create(&pthid,NULL,threadfunc,(void *)1);
	pthread_join(pthid,(void**)&p);
	printf("%ld\n",p);
	return 0;
}

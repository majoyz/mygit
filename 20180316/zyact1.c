#include "func.h"

//typedef struct sigaction{

void sigfunc(int sig,siginfo_t *p,void *p1){
	printf("before sleep %d is coming!\n",sig);
	sleep(3);
	printf("after sleep %d is coming!\n",sig);
}

int main(){
	struct sigaction try;
	memset(&try,0,sizeof(try));
	try.sa_sigaction=sigfunc;
	try.sa_flags=SA_SIGINFO|SA_NODEFER;
	sigaction(SIGINT,&try,NULL);
	while(1);
	return 0;
}

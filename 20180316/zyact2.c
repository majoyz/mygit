#include "func.h"

//typedef struct sigaction{

void sigfunc(int sig,siginfo_t *p,void *p1){
	printf("before sleep %d is coming!\n",sig);
	sleep(3);
	sigset_t set;
	sigpending(&set);
	if(sigismember(&set,SIGQUIT))
		printf("sigquit has been hang\n");
	else
		printf("sigquit has not been hang\n");
	printf("after sleep %d is coming!\n",sig);
}

int main(){
	struct sigaction try;
	memset(&try,0,sizeof(try));
	try.sa_sigaction=sigfunc;
	try.sa_flags=SA_SIGINFO;
	sigemptyset(&try.sa_mask);
	sigaddset(&try.sa_mask,SIGQUIT);
	sigaction(SIGINT,&try,NULL);
	sigaction(SIGQUIT,&try,NULL);
	while(1);
	return 0;
}

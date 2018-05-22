#include "func.h"

void sigfunc(int sig){
	printf("sig %d is coming\n",sig);
}

int main(){
	sigset_t set,set2;
	sigemptyset(&set);
	sigemptyset(&set2);
	//signal(SIGINT,sigfunc);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,NULL);//block
	sleep(5);
	sigpending(&set2);
	if(sigismember(&set2,SIGINT))
		printf("sigint has been hang\n");
	else
		printf("sigint has not been hang\n");
	sigprocmask(SIG_UNBLOCK,&set,NULL);//unblock
	return 0;
}

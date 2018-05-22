#include "func.h"
void sigfunc(int sig){
	printf("before sleep %d sig is coming!\n",sig);
	sleep(3);
	printf("after sleep %d sig is coming!\n",sig);
};

int main(){
	signal(SIGINT,&sigfunc);
	signal(SIGQUIT,&sigfunc);
	while(1);
	return 0;
}

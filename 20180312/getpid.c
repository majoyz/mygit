#include "func.h"

int main(){
	pid_t mypid,myppid;
	mypid=getpid();
	myppid=getppid();
	printf("pid=%d,ppid=%d\n",mypid,myppid);
	while(1);
	return 0;
}

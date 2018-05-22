#include "func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("I'm child,pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(1);
	}
	else{
		int childpid;
		printf("I'm father,pid=%d\n",getpid());
		int status;
		childpid=wait(&status);
		printf("childpid=%d\n",childpid);
	}
	return 0;
}


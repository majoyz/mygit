#include "func.h"

int main(){
	pid_t pid;
	pid=fork();
	if(0==pid){
		printf("I'm zijincheng\n");
	}else{
		printf("I'm fujincheng\n");
		int status;
		wait(&status);
		if(WIFEXITED(status)){
			printf("zijinchengfanhui=%d\n",WEXITSTATUS(status));
		}
		//while(1);
	}
	printf("why?\n");
	return 0;
}

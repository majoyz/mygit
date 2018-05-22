#include "func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("I'm child\n");
	}
	else{
		printf("I'm father\n");
		while(1);
	}
	return 0;
}

#include "func.h"

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("I'm child\n");
		while(1);
	}
	else{
		printf("I'm father\n");
	}
	return 0;
}

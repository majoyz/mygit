#include "func.h"

int main(){
	int fds[2];
	pipe(fds);
	if(!fork()){
		printf("I'm child,I'll write\n");
		close(fds[0]);
		char buf[128]="Hello";
		write(fds[1],buf,strlen(buf));
	}else{
		printf("I'm father,I'll read\n");
		close(fds[1]);
		char buf[128];
		wait(NULL);
		read(fds[0],buf,sizeof(buf));
		printf("%s\n",buf);
	}
	return 0;
}

#include "func.h"

int main(){
	pid_t pid=fork();
	if(pid){
		//printf("I'm father.I'll out\n");
		exit(0);
	}
	//printf("I'm child,sid=%d\n",getsid(0));
	int sid=setsid();
	//printf("My new sid=%d\n",sid);
	chdir("/");
	umask(0);
	for(int i=0;i<3;i++){
		close(i);
	}

	int fd=open("/tmp/log",O_RDWR|O_CREAT|O_TRUNC,0777);
	int pgid;
	char buf[64];
	while(1){
		pgid=getpgid(0);
		sprintf(buf,"%d\n",pgid);
		write(fd,buf,strlen(buf));
		sleep(5);
	}
	return 0;
}

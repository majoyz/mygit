#include "func.h"

int main(){
	int fd=open("file.txt",O_RDWR);
	if(-1==fd){
		perror("open");
		return -1;
	}
	char buf[64]="can you write?";
	printf("uid=%d,gid=%d,euid=%d,rgid=%d\n",getuid(),getgid(),geteuid(),getegid());
	write(fd,buf,strlen(buf));
	close(fd);
	return 0;
}

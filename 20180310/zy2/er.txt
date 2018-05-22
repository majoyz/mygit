#include "func.h"

int main(){
	int fd;
	fd=open("text.txt",O_CREAT|O_TRUNC|O_RDWR,0755);
	char buf[6]="hello";
	write(fd,buf,6);
	if(-1==fd){
		perror("open");
		return -1;
	}
	char *p=(char *)mmap(0,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	strcpy(p,"world");
	munmap(p,10);
	return 0;
}

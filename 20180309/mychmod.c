#include <stdio.h>
#include <sys/stat.h>

int main(int argc,char* argv[]){
	if (argc!=2){
		printf("chmod error\n");
		return -1;
	}
	int ret=chmod(argv[1],0666);
	if(-1==ret){
		perror("chmod");
		return -1;
	}
	return 0;
}

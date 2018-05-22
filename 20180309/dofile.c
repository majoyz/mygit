#include <stdio.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("argc error\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"ab+");
	if(NULL==fp){
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fread(buf,sizeof(char),4,fp);
	puts(buf);
	return 0;
}

#include "head.h"

int getmd(char *filename,char *mdname){
	MD5_CTX ctx;
	int len=0;
	int fd;
	char buf[1024]={0};
	unsigned char mdfilename[32]={0};
	//char mdname[64]={0};
	char tmpmd[4]={0};
	//char filename[5]="main";
	fd=open(filename,O_RDONLY);
	if(fd==-1){
		perror("open");
		return -1;
	}
	
	MD5_Init(&ctx);
	while((len=read(fd,buf,sizeof(buf)))){
		MD5_Update(&ctx,buf,len);
		bzero(buf,sizeof(buf));
	}
	MD5_Final(mdfilename,&ctx);
	//printf("已获得MD5码：\n");
	//puts(mdfilename);
	for(int i=0;i<16;i++){
		sprintf(tmpmd,"%02x",mdfilename[i]);
		rewind(stdout);
		strcat(mdname,tmpmd);
	}
	//printf("\n");
	//puts(mdname);
	//long int lx=strtol(mdfilename,NULL,16);
	//printf("%ld\n",lx);
	return 0;
}

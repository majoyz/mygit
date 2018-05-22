#include "func.h"

int main(int argc,char *argv[]){
	if(argc!=3){
		printf("error argc\n");
		return 0;
	}
	int fdr=open(argv[1],O_RDONLY);
	if(fdr==-1){
		perror("open1");
		return 0;
	}
	int fdw=open(argv[2],O_WRONLY);
	if(fdw==-1){
		perror("open2");
		return 0;
	}
	printf("I am chat_b\n");

	fd_set readfds;
	int gs;
	char buf[128]={0};
	while(1){
		FD_ZERO(&readfds);
		FD_SET(0,&readfds);
		FD_SET(fdr,&readfds);
		gs=select(fdr+1,&readfds,NULL,NULL,NULL);
		if(gs>0){
			if(FD_ISSET(fdr,&readfds)){
				bzero(buf,sizeof(buf));
				int ret1=read(fdr,buf,sizeof(buf));
				if(-1==ret1){
					perror("read");
					return 0;
				}
				else if(0==ret1){
					printf("byebye\n");
					break;
				}
				printf("%s\n",buf);
			}

			if(FD_ISSET(0,&readfds)){
				bzero(buf,sizeof(buf));
				int ret2=read(0,buf,sizeof(buf)-1);
				if(0==ret2){
					printf("write over\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}

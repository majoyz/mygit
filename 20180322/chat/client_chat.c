#include "func.h"

int main(int argc,char *argv[]){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("connect");
		return -1;
	}
	printf("客户端就绪\n");

	char buf[128];
	fd_set readfds;
	while(1){
		FD_ZERO(&readfds);
		FD_SET(sfd,&readfds);
		FD_SET(0,&readfds);
		ret=select(sfd+1,&readfds,NULL,NULL,NULL);
		if(ret>0){
			if(FD_ISSET(sfd,&readfds)){
				bzero(buf,sizeof(buf));
				ret=recv(sfd,buf,sizeof(buf),0);
				if(ret==0){
					printf("server over\n");
					close(sfd);
					break;
				}
				puts(buf);
			}else if(FD_ISSET(0,&readfds)){
				bzero(buf,sizeof(buf));
				ret=read(0,buf,sizeof(buf)-1);
				if(ret>0){
					send(sfd,buf,strlen(buf)-1,0);
				}else{
					printf("read's ret=%d\nclient down\n",ret);
					close(sfd);
					return 0;
				}
			}
		}
	}
	return 0;
}

#include "func.h"

int main(int argc,char *argv[]){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("bind");
		return -1;
	}
	listen(sfd,5);
	struct sockaddr_in cli;
	int sz=sizeof(cli);
	while(1){
		bzero(&cli,sizeof(cli));
		int new_fd=accept(sfd,(struct sockaddr*)&cli,&sz);
		if(new_fd==-1){
			perror("accept");
			return -1;
		}
		printf("服务器就绪\n");
		printf("ip=%s,port=%d,sfd=%d,new_fd=%d\n",inet_ntoa(ser.sin_addr),ntohs(ser.sin_port),sfd,new_fd);
		printf("client port=%d\n",ntohs(cli.sin_port));

		fd_set readfds;
		char buf[128];
		while(1){
			FD_ZERO(&readfds);
			FD_SET(new_fd,&readfds);
			FD_SET(0,&readfds);

			ret=select(new_fd+1,&readfds,NULL,NULL,NULL);
			if(ret>0){
				if(FD_ISSET(new_fd,&readfds)){
					bzero(&buf,sizeof(buf));
					ret=recv(new_fd,buf,sizeof(buf),0);
					if(ret==0){
						printf("chatdown\n");
						close(new_fd);
//						close(sfd);
						break;
					}
					puts(buf);
				}else if(FD_ISSET(0,&readfds)){
					bzero(&buf,sizeof(buf));
					ret=read(0,buf,sizeof(buf)-1);
					if(ret>0){
						send(new_fd,buf,strlen(buf)-1,0);
					}else{
						printf("serverdown\n");
						close(new_fd);
						close(sfd);
						return 0;
					}
				}
			}
		}
	}
//	close(sfd);
	return 0;
}

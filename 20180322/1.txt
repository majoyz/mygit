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
	int new_fd=accept(sfd,(struct sockaddr*)&cli,&sz);
	if(new_fd==-1){
		perror("accept");
		return -1;
	}
	printf("服务器就绪\n");
	printf("ip=%s,port=%d,sfd=%d,new_fd=%d\n",inet_ntoa(ser.sin_addr),ntohs(ser.sin_port),sfd,new_fd);
	printf("client port=%d\n",ntohs(cli.sin_port));
	char buf[128];
	recv(new_fd,&buf,sizeof(buf),0);
	printf("I get \"%s\"\n",buf);
	send(new_fd,"hello,I'm server",16,0);
	close(new_fd);
	close(sfd);
	return 0;
}

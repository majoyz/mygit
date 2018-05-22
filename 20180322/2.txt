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
	send(sfd,"hello,I'm client",16,0);
	char buf[128];
	recv(sfd,&buf,sizeof(buf),0);
	printf("I get \"%s\"\n",buf);
	close(sfd);
	return 0;
}

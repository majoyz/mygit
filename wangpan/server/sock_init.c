#include "head.h"

int sock_init(char *ip,char *port,int *sfd1,int backlog){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}
	int ret;
	int reuse=1;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	if(-1==ret){
		perror("setsockopt");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(ip);
	ser.sin_port=htons(atoi(port));
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("bind");
		return -1;
	}
	listen(sfd,backlog);
	*sfd1=sfd;
	return 0;
}

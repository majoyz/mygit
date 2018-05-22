#include "func.h"

int main(int argc,char *argv[]){
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	//bind(sfd,(struct sockaddr*)&ser,sizeof(ser));

	//struct sockaddr_in cli;
	char buf[128]={0};
	int fl=sizeof(ser);
	sendto(sfd,"hello,I'm client",16,0,(struct sockaddr*)&ser,sizeof(ser));
	recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&ser,&fl);
	puts(buf);
	close(sfd);
	return 0;
}

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

	int len;
	char buf[1000]={0};
	recv_n(sfd,&len,4);
	recv_n(sfd,buf,len);
	int ffd=open(buf,O_RDWR|O_CREAT,0666);
	while(1){
		recv_n(sfd,&len,4);
		if(len>0){
			recv_n(sfd,buf,len);
			write(ffd,buf,len);
		}else{
			break;
		}
	}
	close(ffd);
	close(sfd);
	return 0;
}

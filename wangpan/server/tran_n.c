#include "factory.h"

int send_n(int fd,void *buf,size_t len){
	int total=0;
	int ret;
	while(total<len){
		ret=send(fd,buf+total,len-total,0);
		if(ret==-1){
			printf("send发送失败\n");
			sleep(1);
			return -1;
		}
		total+=ret;
	}
	return total;
}

int recv_n(int fd,void *buf,size_t len){
	int total=0;
	int ret;
	while(total<len){
		ret=recv(fd,buf+total,len-total,0);
		if(ret==0){
			return 0;
		}
		total+=ret;
	}
	return total;
}

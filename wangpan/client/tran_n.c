#include "order.h"

int send_n(int fd,void *buf,size_t len){
	int total=0;
	int ret;
	while(total<len){
		ret=send(fd,buf+total,len-total,0);
		if(ret==-1){
			printf("send发送失败\n");
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
			break;
		}
		total+=ret;
	}
	return total;
}

#include "func.h"

int send_n(int fd,void *buf,size_t len){
	int total=0;
	int ret;
	while(total<len){
		ret=send(fd,buf+total,len-total,0);
		total+=ret;
	}
	return 0;
}

int recv_n(int fd,void *buf,size_t len){
	int total=0;
	int ret;
	while(total<len){
		ret=recv(fd,buf+total,len-total,0);
		total+=ret;
	}
	return 0;
}

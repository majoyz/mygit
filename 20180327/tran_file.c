#include "factory.h"
#define FILENAME "file"

int tran_file(int new_fd){
	train d;
	strcpy(d.buf,FILENAME);
	d.len=strlen(d.buf);
	send_n(new_fd,&d,4+d.len);


	int fd=open(FILENAME,O_RDONLY);

	struct stat buf;
	fstat(fd,&buf);
	d.len=sizeof(off_t);
	memcpy(d.buf,&buf.st_size,d.len);
	send_n(new_fd,&d,4+d.len);

	while(d.len=read(fd,d.buf,sizeof(d.buf))){
		int ret=send_n(new_fd,&d,4+d.len);
		if(ret==-1){
			printf("send_n发送失败\n");
			close(new_fd);
			close(fd);
			return -1;
		}
	}
	send_n(new_fd,&d,4);
	close(new_fd);
	close(fd);
}

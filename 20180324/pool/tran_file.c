#include "func.h"
#define FILENAME "file"

void tran_file(int new_fd){
	train d;
	strcpy(d.buf,FILENAME);
	d.len=strlen(d.buf);
	send_n(new_fd,&d,4+d.len);
	int fd=open(FILENAME,O_RDONLY);
	while(d.len=read(fd,d.buf,sizeof(d.buf))){
		send_n(new_fd,&d,4+d.len);
	}
	send_n(new_fd,&d,4);
	close(new_fd);
	close(fd);
}

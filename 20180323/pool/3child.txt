#include "func.h"

void make_child(pData p,int num){
	int i;
	int ret;
	int fds[2];
	for(i=0;i<num;i++){
		ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		int pid=fork();
		if(!pid){
			close(fds[0]);
			child_handle(fds[1]);//管道给父进程通信
		}
		close(fds[1]);
		p[i].pid=pid;
		p[i].fd=fds[0];//管道给父进程通信
		printf("p[%d].pid=%d,fds[0]=%d\n",i,pid,fds[0]);
	}
}

void child_handle(int fd){
	int sfd;
	int unbusy=0;
	while(1){
		recv_fd(fd,&sfd);
		for(int i=0;i<10;i++){
			printf("I'll send OK to %d\n",sfd);
			sleep(5);
			send(sfd,"OK",2,0);
		}
		write(fd,&unbusy,sizeof(int));
	}
}


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
	short flag;
	int unbusy=0;
	while(1){
		recv_fd(fd,&sfd,&flag);
		if(flag==0){
			printf("I'll send file to %d\n",sfd);
			int ret=tran_file(sfd);
			if(ret==-1){
				printf("client over\n");
				sleep(1);
				//return;
			}
			write(fd,&unbusy,sizeof(int));
		}else if(flag==1){
			exit(0);
		}
	}
}


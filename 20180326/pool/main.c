#include "func.h"

int fds[2];

void sigfunc(int sig){
	//int fds[2];
	char useless='x';
	write(fds[1],(void*)&useless,1);
}

void epoll_add(int epfd,int fd){
	struct epoll_event event;
	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=fd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
	if(ret==-1){
		perror("epoll_ctl");
		return;
	}
}

void epoll_del(int epfd,int fd){
	struct epoll_event event;
	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=fd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event);
	if(ret==-1){
		perror("epoll_ctl");
		return;
	}
}

int main(int argc,char *argv[]){
	if(argc!=4){
		printf("error argc\n");
		return -1;
	}
	pipe(fds);
	signal(SIGUSR1,sigfunc);//用一号用户信号有序退出
	int num=atoi(argv[3]);
	pData p=(pData)calloc(num,sizeof(Data));
	make_child(p,num);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	int ret;
	int reuse=1;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	if(ret==-1){
		perror("sersockopt");
		return -1;
	}
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("bind");
		return -1;
	}

	//ret=lisen(sfd,10);
	int i;
	int j;

	int epfd=epoll_create(1);
	epoll_add(epfd,sfd);
	for(i=0;i<num;i++){
		epoll_add(epfd,p[i].fd);
	}
	epoll_add(epfd,fds[0]);
	listen(sfd,10);

	struct epoll_event *evs=(struct epoll_event *)calloc(num+2,sizeof(struct epoll_event));
	int new_fd;
	int flag;
	while(1){
		bzero(evs,sizeof(struct epoll_event)*(num+1));
		epoll_wait(epfd,evs,num+1,-1);
		for(i=0;i<num;i++){
			if(sfd==evs[i].data.fd){
				new_fd=accept(sfd,NULL,NULL);
				printf("I get a castomer\n");
				for(j=0;j<num;j++){
					if(p[j].busy==0)
						break;
				}
				if(j==num){
					printf("but I'm too busy\n");
					close(new_fd);
					break;
				}
				send_fd(p[j].fd,new_fd,0);
				close(new_fd);
				p[j].busy=1;
				printf("p[%d].pid=%d is busy\n",j,p[j].pid);
			}
			if(fds[0]==evs[i].data.fd){
				epoll_del(epfd,sfd);
				printf("已解注册\n");
				close(sfd);
				printf("已停止监听\n");
				for(i=0;i<num;i++){
					send_fd(p[i].fd,0,1);
				}
				printf("I'll close all childs\n");
				for(i=0;i<num;i++){
					wait(NULL);
				}
				printf("I have closed all childs\n");
				return 0;
			}
			for(j=0;j<num;j++){
				if(p[j].fd==evs[i].data.fd){
					read(p[j].fd,&flag,sizeof(int));
					printf("p[%d].pid=%d is not busy\n",j,p[j].pid);
					p[j].busy=0;
				}
			}
		}
	}
}

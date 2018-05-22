#include "func.h"

void set_nonblock(int fd){
	int tmp=fcntl(fd,F_GETFL);
	tmp=tmp|O_NONBLOCK;
	fcntl(fd,F_SETFL,tmp);
}

int main(int argc,char *argv[]){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}

	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	int ret;
	int reuse=1;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("bind");
		return -1;
	}
	listen(sfd,5);//激活
	int new_fd;
	int epfd=epoll_create(1);
	struct epoll_event event;
	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=0;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	//监控标准输入可读
	if(ret==-1){
		perror("epoll_ctl");
		return -1;
	}

	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	//监控客户端连接请求
	if(ret==-1){
		perror("epoll_ctl");
		return -1;
	}

	struct sockaddr_in cli;
	int sz=sizeof(cli);


	int i;
	int nret;
	char buf[5]={0};
	while(1){
		struct epoll_event evs[3];
		nret=epoll_wait(epfd,evs,3,-1);
		for(i=0;i<nret;i++){
			if(sfd==evs[i].data.fd){
				bzero(&cli,sizeof(cli));
				new_fd=accept(sfd,(struct sockaddr*)&cli,&sz);
				//得到new_fd
				if(new_fd==-1){
					perror("accept");
					return -1;
				}
				set_nonblock(new_fd);//自定子函数设置非阻塞状态
				bzero(&event,sizeof(event));
				event.events=EPOLLIN|EPOLLET;//边沿触发
				event.data.fd=new_fd;
				ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
				//监控new_fd
				if(ret==-1){
					perror("epoll_ctl");
					return -1;
				}
				printf("服务器就绪\n");
				printf("ip=%s,port=%d,sfd=%d,new_fd=%d\n",inet_ntoa(ser.sin_addr),ntohs(ser.sin_port),sfd,new_fd);
				printf("client port=%d\n",ntohs(cli.sin_port));
			}
			if(new_fd==evs[i].data.fd){
				while(1){
					bzero(&buf,sizeof(buf));
					ret=recv(new_fd,buf,sizeof(buf),0);
					if(ret==-1&&errno==EAGAIN){
						break;
					}else if(ret==0){
						printf("chatdown\n");
						bzero(&event,sizeof(event));
						event.events=EPOLLIN;
						event.data.fd=new_fd;
						epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
						close(new_fd);
						break;
					}
					printf("%s",buf);
				}
				//printf("\n");
			}
			if(0==evs[i].data.fd){
				bzero(&buf,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0){
					send(new_fd,buf,strlen(buf),0);
				}else{
					printf("serverdown\n");
					bzero(&event,sizeof(event));
					event.events=EPOLLIN;
					event.data.fd=new_fd;
					epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
					close(new_fd);
					break;
				}
			}
		}
	}
EXIT:
	close(new_fd);
	close(sfd);
	return 0;
}

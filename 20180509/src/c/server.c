 ///
 /// @file    server.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-22 10:13:03
 ///
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(void)
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);//FILE*
	if(-1 == listenfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	//一个服务器程序主动关闭之后，立马可以重启
#if 1
	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		perror("setsockopt error");	
		close(listenfd);
		exit(EXIT_FAILURE);
	}
#endif

#if 1
	//实现系统级别的负载均衡,一个服务器程序可以在同一台物理主机的同一时刻启动多个
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) < 0)
	{
		perror("setsockopt error");	
		close(listenfd);
		exit(EXIT_FAILURE);
	}
#endif

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;  //小端模式      大端模式
	serverAddr.sin_port = htons(8888);//主机字节序转成网络字节序列
	serverAddr.sin_addr.s_addr = INADDR_ANY;//代表本机地址
	
	int ret = bind(listenfd, 
				   (struct sockaddr *)&serverAddr,
				   sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(listenfd);
		exit(EXIT_FAILURE);
	}

	ret = listen(listenfd, 10);
	if(-1 == ret)
	{
		perror("listen");
		close(listenfd);
		exit(EXIT_FAILURE);
	}
	
	int peerFd = accept(listenfd, NULL, NULL);// 完成三次握手
	char buff[1024] = "welcome to server.";//用户态的应用缓冲区
	ret = write(peerFd, buff, strlen(buff));//将应用缓冲区的数据直接copy到内核发送缓冲区
	while(1)
	{
	
		memset(buff, 0, 1024);
		printf("> pls client data:\n");
		ret = read(peerFd, buff, 1024);//将内核接收缓冲区中的数据直接copy到应用缓冲区
		printf("%s\n", buff);
		ret = write(peerFd, buff, strlen(buff));
	}
	close(listenfd);
	return 0;
}

 ///
 /// @file    Socket.cpp
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-20 22:59:38
 ///
 
#include "InetAddress.h"
#include "Socket.h"

namespace wd
{
	Socket::Socket(int sockfd)
	:sockfd_(sockfd)
	{}

	Socket::Socket()
	:sockfd_()//写一个内联函数
	{}

	Socket::~Socket(){
		close(sockfd_);
	}

	int Socket::fd() const{
		return sockfd_;
	}
}

 ///
 /// @file    Socket.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-20 22:59:34
 ///
 
#ifndef _WD_SOCKET_H
#define _WD_SOCKET_H

#include <boost/utility.hpp>

namespace wd
{
	class InetAddress;
	class Socket : boost::noncopyable//不可复制
	{
		public:
			Socket(int sockfd);//两种构造函数
			Socket();
			~Socket();

			int fd() const;//获取fd
			void shutdownWrite();//关闭写端
			void nonblock();//设置为非阻塞

			static InetAddress getLocalAddr(int socjfd);//获取本地的sockaddr_in类
			static InetAddress getPeerAddr(int socjfd);//获取另一端的sockaddr_in类
		private:
			int sockfd_;
	};
}
#endif

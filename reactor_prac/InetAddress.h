 ///
 /// @file    InetAddress.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-20 22:27:39
 ///
 
#ifndef _WD_INETADDRESS_H
#define _WD_INETADDRESS_H

#include <netinet/in.h>
#include <string>

namespace wd
{
	class InetAddress{
		public:
			InetAddress(unsigned short port);//三种构造函数
			InetAddress(const char * pIp,unsigned short port);
			InetAddress(const struct sockaddr_in & addr);

			const struct sockaddr_in * getSockAddrPtr() const;//获取sockaddr_in类
			std::string ip() const;//获取IP地址
			unsigned short port() const;//获取端口号
		private:
			struct sockaddr_in addr_;
	};
}
#endif

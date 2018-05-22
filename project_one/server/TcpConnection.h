 ///
 /// @file    TcpConnection.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-05 16:59:04
 ///

#ifndef _WD_TCPCONNCETION_H
#define _WD_TCPCONNCETION_H

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace wd
{

class EpollPoller;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : Noncopyable,
	public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
	TcpConnection(int sockfd, EpollPoller * loop);
	~TcpConnection();

	std::string receive();//接收
	void send(const std::string & msg);//发送
	void sendInLoop(const std::string & msg);
	void shutdown();//关闭，内部调用socket的shutdown方法

	std::string toString();//用来打印从哪里到哪里（ip地址端口号）

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

private:
	Socket sockfd_;
	SocketIO sockIO_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	bool isShutdownWrite_;
	EpollPoller * loop_;

	TcpConnectionCallback onConnectionCb_;
	TcpConnectionCallback onMessageCb_;
	TcpConnectionCallback onCloseCb_;

};

}//end of namespace wd

#endif

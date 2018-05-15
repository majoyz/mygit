
#include "TcpServer.h"
#include <iostream>
using std::cout;
using std::endl;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());//1.获取数据
	//2. 对数据做处理,交给线程池来做
	//Task task(s, conn);
	//Threadpool.addTask(std::bind(&Task::process, task));
	//第三步，要线程池的线程(计算线程)通知EpollPoller对象所在的线程（IO线程）完成
	cout << "client msg:" << s << endl;
	conn->send(s);
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}

int main(int argc, char const *argv[])
{
	wd::TcpServer tcpserver("192.168.30.128", 9999);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

    return 0;
}

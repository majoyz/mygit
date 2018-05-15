
#include "TcpServer.h"
#include "Threadpool.h"
#include "conf.h"
#include "Mydict.h"
#include <iostream>
#include <queue>
using std::cout;
using std::endl;

int mymin(int a,int b,int c){
	if(a<=b&&a<=c)
		return a;
	else if(b<=a&&b<=c)
		return b;
	else
		return c;
}

int getmed(int tsize,int ssize,string &target,string &source){
	if(tsize == 0)
		return ssize;
	else if(ssize == 0)
		return tsize;
	return mymin(getmed(tsize-1,ssize,target,source)+1
			,getmed(tsize-1,ssize-1,target,source)+(target[tsize-1]==source[ssize-1]?0:2)
			,getmed(tsize,ssize-1,target,source)+1);
}

int Min_Edit_Distance(string target,string source){
	int tsize = target.size();
	int ssize = source.size();
	int ret = getmed(tsize,ssize,target,source);
	return ret;
}


struct MyResult{
	string _word;//候选词
	int _iFreq;//词频
	int _iDist;//与查询词的最小编辑距离
};

auto MyCompare = [](const MyResult & lhs,const MyResult & rhs){
	//lhs更接近则返回true
	unsigned long i = 0;
	if(lhs._iDist < rhs._iDist)
		return true;
	else if(lhs._iDist > rhs._iDist)
		return false;
	else{
		if(lhs._iFreq > rhs._iFreq)
			return true;
		else if(lhs._iFreq < rhs._iFreq)
			return false;
		else{
			while(i<lhs._word.size()&&i<rhs._word.size()){
				if(lhs._word[i] < rhs._word[i])
					return true;
				else
					return false;
				++i;
			}
		}
	}
	return true;
};

class Task
{
public:
	Task(const string & query, const wd::TcpConnectionPtr & conn)
	: _queury(query)
	, _conn(conn)
	, _resultQue(MyCompare)
	{}
	
	//process的执行是在一个计算线程里面完成的
	void process()
	{
		cout << "> task is processing" << endl;
		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		//
		Configuration myconf("../conf/my.conf");
		auto mydict = Mydict::createInstance();
		//string dictenpath = myconf.getConfigMap()["mydict"];
		//string indexenpath = myconf.getConfigMap()["myindex"];
		mydict->init(myconf.getConfigMap()["mydict"].c_str(),myconf.getConfigMap()["myindex"].c_str());//初始化词典及索引
		int j = _queury.size();
		string ctmp;
		MyResult myresult;
		while(--j>=0){
			ctmp = _queury[j];
			for(auto linenum : (mydict->getIndexTable())[ctmp]){
				myresult._word = mydict->getDict()[linenum].first;
				myresult._iFreq = mydict->getDict()[linenum].second;
				myresult._iDist = Min_Edit_Distance(_queury,myresult._word);
			}
			_resultQue.push(myresult);
		}

		//
		string result5;
		int i = 5;//把头5个相似词传给客户端
		while(--i){
			result5 = result5 + _resultQue.top()._word;
			_resultQue.pop();
		}
		//
		_conn->sendInLoop(result5);
	}
private:
	string _queury;
	wd::TcpConnectionPtr _conn;
	std::priority_queue<MyResult,vector<MyResult>,decltype(MyCompare)> _resultQue;
};

wd::Threadpool * g_threadpool = NULL;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());

	Task task(s, conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}

//class EchoServer
//{
//public:
//	void start();
//	void onMessage();
//	void onConnection();
//	void onClose();
//private:
//	Threadpool _threadpool;
//	TcpServer _server;
//};

int main()
{
	wd::Threadpool threadpool(4, 10);
	g_threadpool = &threadpool;
	threadpool.start();

	wd::TcpServer tcpserver("192.168.5.47", 9999);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

    return 0;
}

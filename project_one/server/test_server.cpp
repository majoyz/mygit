
#include "TcpServer.h"
#include "Threadpool.h"
#include "conf.h"
#include "Mydict.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cstring>
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
//
int edit_length(string &x, string &y){  
	int xlen = x.length();  
	int ylen = y.length();  
	int edit[3][30+1];  
	memset(edit, 0, sizeof(edit));  

	int i = 0;  
	int j = 0;  
	for(j = 0; j <= ylen; j++){  
		edit[0][j] = j;  
	}  
	for(i = 1; i <= xlen; i++){  
		edit[i%3][0] = edit[(i-1)%3][0] + 1;  
		for(j = 1; j <= ylen; j++){  
			if (x[i-1] == y[j-1]) {  
				edit[i%3][j] = min(min(edit[i%3][j-1] + 1, edit[(i-1)%3][j] + 1),  
						edit[(i-1)%3][j-1]);  
			} else {  
				if(i >= 2 && j >= 2 && x[i-2] == y[j-1] && x[i-1] == y[j-2]){  
					edit[i%3][j] = min(min(edit[i%3][j-1] + 1, edit[(i-1)%3][j] + 1),  
							min(edit[(i-1)%3][j-1] + 1, edit[(i-2)%3][j-2] + 1));  
				} else {  
					edit[i%3][j] = min(min(edit[i%3][j-1] + 1, edit[(i-1)%3][j] + 1),  
							edit[(i-1)%3][j-1] + 1);  
				}  
			}  
		}  
	}  
	return edit[(i-1)%3][j-1];  
}  
//
struct MyResult{
	string _word;//候选词
	int _iFreq;//词频
	int _iDist;//与查询词的最小编辑距离
};

auto MyCompare = [](const MyResult & rhs,const MyResult & lhs){
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
			Configuration myconf("../conf/my.conf");
			//		cout << "after conf" << endl;
			auto mydict = Mydict::createInstance();
			//		cout << "after Mydict create" << endl;
			string dictenpath = myconf.getConfigMap()["mydict"].c_str();
			string indexenpath = myconf.getConfigMap()["myindex"].c_str();
			mydict->init(myconf.getConfigMap()["mydict"].c_str(),myconf.getConfigMap()["myindex"].c_str());//初始化词典及索引
			//		cout << "after Mydict init" << endl;
			int j = _queury.size();
			string ctmp;
			MyResult myresult;
			set<int> tmp_hebing;
			//		cout << _queury << "'s size = " << j << endl;
			while(--j>=0){
				ctmp = _queury[j];
				//有重复字母时没有查重
				//			set_union(tmp_hebing.begin(),tmp_hebing.end(),mydict->getIndexTable()[ctmp].begin(),mydict->getIndexTable()[ctmp].end(),back_inserter(tmp_hebing));
				tmp_hebing.insert(mydict->getIndexTable()[ctmp].begin(),mydict->getIndexTable()[ctmp].end());
				//			for(auto linenum : (mydict->getIndexTable())[ctmp]){
				//				myresult._word = mydict->getDict()[linenum].first;
				//				myresult._iFreq = mydict->getDict()[linenum].second;
				//				myresult._iDist = Min_Edit_Distance(_queury,myresult._word);
				//			cout << myresult._word << " " << myresult._iFreq << " " << myresult._iDist << endl;
				//			_resultQue.push(myresult);
				//			}
			}
			//		cout << "hebing finish" << endl;
			//		合并很快的，主要是下面的部分慢
			int suduceshi = 0;
			for(auto linenum : tmp_hebing){
				myresult._word = mydict->getDict()[linenum].first;
				myresult._iFreq = mydict->getDict()[linenum].second;
				//myresult._iDist = Min_Edit_Distance(_queury,myresult._word);
				myresult._iDist = edit_length(_queury,myresult._word);
				//			cout << myresult._word << " " << myresult._iFreq << " " << myresult._iDist << endl;
				_resultQue.push(myresult);
				++suduceshi;
				if(!(suduceshi%100))
					//			数量增长不多，应该是MED算法耗时增加
					cout << suduceshi << endl;
			}

			string result5;
			int i = 6;//把头5个相似词传给客户端
			while(--i){
				result5 = result5 + _resultQue.top()._word;
				result5 = result5 + " ";
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

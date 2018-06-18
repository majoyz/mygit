
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
#include <hiredis/hiredis.h>//redis C接口库
using std::cout;
using std::endl;

int edit_length(string &x, string &y){ //Damerau-Levenstein最小编辑距离算法，动态规划 
	if(x[0]>96&&x[0]<123){//英文
		int xlen = x.length();
		int ylen = y.length();
		int edit[xlen+1][ylen+1];
		memset(edit, 0, sizeof(edit));
		int i = 0;
		int j = 0;
		for(j = 0; j <= ylen; j++){ 
			edit[0][j] = j;
		}
		for(i = 1; i <= xlen; i++){
			edit[i][0] = edit[i-1][0] + 1;
			for(j = 1; j <= ylen; j++){
				if (x[i-1] == y[j-1]) {
					edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
							edit[i-1][j-1]);
				} else {
					if(i >= 2 && j >= 2 && x[i-2] == y[j-1] && x[i-1] == y[j-2]){
						edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
								min(edit[i-1][j-1] + 1, edit[i-2][j-2] + 1));
					} else {
						edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
								edit[i-1][j-1] + 1);
					}
				}
			}
		}
		return edit[i-1][j-1];
	}else{//中文
		int xlen = x.length()/3;
		int ylen = y.length()/3;
		string tmpx,tmpy,tmpx2,tmpy2;
		int edit[xlen+1][ylen+1];
		memset(edit, 0, sizeof(edit));

		int i = 0;  
		int j = 0;  
		for(j = 0; j <= ylen; j++){  
			edit[0][j] = j;  
		}  
		for(i = 1; i <= xlen; i++){  
			edit[i][0] = edit[i-1][0] + 1;  
			for(j = 1; j <= ylen; j++){  
				tmpx = x.substr(3*(i-1),3);
				tmpy = y.substr(3*(j-1),3);
				if (tmpx == tmpy) {
					edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
							edit[i-1][j-1]);
				} else {
					if(i >= 2 && j >= 2 && x.substr(3*(i-2),3)==tmpy && tmpx == y.substr(3*(j-2),3)){
						tmpx2 = x.substr(3*(i-2),3);
						tmpy2 = y.substr(3*(j-2),3);
						if(tmpx2 == tmpy && tmpx == tmpy2){
							edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
									min(edit[i-1][j-1] + 1, edit[i-2][j-2] + 1));
						}
					} else {
						edit[i][j] = min(min(edit[i][j-1] + 1, edit[i-1][j] + 1),
								edit[i-1][j-1] + 1);
					}
				}
			}
		}
		return edit[i-1][j-1];
	}
}

struct MyResult{//每一个候选词的结果类
	string _word;//候选词
	int _iFreq;//词频
	int _iDist;//与查询词的最小编辑距离
};

auto MyCompare = [](const MyResult & rhs,const MyResult & lhs){//MyResult的比较
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
			while(i<lhs._word.size()&&i<rhs._word.size()){//这里对中文有问题吗？试试
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
			//在这里，先去缓存里查，查到的话直接最后一步发送
			//在这个计算线程里，只需要去拿一个cache
			//线程id是唯一的，调用pthread_self()返回的id肯定是不一样的
			//可以建立一个pthread_t到cache的一个映射
			//或
			//用cachemanager类管理，即要用的方法
			//或
			//利用线程局部存储的方式
			redisContext *rc = redisConnect("127.0.0.1",6379);
			redisReply *r = (redisReply*)redisCommand(rc,"get %s",_queury.c_str());
			if (NULL == r) {
				printf("Redis Command error []\n");
				redisFree(rc);  
				return;
			}   
			if (r->type == REDIS_REPLY_ERROR ) { 
				printf("Redis Command[], error:%s\n", r->str);
				freeReplyObject(r);
				redisFree(rc);  
				return;
			}  
			if(r->str){//在缓存里有，在这里直接返回
				_conn->sendInLoop(r->str);
				cout << "get from redis" << endl;
				return;
			}
			Configuration myconf("../conf/my.conf");
			auto mydict = Mydict::createInstance();//词典单例模式的创建
			string dictenpath = myconf.getConfigMap()["mydict"].c_str();//获取词典路径
			string indexenpath = myconf.getConfigMap()["myindex"].c_str();//获取索引路径
			string dictcnpath = myconf.getConfigMap()["mydictcn"].c_str();//获取中文词典路径
			string indexcnpath = myconf.getConfigMap()["myindexcn"].c_str();//获取中文索引路径
			mydict->init(myconf.getConfigMap()["mydict"].c_str(),myconf.getConfigMap()["myindex"].c_str(),myconf.getConfigMap()["mydictcn"].c_str(),myconf.getConfigMap()["myindexcn"].c_str());//初始化词典及索引
			int j = _queury.size();
			string ctmp;
			MyResult myresult;
			set<int> tmp_hebing;
			if(_queury[0]>96&&_queury[0]<123){//英文
				while((--j)>=0){
					ctmp = _queury[j];//有重复字母时没有查重
					tmp_hebing.insert(mydict->getIndexTable()[ctmp].begin(),mydict->getIndexTable()[ctmp].end());
				}
			}else{
				for(int i = 0;i<j;i+=3){
					ctmp = _queury.substr(i,3);//有重复字母时没有查重
					cout << " ctmp = " << ctmp << endl;
					tmp_hebing.insert(mydict->getIndexTable()[ctmp].begin(),mydict->getIndexTable()[ctmp].end());
				}
				for(auto every : tmp_hebing){
					cout << every << " ";
				}
				cout << endl;
			}
			//合并很快的，主要是下面的部分慢，不用那个递归就好了
			int suduceshi = 0;
			for(auto linenum : tmp_hebing){
				myresult._word = mydict->getDict()[linenum].first;
				myresult._iFreq = mydict->getDict()[linenum].second;
				myresult._iDist = edit_length(_queury,myresult._word);
//				myresult._iDist = editDistance(_queury,myresult._word);
				_resultQue.push(myresult);
				++suduceshi;
				if(!(suduceshi%1000))
					cout << suduceshi << endl;
			}
			if(_resultQue.empty()){
				_conn->sendInLoop(" ");
				return;
			}
			string result5;
			int i = 6;//把头5个相似词传给客户端
			while(--i){
				result5 = result5 + _resultQue.top()._word;
				result5 = result5 + to_string(_resultQue.top()._iDist);
				result5 = result5 + " ";
				_resultQue.pop();
				if(_resultQue.empty())
					break;
			}
			redisCommand(rc,"set %s %s",_queury.c_str(),result5.c_str());//放进缓存
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

	wd::TcpServer tcpserver("10.211.55.4", 8888);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

	return 0;
}

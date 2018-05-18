 ///
 /// @file    myhiredis.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-16 15:23:18
 ///
 
#include <iostream>
#include <hiredis/hiredis.h> //redis C接口库
using namespace std;

class MyHiredis{
	public:
		MyHiredis();//在构造函数里连接
		~MyHiredis();
		int get(const char *format);
		int set(const char *format);
	private:
		redisContext *_rc;
		redisReply *_rrp;
};

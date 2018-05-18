 ///
 /// @file    myhiredis.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-16 15:30:27
 ///
 
#include "myhiredis.h"

MyHiredis::MyHiredis(){
	_rc = redisConnect("127.0.0.1",6379);
	cout << "MyHiredis()" << endl;
}

MyHiredis::~MyHiredis(){
	freeReplyObject(_rrp);
	redisFree(_rc);
	cout << "~MyHiredis()" << endl;
}

int MyHiredis::get(const char *format){
	
}

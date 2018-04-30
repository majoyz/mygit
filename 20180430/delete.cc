 ///
 /// @file    delete.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-30 17:44:37
 ///
 
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
using namespace std;

int main(){
	shared_ptr<FILE> sp(fopen("test.txt","w+"));//需要一个delete参数？制定删除方式？
	string msg("hello,world");
	fwrite(msg.c_str(),msg.size(),1,sp.get());
}

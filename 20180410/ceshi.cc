 ///
 /// @file    ceshi.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-10 10:30:39
 ///
 
#include <iostream>
using std::cout;
using std::endl;

void func(){
	cout<<"I'm func"<<endl;
	return;
}

int main(){
	func();
	::printf("I'm printf\n");
	return 0;
}

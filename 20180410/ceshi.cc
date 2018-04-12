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

void learn_const(){
	const int x=10;
	int a=20,b=30,c=40;
	const int *pa=&a;//常量指针
	int * const pb=&b;
	const int * const pc=&c;
	cout<<"x="<<x<<" a="<<*pa<<" b="<<*pb<<" c="<<*pc<<endl;
	return;
}

void learn_new(){
	int *p1=new int(10);
	cout<<"*p1="<<*p1<<endl;

	return;
}

int main(){
	func();
//	::printf("I'm printf\n");
	learn_const();
	learn_new();
	return 0;
}

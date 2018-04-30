 ///
 /// @file    lrvalue.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-30 11:24:31
 ///
 
#include <iostream>
using namespace std;

int main(){
	int a=1;
	int b=2;
	int * pflag = &a;

	&a;
	&b;
	//&(a+b);//error,right value
	//&(a++);//error,right value
	&(++a);
	&(*pflag);
	//&100;//error right value
	//&string("hello");//error right value
	const int & m = 3;//const can get right value
	const int & n = a;//const can get left value
	//int & x = 7;//error can't get right value without const
	
	//行参不能区分实参传递过来的是左值还是右值（c++11之前）
	//
	//c++11提出了右值引用&&，只能绑定到右值
	
	return 0;
}

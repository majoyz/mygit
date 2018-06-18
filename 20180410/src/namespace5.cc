 ///
 /// @file    namespace5.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 10:22:27
 ///
 
#include <stdio.h>  //C++为了兼容C，认为C的标准库函数统统位于匿名的名称空间
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


void func(void)
{
	cout << "func()" << endl;
}
 
int main(void)
{
	::printf("hello,world\n");
	::func();

	return 0;
}

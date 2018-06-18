 ///
 /// @file    hello.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 09:44:04
 ///
 
#include <stdio.h>
#include <iostream> //C++标准库的头文件没有.h后缀, 它的实现是模板写的  
 
using namespace std;//命名空间

// 1 << 4; // 左移运算符

int main(void)
{
	printf("hello,world\n");//函数
	cout << "hello,world" << endl;//cout是一个对象, << 输出流运算符
	//cout >> "hello";
	int a;
	cin >> a; 
	return 0;
}

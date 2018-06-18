 ///
 /// @file    memory2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 11:30:30
 ///
 
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

int a = 10;
const int b = 1;//位于文字常量区
 
int main(void)
{
	int c = 100;
	const int d = 11;//位于栈上
	const char * p1 = "hello";

	printf("&a = %p\n", &a);
	printf("&b = %p\n", &b);
	printf("&c = %p\n", &c);
	printf("&d = %p\n", &d);
	printf("p1 = %p\n", p1);
 
	return 0;
}

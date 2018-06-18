 ///
 /// @file    memory.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 11:12:11
 ///
 
#include <stdio.h>

int a = 0;
char * p1;//全局变量自动会进行初始化
 
int main(void)
{
	int b;
	char s[] = "123456";//栈上
	char * p2;
	const char * p3 = "123456";//文字常量区
	static int c = 0;
	p1 = new char[10];
	p2 = new char[5];

	printf("&a = %p\n", &a);
	printf("p1 = %p\n", p1);
	printf("&p1 = %p\n", &p1);
	printf("&b = %p\n", &b);
	printf("&s = %p\n", s);
	printf("p2 = %p\n", p2);
	printf("&p2 = %p\n", &p2);
	printf("p3 = %p\n", p3);
	printf("&p3 = %p\n", &p3);
	printf("&c = %p\n", &c);
	printf("&main = %p\n", main);

	//*p3 = 'A';

	return 0;
}

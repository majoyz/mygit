 ///
 /// @file    new.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 11:19:22
 ///
 
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//malloc/free 与new/delete的差别？
//1. malloc/free是库函数,  new/delete是表达式
//2. malloc只负责开辟空间，并不会初始化空间的内容
//	 new表达式除了开辟空间，它还会进行初始化
 
void test0(void)
{
	int * p1 = (int *)malloc(sizeof(int));
	*p1 = 100;
	cout << "*p1 = " << *p1 << endl;

	int * p2 = (int *)malloc(10 * sizeof(int));
	memset(p2, 0, 10 * sizeof(int));//清零，做初始化

	for(int idx = 0; idx != 10; ++idx)
	{
		p2[idx] = idx;
	}
	for(int idx = 0; idx != 10; ++idx)
	{
		cout << p2[idx] << endl;
	}
 
	free(p1);
	free(p2);
}

void test1(void)
{
	int * p1 = new int(10);
	cout << "*p1 = " << *p1 << endl;

	int * p2 = new int[10]();
	for(int idx = 0; idx != 10; ++idx)
	{
		p2[idx] = idx;
	}
	for(int idx = 0; idx != 10; ++idx)
	{
		cout << p2[idx] << endl;
	}

	delete p1;
	delete [] p2;
}

int main(void)
{
	test0();
	test1();

	return 0;
}

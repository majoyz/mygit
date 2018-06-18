 ///
 /// @file    overload.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 15:18:34
 ///
 
#include <stdio.h>

//C++语言支持函数重载
//实现原理：名字改编(name mangling)
//具体步骤:当函数名称相同时, 会根据参数的类型、个数、顺序不同进行改编
int add(int x, int y)
{
	return x + y;
}

int add(int x, double y)
{
	return x + y;
}

int add(int x, int y, int z)
{
	return x + y + z;
}
 
int main(void)
{
	int a = 3, b = 4, c = 5;

	printf("a + b = %d\n", add(a, b));
	printf("a + b + c = %d\n", add(a, b, c));
	return 0;
}

 ///
 /// @file    overload.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 15:18:34
 ///
 
#include <stdio.h>

//C语言不支持函数重载
int add(int x, int y)
{
	return x + y;
}

int addx(int x, int y, int z)
{
	return x + y + z;
}
 
int main(void)
{
	int a = 3, b = 4, c = 5;

	printf("a + b = %d\n", add(a, b));
	printf("a + b + c = %d\n", addx(a, b, c));
	return 0;
}

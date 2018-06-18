 ///
 /// @file    const2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 11:00:28
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//int (*p)(void)   int *()
//函数指针    指针函数
//int (*p)[]      int *[]
//数组指针    指针数组
//
//常量指针    指针常量
//


 
int main(void)
{
	int a = 10;
	int b = 100;
	cout << "a = " << a << endl;

	const int * pa = &a;//常量指针(pointer to const)
	//*pa = 20;//error,通过pa指针不能修改所指变量的值 
	pa = &b;//ok, 能够改变pa的指向

	int const * pb = &a;
	//*pb = 20;
	pb = &b;

	int * const pc = &a;//指针常量(const pointer)
	*pc = 20;//ok, 通过pc指针是可以修改所指变量的值
	//pc = &b;//error, 不能改变pa的指向
	cout << "a = " << a << endl;

	const int * const pd = &a;//两者都不能进行修改
	//*pd = 20;//error
	//pd = &b;//error

 

	return 0;
}

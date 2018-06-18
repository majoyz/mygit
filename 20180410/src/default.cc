 ///
 /// @file    default.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 16:10:25
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//C++里定义的函数可以设置默认值(缺省参数)
//
//默认参数的设置顺序是从右到左的
int add(int x = 0, int y = 0)
{
	return x + y;
}

//设置默认值可能会导致二义性，注意不要这样使用
//int add(int x, int y, int z = 0)
int add(int x, int y, int z)
{
	return x + y + z;
}
 
int main(void)
{
	int a = 3, b = 4, c = 5;
	//add(,b)

	//cout << "add() = " << add() << endl;
	//cout << "add(a) = " << add(a) << endl;
	cout << "add(a, b) = " << add(a, b) << endl;
	cout << "add(a, b, c) = " << add(a, b, c) << endl;
 
	return 0;
}

 ///
 /// @file    const.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 10:48:39
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//编辑 --> 预编译 --> 编译 --> 链接 --> 执行

//定义一个常量
#define MAX 100
//1. 宏定义发生时机：预编译（预处理）, 简单的执行字符串的替换而已，没有类型检查
//
//2. const常量发生时机：编译, 有类型检查，
 
int main(void)
{
	int a = 1;
	const int b = 10;
	//b = 20;//error
	
	//const int c;//const修饰的变量必须要进行初始化

	cout << a * MAX << endl;
	cout << "const b = " << b << endl;

	return 0;
}

 ///
 /// @file    variadicTemplate.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-20 11:17:17
 ///
 
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string; 
template <typename... Args> //Args称为模板参数包
void display(Args... args)//args 称为函数参数包
{
	//获取可变参数的用法
	cout << "sizeof(Args) = " << sizeof...(Args) << endl;
	cout << "sizeof(args) = " << sizeof...(args) << endl;
}
int test0(void)
{
	display(1);
	display(1, 'a');
	display(1, 'a', string("hell"));
	display(1, 'a', "hell", 1.1);
	return 0;
}

//============================================

// 递归调用
void print()
{	cout <<endl;	}

template <typename T, typename... Args>
void print(T t, Args... args)
{
	cout << t << endl;
	print(args...);//函数参数包扩展 print(arg1, arg2, ..., argN)
	//print();
}

void test1(void)
{
	print(1, 2, 3 ,4);
	//print(2, 3, 4)
	//print(3, 4)
	//print(4)
	//print()
}

//============================================
template <typename T>
T sum(T t)
{
	return t;
}

template <typename T, typename... Args>
T sum(T t, Args... args)
{
	return t + sum(args...);//
}

void test2(void)
{
	int ret = sum(1, 2, 3, 4);
	//1 + sum(2, 3, 4)
	//1 + 2 + sum(3, 4)
	//1 + 2 + 3 + sum(4)
	//1 + 2 + 3 + 4
	cout << ret << endl;
}

int main(void)
{
	test2();
	return 0;
}

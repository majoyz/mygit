 ///
 /// @file    Demo.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-17 11:45:38
 ///
 
#include <iostream>
using std::cout;
using std::endl;


struct Function
{
	//函数调用运算符
	int operator()(int x, int y)
	{
		++_count;
		return x + y;
	}

	int operator()(int x, int y, int z)
	{
		return x * y * z;
	}

	int getCount() const {	return _count;	}

	int _count = 0;// 对象的状态
};

//函数对象与普通函数的差别？
//函数对象内部可以存储自己的状态
//
//闭包
//
void display(void)
{
	static int count = 0;
	++count;
}
 
int main(void)
{
	Function func;
	cout << "1 + 2 = " << func(1, 2) << endl;//函数对象: 重载了函数调用运算符的对象
	cout << "3 + 4 =" << func(3, 4) << endl;
	cout << "func(1, 2, 3) = " << func(1, 2, 3) << endl;

	cout << "func被执行了 " << func.getCount() << "次" << endl;

	Function func2;
	cout << "5 + 6 = " << func2(5, 6) << endl;
	cout << "func2被执行了 " << func2.getCount() << "次" << endl;

	return 0;
}

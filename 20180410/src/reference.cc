 ///
 /// @file    reference.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 11:32:27
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	int number = 100;
	int ival = 1;
	//int & r;//引用是不能单独存在，它必须依附一个实体
	int & ref = number;//引用是一个变量的别名, 一经初始化(绑定)之后，就不能再改变其指向
	cout << "number = " << number << endl;
	cout << "ref = " << ref << endl;
	cout << "&number = " << &number << endl;
	cout << "&ref = " << &ref << endl;

	ref = 20;
	cout << "修改之后:" << endl;
	cout << "number = " << number << endl;
	cout << "ref = " << ref << endl << endl;

	ref = ival;
	cout << "number = " << number << endl;
	cout << "ref = " << ref << endl;
	cout << "ival = " << ival << endl;

	return 0;
}

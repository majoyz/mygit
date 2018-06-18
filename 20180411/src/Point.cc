 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 15:15:12
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	//构造函数可以进行重载

	//当没有定义任何构造函数时，编译器会为我们自动提供给一个默认构造函数
	Point()
	{
		_ix = 0;
		_iy = 0;
		cout << "Point()" << endl;
	}

	//一旦定义了自己的构造函数之后，编译器就不会再自动提供默认构造函数
	Point(int ix, int iy = 0)
	{
		cout << "Point(int,int)" << endl;
		_ix = ix;//赋值操作
		_iy = iy;
	}

	void print()
	{
		cout << "(" << _ix
			 << "," << _iy 
			 << ")" << endl;
	}

private:
	int _ix;
	int _iy;
};
 
int main(void)
{
	Point pt1(1, 2);
	pt1.print();

	Point pt2;
	pt2.print();

	Point pt3(3);
	pt3.print();

	return 0;
}

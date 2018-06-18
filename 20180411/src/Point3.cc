 ///
 /// @file    Point2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 15:15:12
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	Point()
	: _ix(0) //初始化列表/初始化表达式
	, _iy(0)
	{
		//_ix = 0;
		//_iy = 0;
		cout << "Point()" << endl;
	}

	Point(int ix, int iy = 0) 
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
		//_ix = ix;//赋值操作
		//_iy = iy;
	}

	//复制构造函数
	//如果不显式提供，编译器也会自动为我们提供一个
#if 1
	Point(const Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout << "Point(const Point &)" << endl;
	}
#endif

	void print()
	{
		cout << "(" << _ix
			 << "," << _iy 
			 << ")" << endl;
	}


	~Point()
	{	//做清理工作
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};
 
int test0(void)
{
	int a(1);
	cout << "a = " << a << endl;
	Point pt1(1, 2);
	pt1.print();

	Point pt2;
	pt2.print();

	Point pt3(3);
	pt3.print();

	return 0;
}

void test1()
{
	int a = 1;
	int b = a;
	cout << "b = " << b << endl;

	Point p1(1, 2);
	cout << "p1 = ";
	p1.print();
	Point p2 = p1;
	cout << "p2 = ";
	p2.print();
}

int main(void)
{
	test1();
	return 0;
}

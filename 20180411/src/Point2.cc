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

int main(void)
{
	test0();
	return 0;
}

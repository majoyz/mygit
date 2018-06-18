 ///
 /// @file    Line.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 14:34:08
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	Point()
	: _ix(0)
	, _iy(0)
	{
		cout << "Point()" << endl;
	}

	Point(int ix, int iy)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
	}
	void print()
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")";
	}

private:
	int _ix;
	int _iy;
};

class Line
{
public:
	Line(int x1, int y1, int x2, int y2)// 默认情况下，会调用相应对象的默认构造函数
	//: _pt1()
	//, _pt2()
	: _pt1(x1, y1)   //如果数据成员是对象成员，不希望其调用默认构造函数时，就要在显式调用相应构造函数
	, _pt2(x2, y2)
	{
		cout << "Line(int,int,int,int)" << endl;
	}

	void display()
	{
		_pt1.print();
		cout << " ---> " ;
		_pt2.print();
		cout << endl;
	}

private:
	Point _pt1;
	Point _pt2;
};
 
int main(void)
{
	//Point pt(1, 2);
	//pt.print();
	Line line(1, 2, 3, 4);
	line.display();
 
	return 0;
}

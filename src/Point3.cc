 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-18 10:05:52
 ///
 
#include "Mylogger.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Point
{
public:
	explicit  //禁止隐式转换,需要显式调用
	Point(int ix)
	: _ix(ix)
	, _iy(0)
	{
		cout << "Point(int)" << endl;
	}

	Point(int ix, int iy)
	: _ix(ix)
	, _iy(iy)
	{
		LogDebug("Point(int,int)");	
	}

	
	operator int()
	{
		return _ix;
	}

#if 0
	operator double()
	{
		return _ix;
	}
#endif

	
	//friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};

#if 0
std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}
#endif
 
int main(void)
{
	Point pt(1, 2);
	cout << "pt = " << pt << endl;//会自动调用类型转换函数将 pt对象转出int型数据

	return 0;
}

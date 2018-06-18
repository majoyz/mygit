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

class AnotherPoint;

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

	//类型转换函数的特征:
	//1. 没有返回值，
	//2. 没有参数
	//3. 在函数体内必须用传值方式以return语句返回一个目标类型的变量
	//
	//
	//4. 能不使用就不要使用, 不符合常理
	operator int()
	{
		cout << "operator int()" << endl;
		return _ix;
	}

	operator double()
	{
		cout << "operator double()" << endl;
		return _ix * _iy;
	}

	operator AnotherPoint();

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};

 
class AnotherPoint
{
public:
	explicit  //禁止隐式转换,需要显式调用
	AnotherPoint(int ix)
	: _ix(ix)
	, _iy(0)
	{
		cout << "AnotherPoint(int)" << endl;
	}

	AnotherPoint(int ix, int iy)
	: _ix(ix)
	, _iy(iy)
	{
		LogDebug("AnotherPoint(int,int)");	
	}

	friend std::ostream & operator<<(std::ostream & os, const AnotherPoint & rhs);
private:
	int _ix;
	int _iy;
};

Point::operator AnotherPoint()
{
	cout << "operator AnotherPoint(int,int)" << endl;
	return AnotherPoint(_ix, _iy);
}

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

std::ostream & operator<<(std::ostream & os, const AnotherPoint & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

int main(void)
{
	Point pt(1, 2);
	cout << "pt = " << pt << endl;
	int val1 = pt;
	cout << "val1 = " << val1 << endl;
	double val2 = pt;
	cout << "val2 = " << val2 << endl;
	cout << endl;

	AnotherPoint ap = pt;
	cout << "ap = " << ap << endl;
	return 0;
}

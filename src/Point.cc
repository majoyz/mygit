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

	void print() const
	{
		//LogInfo();
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
	std::string s1 = "hello,world";
	Point pt = 1;//由其他类型转换成自定类类型--> 由构造函数完成 --> 隐式转换
	pt.print();

	return 0;
}

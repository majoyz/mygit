 ///
 /// @file    Line.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-18 10:05:52
 ///
 
#include "Line.h"
#include <iostream>
using std::cout;
using std::endl;

class Line::LineImpl
{
	class Point//嵌套类, 如果是定义在private区域，就是只为外部类进行服务
	{
	public:
		Point(int ix, int iy)
		: _ix(ix)
		, _iy(iy)
		{}

		void print() const
		{
			cout << "(" << _ix
				 << "," << _iy
				 << ")";
		}
		
	private:
		int _ix;
		int _iy;
	};

public:
	LineImpl(int x1, int y1, int x2, int y2)
	: _pt1(x1, y1)
	, _pt2(x2, y2)
	{
		cout << "LineImpl(int, int, int, int)" << endl;
	}

	void display() const
	{
		_pt1.print();
		cout << "--->";
		_pt2.print();
		cout << endl;
	}
	
private:
	Point _pt1;
	Point _pt2;
};


Line::Line(int x1, int y1, int x2, int y2)
: _pImpl(new LineImpl(x1, y1, x2, y2))
{
	cout << "Line(int,int,int,int)" << endl;
}

Line::~Line()
{
	cout << "~Line()" << endl;
	if(_pImpl)
	{
		delete _pImpl;
	}
}

 ///
 /// @file    Point5.cc
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

	explicit //禁止隐式转换 //implicit
	Point(int ix, int iy = 0)
	: _ix(ix) 
	, _iy(iy)
	{
		cout << "Point(int,int = 0)" << endl;
	}

	Point(const Point & rhs);

#if 1
	void print(
	//Point * const this
	)
	{
		cout << "void Point::print()" << endl;
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}
#endif

#if 1
	//在const成员函数内部不能修改数据成员
	void print(
	// const Point * const this
	) const
	{
		//_ix = 100;//error
		cout << "void Point::print() const " << endl;
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}
#endif


	~Point()
	{
		cout << "~Point()" << endl;
	}
private:
	int _ix;
	int _iy;
};
 
int main(void)
{
	int arr[5];
	Point points[5] = {Point(1, 2), Point(3, 4)};
	
	Point pt = 1;//隐式转换 --> 构造函数
	pt.print();

	return 0;
}

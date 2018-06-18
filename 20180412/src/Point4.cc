 ///
 /// @file    Point3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 14:34:08
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	Point(int ix, int iy)
	: _ix(ix) 
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	Point(const Point & rhs);

#if 1
	void print(
	//Point * const this
	)
	{
		cout << "void Point::print()" << endl;
		this->_ix = 100;
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
private:
	int _ix;
	int _iy;
};
 
int main(void)
{
	Point pt(1, 2);// 非const对象既可以调用非const成员函数，也可以调用const成员函数
	pt.print();

	const int a = 10;

	const Point pt2(3, 4);//const对象只能调用const成员函数
	pt2.print();

	return 0;
}

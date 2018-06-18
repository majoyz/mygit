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
	Point(int ix, int iy, double & refx)
	: _ix(ix) //引用成员必须要放在初始化列表之中进行
	, _iy(iy)
	, _refx(refx)
	{
		//_ix = ix;
		//_iy = iy;
	}
	void print()
	{
		cout << "(" << _ix
			 << "," << _iy
			 << "," << _refx
			 << ")" << endl;
	}

private:
	int _ix;
	int _iy;
	double & _refx;
};
 
int main(void)
{
	double z = 5.5;
	Point pt(1, 2, z);
	pt.print();

	z = 6.6;
	pt.print();
 
	return 0;
}

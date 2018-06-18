 ///
 /// @file    Point2.cc
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
	: _ix(ix) //常量成员必须要放在初始化列表之中进行
	, _iy(iy)
	{
		//_ix = ix;
		//_iy = iy;
	}
	void print()
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

private:
	const int _ix;
	const int _iy;
};
 
int main(void)
{
	Point pt(1, 2);
	pt.print();
 
	return 0;
}

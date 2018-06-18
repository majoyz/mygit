 ///
 /// @file    X.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 15:56:36
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class X
{
public:
	//初始化成员时，成员初始化的顺序只与其被声明时的顺序保持一致，
	//而与其初始化列表中的顺序无关
	X(int iy)
	: _iy(iy)
	, _ix(_iy)
	{
		
	}

	void print()
	{
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
	X x(2);
	x.print();

	return 0;
}

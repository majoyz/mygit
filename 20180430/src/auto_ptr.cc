 ///
 /// @file    auto_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 16:00:04
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;
 
class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{	cout << "Point(int,int)" << endl;	}

	void display() const{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	~Point(){	cout << "~Point()" << endl;}
	
	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

int main(void)
{
	auto_ptr<Point> ap(new Point(1, 2));
	cout << "ap'get = " << ap.get() << endl;
	cout << "*ap = " << *ap << endl;
	ap->display();
	cout << endl;
	
	auto_ptr<Point> ap2(ap);//在语法上是一个复制操作
							//但实现时，已经发生了所有权的转移
							//存在缺陷
	cout << "*ap2 = " << *ap2 << endl;
	cout << "*ap = " << *ap << endl;//error，段错误

	return 0;
}

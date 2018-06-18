 ///
 /// @file    abuse_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 17:27:01
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;
 
class Point
: public std::enable_shared_from_this<Point>
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

	shared_ptr<Point> addPoint(Point * pt)
	{//在类内部获取本对象的智能指针
		_ix += pt->_ix;
		_iy += pt->_iy;
		//return shared_ptr<Point>(this);
		return shared_from_this();
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

void test0(void)
{
	//误用： 将一个原生裸指针交给两个不同的智能指针进行托管
	Point * pt = new Point(1, 2);
	//shared_ptr<Point> sp(pt);
	//shared_ptr<Point> sp2(pt);
	unique_ptr<Point> up(pt);
	unique_ptr<Point> up2(pt);
}

void test1(void)
{
	shared_ptr<Point> sp(new Point(1, 2));
	shared_ptr<Point> sp2(new Point(3, 4));

	shared_ptr<Point> sp3(sp->addPoint(sp2.get()));
}

int main(void)
{
	//test0();
	test1();
	return 0;
}

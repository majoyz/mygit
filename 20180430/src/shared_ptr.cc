 ///
 /// @file    shared_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 16:31:05
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
 
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
	shared_ptr<Point> sp(new Point(1, 2)); 
	cout << "sp' use_count = " << sp.use_count() << endl;
	cout << "*sp = " << *sp << endl;
	cout << "sp'get = " << sp.get() << endl<< endl;


	//shared_ptr是共享所有权的智能指针
	//当进行复制或赋值时，只需要将引用计数加1
	shared_ptr<Point> sp2(sp);//复制语义
	cout << "*sp = " << *sp << endl;
	cout << "*sp2 = " << *sp2 << endl;

	cout << "sp' use_count = " << sp.use_count() << endl;
	cout << "sp2' use_count = " << sp2.use_count() << endl << endl;


	shared_ptr<Point> sp3;
	sp3 = sp2;//赋值
	cout << "sp2' use_count = " << sp2.use_count() << endl;
	cout << "sp3' use_count = " << sp3.use_count() << endl;

	return 0;
}

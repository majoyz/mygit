 ///
 /// @file    weak_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 17:12:37
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::weak_ptr;
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
{	//weak_ptr不能直接托管对象,不能直接访问被托管的对象
	//weak_ptr<Point> wp(new Point(1, 2));
	weak_ptr<Point> wp;

	{//语句块
		shared_ptr<Point> sp(new Point(1, 2));	
		wp = sp;//
		cout << "wp' use_count = " << wp.use_count() << endl;
		//cout << "*wp = " << *wp << endl;//error
		
		//如果要访问weak_ptr中托管的对象,必须要提升成一个shared_ptr
		shared_ptr<Point> sp2 = wp.lock();
		if(sp2){
			cout << "weak_ptr提升成功，" << endl;
			cout << "*sp2 = " << *sp2 << endl;
		}else {
			cout << "weak_ptr提升失败, 托管的对象已经被销毁" << endl;
		}
	}
	
	cout << endl;
	//weak_ptr知道其所托管对象的生命周期是否结束
	shared_ptr<Point> sp2 = wp.lock();
	if(sp2){
		cout << "weak_ptr提升成功，" << endl;
		cout << "*sp2 = " << *sp2 << endl;
	}else {
		cout << "weak_ptr提升失败, 托管的对象已经被销毁" << endl;
	}
	return 0;
}

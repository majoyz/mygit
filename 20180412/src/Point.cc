 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 15:15:12
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

	Point(int ix, int iy = 0) 
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	Point(Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout << "Point(const Point &)" << endl;
	}

	//赋值运算符函数
	//如果没有显式提供赋值运算符函数，编译器会自动提供一个
#if 0
	Point & operator=(const Point & rhs)
	{
		cout << "Point & operator=(const Point &)" << endl;
		this->_ix = rhs._ix;
		this->_iy = rhs._iy;
		return *this;
	}
#endif

	void print(/* Point * const this */) //每一个成员函数第一个参数就是隐含的this指针, this指针代表的是当前对象
	{
		//this = 0x1000H;//error
		cout << "(" << this->_ix
			 << "," << this->_iy 
			 << ")" << endl;
	}


	~Point()
	{	//做清理工作
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};


int main(void)
{
	int a = 3;
	int b = 4;
	a = b;//赋值操作, 复制

	Point pt1(1, 2);
	cout << "pt1 = ";
	pt1.print();
	Point pt2(3, 4);
	cout << "pt2 = ";
	pt2.print();
	//pt2 = pt1;//针对于自定义类类型, 运算符重载
	pt2.operator=(pt1);
	cout << "pt2 = ";
	pt2.print();
	

	return 0;
}

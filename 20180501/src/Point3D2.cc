 ///
 /// @file    Point3D.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-01 10:16:14
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	Point(int ix = 0, int iy =0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int=0,int=0)" << endl;
	}

	void print() const{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	int getY()const {	return _iy;	}

protected://protected成员的访问权限是直接开放给派生类
	int getX() const {	return _ix;	}

	int _ix;
private:
	int _iy;
};

class Point3D
: protected Point 
{
public:
	Point3D(int ix, int iy, int iz)
	: Point(ix, iy)
	, _iz(iz)
	{
		cout << "Point3D(int, int, int)" << endl;
	}

	void display() const
	{
		print();////对于基类的public成员而言,使用protected继承时，在派生类内部是protected的
		cout << "(" << _ix //对于基类的protected成员而言,使用protected继承时，在派生类内部是protected的
			 << "," << getY()//_iy //对于基类的私有成员而言，不能在派生类内部直接访问
			 << "," << _iz
			 << endl;
	}

private:
	int _iz;
};


class Point4D
: protected Point3D
{
public:
	void show()const
	{
		print();
	}
};

class Point5D
: protected Point4D
{
public:
	void func() const
	{
		print();
	}
};


 
int main(void)
{
	Point3D pt3d1(1, 2, 3);
	pt3d1.print();//error
	pt3d1.getX();//对于派生类对象而言，只能以公有继承方式访问基类的公有成员;其他情况一律不能进行访问
	pt3d1.getY();

}

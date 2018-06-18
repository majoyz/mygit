 ///
 /// @file    unique_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 16:11:01
 ///
 
#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
 
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

unique_ptr<Point> getPoint()
{
	unique_ptr<Point> up(new Point(5, 6));
	return up;
}

int main(void)
{
	unique_ptr<Point> up(new Point(1, 2));
	cout << "*up = " << *up << endl;
	cout << "up'get = " << up.get() << endl;

	//unique_ptr不能进行复制或赋值,表达的是对象语义, 独享所有权
	//unique_ptr<Point> up2(up);//error
	unique_ptr<Point> up3(new Point(3, 4));
	//up = up3;//error
	
	cout << "*up3 = " << * up3 << endl;
	up3 = getPoint();//unique_ptr具有移动语义，其内部定义了移动构造函数和移动赋值运算符函数
	cout << "*up3 = " << * up3 << endl;

	cout << endl << "将点放入容器之中:" << endl;
	vector<unique_ptr<Point>> points;
	//points.push_back(up);//error, up是左值,会进行复制
	points.push_back(std::move(up));//必须用右值的方式放入
	points.push_back(std::move(up3));

	//cout << "*up3 = " << * up3 << endl;//error, up3被托管的对象已经转移到容器之中去了, 不能直接使用
	//reset重新托管一个对象
	up.reset(new Point(10,11));

	cout << "*up = " << *up << endl;
	return 0;
}

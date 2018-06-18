 ///
 /// @file    list.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-24 10:04:11
 ///
 

#include <iostream>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;
 
int test0(void)
{
	int arr[3] = {4, 5, 6};
	list<int> liInt{1, 2, 3};
	list<int>::iterator it = liInt.begin();
	list<int>::const_iterator cit = liInt.begin();
	*it = 0;
	//*cit = 1;//error

	liInt.insert(it, arr, arr + 3);
	for(auto & number : liInt){
		cout << number << " ";
	}
	cout << endl;

	list<int>::iterator lit;
	//lit += 2;
	for(lit = liInt.begin(); lit != liInt.end(); ++lit){
		cout << *lit << " ";
	}
	cout << endl;

	//liInt.insert(cit, arr, arr + 3);
	//liInt.insert(cit, {1, 2, 3});

	return 0;
}

void test1(void)
{
	vector<int> vecInt{1, 2, 3};
	vecInt.push_back(4);
	cout << "size = " << vecInt.size() << endl;
	cout << "capacity = " << vecInt.capacity() << endl;
	vecInt.shrink_to_fit();
	cout << "size = " << vecInt.size() << endl;
	cout << "capacity = " << vecInt.capacity() << endl;
}

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{	cout << "Point(int=0,int=0)" << endl;	}

	Point(const Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout << "Point(const Point &)" << endl;
	}

	void set(int ix, int iy)
	{
		_ix = ix;
		_iy = iy;
	}

	~Point()
	{	cout << "~Point()" << endl;	}

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

void test2(void)
{
	//Point points0[10];
	vector<Point> points(10);
	Point pt1(1, 2);
	points.push_back(pt1);//放入容器中的元素都是一个全新的副本(copy)
	pt1.set(3, 4);
	for(auto & point : points){
		cout << point << " ";
	}
	cout << endl;
	cout << "pt1 = " << pt1 << endl;
}

int main(void)
{
	//test1();
	test2();
	return 0;
}

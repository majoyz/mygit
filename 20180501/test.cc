 ///
 /// @file    test.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-01 10:57:27
 ///
 
#include <iostream>
using namespace std;

class Point{
	public:
		Point(int ix,int iy)
		:_ix(ix)
		,_iy(iy)
		{cout << "Point(int ix,int iy)" << endl;}

		~Point(){
			cout << "~Point()" << endl;
		}

		void print(){
			cout << "(" << _ix << "," << _iy << ")" << endl;
		}

	private:
		int _ix;
		int _iy;
};

class Point3D:protected Point//应该相当于Point是Point3D里面的protected下的类
{
public:

	Point3D(int ix,int iy,int iz)
		:Point(ix,iy)
		,_iz(iz)
		{cout << "Point3D(int,int,int)" << endl;}
	void print3D(){
		print();
		cout << "_iz = " << _iz << endl;
	}

private:
	int _iz;
};

class Point4D:public Point3D
{
public:

	Point4D(int ix,int iy,int iz,int i)
		:Point3D(ix,iy,iz)
		,_i(i)
		{cout << "Point4D(int,int,int,int)" << endl;}
	void print4D(){
		print3D();
		cout << "_i = " << _i << endl;
		print();
	}
private:
	int _i;
};

int main(){
	Point xy(1,2);
	Point3D xyz(4,5,6);
	//xyz.print();
	Point4D xyzi(7,8,9,10);
	xyzi.print4D();
	//xyzi.print();

	return 0;
}

 ///
 /// @file    Complex.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-17 10:03:58
 ///
 
#include "Mylogger.h"
#include <iostream>
using std::cout;
using std::endl;

class Complex
{
public:
	Complex(double dreal, double dimag)
	: _dreal(dreal)
	, _dimag(dimag)
	{
		LogDebug("Complex(double, double)");
	}

	// 1 + 2 i
	// -2 + 2i
	//   2i
	//   -2i
	//  0
	//  1
	//1 - 2i

	void display() const
	{
		if(_dreal == 0 && _dimag != 0)
			cout << _dimag << "i" << endl;
		else
		{
			cout << _dreal;
			if(_dimag > 0)
				cout << "+" << _dimag << "i" << endl;
			else if(_dimag < 0)
				cout << _dimag << "i" << endl;
			else 
				cout << endl;
		}
	}

	double getReal() const {	return _dreal;	}
	double getImage() const {	return _dimag;	}
	
private:
	double _dreal;
	double _dimag;// -1 = i^2
};

//以普通函数的形式重载运算符
Complex operator+(const Complex & lhs, const Complex & rhs)
{
	return Complex(lhs.getReal() + rhs.getReal(), 
				   lhs.getImage() + rhs.getImage());
}


 
int main(void)
{
	Complex c1(1, 2);
	c1.display();

	Complex c2(-3, 4);
	c2.display();

	Complex c4(0, 2);
	c4.display();
	Complex c5(0, 0);
	c5.display();
	Complex c6(0, -1);
	c6.display();
	Complex c7(-1, -2);
	c7.display();
	cout << "执行加法:" << endl;

	int a = 3, b = 4;
	int c = a + b;
 
	Complex c3 = c1 + c2;
	c3.display();

	return 0;
}

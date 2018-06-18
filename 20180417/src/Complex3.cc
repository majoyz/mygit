 ///
 /// @file    Complex3.cc
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

	//以成员函数的形式重载运算符
	Complex operator+(const Complex & rhs)
	{
		return Complex(_dreal + rhs._dreal,
					   _dimag + rhs._dimag);
	}
private:
	double _dreal;
	double _dimag;// -1 = i^2
};



 
int main(void)
{
	Complex c1(1, 2);
	c1.display();

	Complex c2(-3, 4);
	c2.display();

	Complex c3 = c1 + c2;//Complex c3 = c1.operator+(c2)
	c3.display();

	return 0;
}

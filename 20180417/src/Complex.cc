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

	void display() const
	{
		cout << _dreal << " + " << _dimag << endl;
	}
	
private:
	double _dreal;
	double _dimag;// -1 = i^2
};

#if 0
//内置类型的运算符不能进行重载
int operator+(int x, int y)
{
	return x - y;
}
#endif

void test()
{
	//if( a = 0  && xxx )
}
 
int main(void)
{
	Complex c1(1, 2);
	c1.display();

	Complex c2(3, 4);
	c2.display();
 
	Complex c3 = c1 + c2;

	return 0;
}

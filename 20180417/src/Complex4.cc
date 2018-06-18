 ///
 /// @file    Complex4.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-17 10:03:58
 ///
 
#include "Mylogger.h"
#include <iostream>
#include <limits>
using std::cout;
using std::endl;

class Complex
{
public:
	Complex(double dreal = 0, double dimag = 0)
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

	//如果执行完操作之后，对象本身的值发生变化，建议以成员函数形式进行重载
	//
	// -= *=  /=   %=
	//
	Complex & operator+=(const Complex & rhs)
	{
		_dreal += rhs._dreal;
		_dimag += rhs._dimag;
		return *this;
	}

	//前置++, 其效率比后置更高
	Complex & operator++()
	{
		++_dreal;
		++_dimag;
		return *this;
	}
	//后置++
	Complex operator++(int) //int是为了区分前置和后置
	{
		Complex ret(*this);
		++_dreal;
		++_dimag;
		return ret;
	}

	friend Complex operator+(const Complex & lhs, const Complex & rhs);
	friend bool operator<(const Complex & lhs, const Complex & rhs);
	friend std::ostream & operator<<(std::ostream & os, const Complex & rhs);
	friend std::istream & operator>>(std::istream & is, Complex & rhs);

	//对于输入输出流运算符而言，如果以成员函数形式进行重载，第一个参数是
	//隐含的this参数，而输入输出流运算符的左操作数必须是流对象;
	//因此输入输出流运算符不能是成员函数
	//operator<<();

private:
	double _dreal;
	double _dimag;
};

//以友元函数的形式重载运算符
//
//+ - * /
//
Complex operator+(const Complex & lhs, const Complex & rhs)
{
	return Complex(lhs._dreal + rhs._dreal,
				   lhs._dimag + rhs._dimag);
}

std::ostream & operator<<(std::ostream & os, const Complex & rhs)
{
	if(rhs._dreal == 0 && rhs._dimag != 0)
		os << rhs._dimag << "i";
	else
	{
		os << rhs._dreal;
		if(rhs._dimag > 0)
			os << "+" << rhs._dimag << "i";
		else if(rhs._dimag < 0)
			os << rhs._dimag << "i";
	}
	return os;
}

void inputDouble(std::istream & is, double & value)
{
	while(is >> value, !is.eof())
	{
		if(is.bad())
		{
			LogError("istream corrupted!");
			return;
		}else if(is.fail())
		{
			is.clear();
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "pls input a double value: " << endl;
			continue;
		}
		break;
	}
}

std::istream & operator>>(std::istream & is, Complex & rhs)
{
	cout << "pls input real double value:";
	inputDouble(is, rhs._dreal);
	cout << "pls input image double value:";
	inputDouble(is, rhs._dimag);
	return is; 
} 
//自定义比较方式
//
//>  >= <=  !=  ==
//
bool operator<(const Complex & lhs, const Complex & rhs)
{
	return lhs._dreal < rhs._dreal;
}
 
//int operator+(int,int);

int main(void)
{
	Complex c1(1, 2);
	cout << c1 << endl;
	return 0;
}

int test1(void)
{
	Complex c1;
	while(std::cin >> c1)
	{
		cout << "c1 = " << c1 << endl;
	}

	return 0;
}

int test0(void)
{
	int a = 3, b = 4;
	int c = a + b;
	cout << "c = " << c << endl;

	a += b;// a = a + b

	++a;
	a++;

	Complex c1(1, 2);
	cout << "c1 = " << c1 << endl;

	Complex c2(-3, 4);
	cout << "c2 = " << c2 << endl;

	Complex c3 = c1 + c2;// Complex c3 = operator+(c1, c2)
	cout << "c3 = " << c3 << endl;
	cout << endl;

	c1 += c2;// c1.operator+=(c2) 
	cout << "c1 = " << c1 << endl;//链式编程
	// operator<<(operator<<(operator<<(cout, "c1 = "), c1), endl);
	// operator<<(cout, c1);

	cout << "前置++，表达式的值:";
	cout << (++c1) << endl;
	cout << endl;
	cout << "前置++ 之后, c1 =" << c1 << endl;

	cout << "后置++，表达式的值:";
	cout << (c1++) << endl;
	cout << "后置++ 之后, c1 =";
	cout << "c1 = " << c1 << endl;

	cout << "比较方式：" << endl;
	cout << "c1 < c2 ? " << (c1 < c2) << endl;
	return 0;
}

 ///
 /// @file    multiDerived1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-01 11:04:46
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class A
{
public:	
	void display() const
	{
		cout << "A::display() _ia = " << _ia << endl;
	}
	void setA(int ia){
		_ia = ia;
	}
private:
	int _ia;
};

class B
: virtual public A
{
public:	
	void show() const
	{
		cout << "B::show()" << endl;
	}
};

class C
: virtual public A
{
public:
#if 0
	void display() const
	{
		cout << "C::display()" << endl;
	}
#endif
};

class D 
: public B
, public C// 默认情况下是private继承
{};
 
int main(void)
{	//多基派生的二义性： 存储二义性 --> 采用虚继承
	D d;
	d.setA(10);
	d.display();
	return 0;
}

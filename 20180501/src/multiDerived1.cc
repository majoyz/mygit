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
		cout << "A::display()" << endl;
	}
};

class B
{
public:	
	void display() const
	{
		cout << "B::display()" << endl;
	}
};

class C
: public A
, public B
{
public:
#if 0
	void display() const
	{
		cout << "C::display()" << endl;
	}
#endif
};
 
int main(void)
{	//多基派生的二义性： 成员名冲突的二义性 --> 作用域限定符
	C c;
	c.A::display();
	c.B::display();
	//c.display();

	return 0;
}

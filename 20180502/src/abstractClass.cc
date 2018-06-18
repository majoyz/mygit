 ///
 /// @file    abstractClass.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:49:18
 ///
 
#include <iostream>
using std::cout;
using std::endl;


//定义了protected构造函数的类也成为抽象类
class A
{
public:
	void display() const
	{	cout << "A::display()" << endl;	}
protected:
	A(){	cout << "A()" << endl;}
};

class B
: public A
{
public:
	B(){	cout << "B()" << endl;	}
};

 
int main(void)
{
	A * pa = new B;
	pa->display();
	return 0;
}

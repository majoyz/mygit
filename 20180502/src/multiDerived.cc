 ///
 /// @file    multiDerived.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 15:14:11
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
	virtual void a(){	cout << "A::a()" << endl;	}
	virtual void b(){	cout << "A::b()" << endl;	}
	virtual void c(){	cout << "A::c()" << endl;	}
};

class B
{
public:
	virtual void a(){	cout << "B::a()" << endl;	}
	virtual void b(){	cout << "B::b()" << endl;	}
	void c(){	cout << "B::c()" << endl;	}
	void d(){	cout << "B::d()" << endl;}
};

class C
: public A
, public B
{
public:
	virtual void a(){	cout << "C::a()" << endl;	}
	void c(){	cout << "C::c()" << endl;	}
	void d(){	cout << "C::d()" << endl;}
};

 
int main(void)
{
	A a;
	B b;
	C c;
	c.a();
	//c.b();//error
	c.c();
	c.d();
	cout << endl;

	A * pA = &c;
	pA->a();
	pA->b();
	pA->c();

	cout << endl;
	B * pB = &c;
	pB->a();
	pB->b();
	pB->c();
	pB->d();
	cout << endl;
	C * pC = &c;
	pC->a();
	//pC->b();//error,二义性
	pC->c();
	pC->d();

	cout << "pA = " << pA << endl;
	cout << "pB = " << pB << endl;
	cout << "pC = " << pC << endl;

	return 0;
}

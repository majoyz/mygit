 ///
 /// @file    derived2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-01 11:22:56
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 


class Base
{
public:
	Base(){	cout << "Base()" << endl;	}
	Base(int ib): _ib(ib) {	cout << "Base(int)" << endl;	}

	void print() const
	{	cout << "Base::_ib = " << _ib << endl;	}

	~Base()
	{
		cout << "~Base()" << endl;
	}
private:
	int _ib;
};

class Derived
: public Base
{
public:
	Derived(int id)
	: Base()
	, _id(id)
	{
		cout << "Derived(int)" << endl;
	}

	Derived(int ib, int id)
	: Base(ib) 
	, _id(id)
	{
		cout << "Derived(int,int)" << endl;
	}

	void display() const
	{
		print();
		cout << "Derived::_id = " << _id << endl;
	}

	~Derived(){	cout << "~Derived()" << endl;	}
private:
	int _id;
};


int main(void)
{
	//派生类能够适应基类
	Base base(10);
	Derived d1(1, 2);
	cout << "sizeof(Base) = " << sizeof(Base) << endl;
	cout << "sizeof(Derived) = " << sizeof(Derived) << endl;

	Base base2 = base;//Base(const Base&)

	Base base3 = d1;//Base(const Base&) 把一个派生类对象赋值给基类对象

	//Derived d2 = base;//error, Derived(const Derived &)

	Base * pbase = &base;
	pbase->print();

	pbase = &d1;//把一个基类指针指向派生类对象
	pbase->print();

	cout << endl;
	Base & ref1 = base;
	ref1.print();

	Base & ref2 = d1;//把一个基类引用指向派生类对象
	ref2.print();
	cout << endl;

	Derived * pDerived = &base;//error
	Derived & ref3 = base;

	return 0;
}

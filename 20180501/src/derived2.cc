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
private:
	int _ib;
};

class Derived
: public Base
{
public:
#if 0
	Derived(int id)
	: _id(id)
	{
		cout << "Derived(int)" << endl;
	}
#endif

	void display() const
	{
		print();
		cout << "Derived::_id = " << _id << endl;
	}
private:
	int _id;
};


int main(void)
{
	Derived d;
	d.display();

	return 0;
}

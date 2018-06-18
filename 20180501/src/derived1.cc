 ///
 /// @file    derived1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-01 11:22:56
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 

class Base
{
public:
#if 1
	Base(){	cout << "Base()" << endl;	}
#endif
	void print() const
	{	cout << "Base::_ib = " << _ib << endl;	}
private:
	int _ib;
};

class Derived
: public Base
{
public:
	Derived(int id)
	: _id(id)
	{
		cout << "Derived(int)" << endl;
	}

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
	Derived d(10);
	d.display();

	return 0;
}

 ///
 /// @file    virtual1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 10:17:33
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	explicit
	Base(int ibase)
	: _ibase(ibase)
	{
		cout << "Base(int)" << endl;
	}

	void func1(){
		//动态联编,表现虚函数的特性
		this->display();
	}

	void func2(){
		Base::display();
	}

	virtual
	void display(){
		cout << "Base::display() _ibase = " << _ibase << endl;
	}
private:
	int _ibase;
};

class Derived
: public Base
{
public:
	Derived(int ibase, int iderived)
	: Base(ibase)
	, _idreived(iderived)
	{
		cout << "Derived(int,int)" << endl;
	}

	void display() {
		cout << "Derived::display() _idreived = " << _idreived << endl;
	}

	void print(){
		cout << "Derived::print()" << endl;
	}
private:
	int _idreived;
};
 
int main(void)
{
	Base base(1);
	base.func1();
	base.func2();
	cout << endl;

	Derived d1(10, 11);
	d1.func1();
	d1.func2();
	

	return 0;
}

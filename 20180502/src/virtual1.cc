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
	//通过对象名进行访问时，并不表现出多态性
	Derived d1(10, 11);
	d1.display();//静态联编，直接到代码区找相应的函数, 这种情况下是有隐藏的
	d1.Base::display();
	d1.print();

	Base & ref = d1;
	ref.display();//引用底层实现还是指针, 动态联编

	return 0;
}

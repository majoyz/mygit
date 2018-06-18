 ///
 /// @file    virtual3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:02:24
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Base1
{
public:
	Base1(){
		cout << "Base1()" << endl;
	}

	virtual
	void func1(){
		cout << "Base1::func1()" << endl;
	}
	virtual
	void func2(){
		cout << "Base1::func2()" << endl;
	}

	~Base1(){cout << "~Base1()" << endl;}
};

class Base2
: public Base1
{
public:
	//在构造函数或析构函数内调用虚函数，采用的是静态联编
	Base2(){
		cout << "Base2()" << endl;
		func1();
	}

#if 0
	virtual
	void func1(){
		cout << "Base2::func1()" << endl;
	}
	virtual
	void func2(){
		cout << "Base2::func2()" << endl;
	}
#endif

	~Base2(){
		func2();
		cout << "~Base2()" << endl;
	}
};

class Derived
: public Base2
{
public:
	Derived(){
		cout << "Derived()" << endl;
	}

	virtual
	void func1(){
		cout << "Derived::func1()" << endl;
	}
	virtual
	void func2(){
		cout << "Derived::func2()" << endl;
	}

	~Derived(){
		cout << "~Derived()" << endl;
	}
};
 
int main(void)
{
	Derived d;

	return 0;
}

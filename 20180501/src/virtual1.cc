 ///
 /// @file    virtual1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-01 16:22:41
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Base
{
public:
	//为什么构造函数不能设置为虚函数?
	//答: 虚函数的特性表现是要在对象创建完毕之后, 才能去使用虚函数
	//virtual
	Base(double dbase)
	: _dbase(dbase)
	{
		cout << "Base(double)" << endl;
	}

	virtual 
	void display() {
		cout << "Base::_dbase = " << _dbase << endl;
	}
private:
	double _dbase;
};

class Derived
: public Base
{
public:
	Derived(double d1, double d2)
	: Base(d1)
	, _dDerived(d2)
	{
		cout << "Derived(double,double)" << endl;
	}

	//当派生类中重定义了基类的虚函数时，不管在其前面有没有virtual, 
	//都是虚函数, 派生类中的相应函数会自动成为虚函数
	virtual
	void display()
	{
		cout << "Derived::display()" << endl;
	}

#if 1
	virtual 
	void display(int) {
		cout << "Derived::_dDerived = " << _dDerived << endl;
	}
#endif
private:
	double _dDerived;
};

//从编译期来看，只会调用基类的display方法
//从运行期结果来看，会调用相应对象的display方法
//
//虚函数如何实现? --> 虚表(虚函数表)
//当基类定义了虚函数之后，在其存储布局中会多一个虚函数指针, 
//该虚函数指针指向了一张虚函数表， 虚函数表中存放的是虚函数的
//入口地址
//
//虚函数的特性被激活的条件:
//1. 基类定义虚函数，派生类覆盖虚函数
//2. 创建派生类对象
//3. 用基类的指针指向派生类对象
//4. 用基类指针调用虚函数
//
void display(Base * base){
	base->display();
}

int main(void)
{
	Base base(10);
	Derived derived(1, 2);
	cout << "sizeof(Base) = " << sizeof(Base) << endl;
	cout << "sizeof(Derived) = " << sizeof(Derived) << endl;


	display(&base);
	display(&derived);

	return 0;
}

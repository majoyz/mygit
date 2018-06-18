 ///
 /// @file    pureVirtual.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:24:43
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	//定义了纯虚函数的类称为抽象类
	virtual void display()=0;//纯虚函数,只有声明，没有实现, 作为接口存在
	virtual void print()=0;
	virtual void show()=0;
};

class B
: public A
{
public:
	//如果一个派生类只实现了顶层基类的其中一个纯虚函数，该派生类也会成为抽象类
	//如果不想成为抽象类，必须要实现所有的纯虚函数
	void display(){
		cout << "B::display()" << endl;
	}
	void print(){
		cout << "B::print()" << endl;
	}

	virtual void func1(){}
};

class C
: public B
{
public:
	void show(){
		cout << "C::show()" << endl;
	}
};
 
int main(void)
{
	//A a;//抽象类不能创建对象
	A * pA = new C;
	pA->display();
	pA->print();
	pA->show();

	return 0;
}

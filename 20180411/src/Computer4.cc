 ///
 /// @file    Computer4.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 14:37:34
 ///
 
#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Computer
{
public:
	Computer(const char * brand, float price)
	: _brand(new char[strlen(brand) + 1]())
	, _price(price)
	{
		strcpy(_brand, brand);
		cout << "Computer(const char*, float)" << endl;
	}

	//系统自动提供的
#if 0
	Computer(const Computer & rhs)
	: _brand(rhs._brand) //浅拷贝
	, _price(rhs._price)
	{
		cout << "Computer(const Computer&)" << endl;
		//_brand = rhs._brand;
	}
#endif
	//1. 复制构造函数的形参不能去掉引用符号: 因为会导致无穷递归, 直到栈溢出
	//2. 复制构造函数的形参不能去掉const: 如果去掉之后，非const引用不能绑定到临时对象的
	Computer(const Computer & rhs)
	: _brand(new char[strlen(rhs._brand) +1]())
	, _price(rhs._price)
	{
		cout << "Computer(const Computer&)" << endl;
		strcpy(_brand, rhs._brand);//深拷贝
	}

	void setBrand(const char * brand);
	void setPrice(float price);

	void print()
	{
		cout << "品牌:" << _brand << endl
			 << "价格:" << _price << endl;
	}

	//在对象被销毁时，自动调用
	~Computer()
	{//清理工作
		delete [] _brand;
		cout << "~Computer()" << endl;
	}

private:
	char* _brand;
	float _price;	
};
 

void Computer::setBrand(const char * brand)
{
	::strcpy(_brand, brand);
}

void Computer::setPrice(float price)
{
	_price = price;
}

//值传递的本质就是进行复制
//
//当形参和实参都是对象，进行实参与形参的结合时会调用复制构造函数
void func1(Computer c1)
{
	c1.print();
}


//当函数的返回值就是对象时，执行return语句就会调用复制构造函数
Computer func2()
{
	cout << "func2()" << endl;
	Computer com("战神", 9000);
	com.print();
	return com;
}

int main(void)
{
	cout << "sizeof(Computer) = " << sizeof(Computer) << endl;
	Computer com1("xiaomi", 6666);
	Computer com2 = com1;//调用复制构造函数
	cout << "com1 = ";
	com1.print();
	cout << "com2 = ";
	com2.print();
	cout << endl;

	func1(com1);//Computer c1 = com1;
	cout << endl;
	//&com1;

	func2();//func2返回的对象是一个匿名对象-->临时对象-->非持久化对象
	Computer com3 = func2();// const Computer & rhs = func2();
	
	const int & ref = 10;
	cout << "ref = " << ref << endl;

	return 0;
}

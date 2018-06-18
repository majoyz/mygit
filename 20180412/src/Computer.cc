 ///
 /// @file    Computer.cc
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

#if 0
	//系统提供的， 现在不再满足Computer类的需求
	Computer & operator=(const Computer & rhs)
	{
		_brand = rhs._brand;//浅拷贝
		_price = rhs._price;
		return *this;
	}
#endif

	Computer & operator=(const Computer & rhs)
	{
		cout << "Computer & operator=(const Computer&)" << endl;
		if(this !=  &rhs) //自复制
		{
			delete [] _brand;//回收左操作数开辟的空间

			_brand = new char[strlen(rhs._brand) + 1]();//深拷贝
			strcpy(_brand, rhs._brand);
			_price = rhs._price;
		}

		return *this;
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


int main(void)
{
	Computer com1("xiaomi", 6666);
	cout << "com1: ";
	com1.print();
	cout << endl; 
	Computer com2("Mac", 8888);
	cout << "com2: ";
	com2.print();
	cout << endl; 

	Computer com3 = com1;//调用复制构造函数
	Computer com4(com1);

	com1 = com1;//自复制

	com2 = com1;//调用Computer的赋值运算符函数
	cout << "执行赋值操作:" << endl;
	cout << "com2: ";
	com2.print();


	return 0;
}

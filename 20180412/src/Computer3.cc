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
		_totalPrice += _price;
	}

	Computer(const Computer & rhs)
	: _brand(new char[strlen(rhs._brand) +1]())
	, _price(rhs._price)
	{
		cout << "Computer(const Computer&)" << endl;
		strcpy(_brand, rhs._brand);//深拷贝
	}

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

	//静态成员函数的参数之中没有隐含的this指针
	//不能直接调用非静态的数据成员和成员函数
	//
	//可以调用静态的数据成员和成员函数
	//
	static void printTotalPrice()
	{
		//print();
		//cout << "品牌:" << this->_brand << endl
		cout << "总价:" << _totalPrice << endl;
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
	static float _totalPrice;//存放的区域在全局静态区
};

//静态成员的初始化
//
//静态数据成员是整个类的所有对象共享的
float Computer::_totalPrice = 0.0;
 

void Computer::setBrand(const char * brand)
{
	::strcpy(_brand, brand);
}

void Computer::setPrice(float price)
{
	_price = price;
	//print();
}


int main(void)
{
	Computer::printTotalPrice();//不需要产生对象就可以调用静态成员函数

	Computer com1("xiaomi", 6666);
	cout << "com1: ";
	com1.print();
	//com1.printTotalPrice();
	Computer::printTotalPrice();//静态成员函数可以直接通过类名进行调用
	cout << endl; 

	Computer com2("Mac", 8888);
	com2.print();
	Computer::printTotalPrice();
	//com2.printTotalPrice();

	cout << "sizeof(Computer) = " << sizeof(Computer) << endl;


	return 0;
}

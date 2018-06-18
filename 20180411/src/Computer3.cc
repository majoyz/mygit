 ///
 /// @file    Computer3.cc
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

int test0(void)
{
	return 0;
}

Computer com2("小米", 6666);
static Computer com3("Thinkpad", 8888);

int main(void)
{
	//位于栈上，栈对象
	Computer com("战神", 9000);
	com.print();
	//com.~Computer();//析构函数可以主动调用, 一般不这样使用
	
	int * p = new int(1);

	//位于堆上，堆对象
	Computer * pc = new Computer("Macbook", 10000);
	pc->print();

	delete pc;
	delete p;

	return 0;
}

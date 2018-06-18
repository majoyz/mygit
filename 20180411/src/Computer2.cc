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

//代码风格（规范）
//
//代码写出来是给人看的
//
//


struct Person
{//默认访问权限就是public

	void setName(const string & name)
	{
		_name = name;
	}

	void setGender(bool gender)
	{
		_gender = gender;
	}

	void print()
	{
		cout << "姓名:" << _name << endl
			 << "性别:" << _gender << endl;
	}

	string _name;
	bool _gender;
};

class Computer
{//默认访问权限是private
public:// 称为类对外提供的服务或者接口
	void setBrand(const char * brand);
	void setPrice(float price);

private://体现类的封装性
	char _brand[20];// char m_brand[20];  
	float _price;	// float price_;
};
 

//类名是具有作用域的效果的
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
	Computer com;
	//com._price = 5000;//error
	com.setBrand("战神");//public区域的成员可以在类之外访问
	com.setPrice(9000);//private/protected不可以在类之外进行访问
	return 0;
}

int main(void)
{
	Person person;
	person._name = "Mike";
	person._gender = true;
	person.print();

	person.setName("Jakie");
	person.setGender(false);
	person.print();

	return 0;
}

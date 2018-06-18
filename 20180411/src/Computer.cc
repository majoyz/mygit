 ///
 /// @file    Computer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 14:37:34
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//代码风格（规范）
//
//代码写出来是给人看的
//

class Computer
{//默认访问权限是private
public:// 称为类对外提供的服务或者接口
	//在类内部实现的函数都是inline函数
	void setBrand(const char * brand)
	{
		::strcpy(_brand, brand);
	}

//protected:
	void setPrice(float price)
	{
		_price = price;
	}

private://体现类的封装性
	char _brand[20];// char m_brand[20];  
	float _price;	// float price_;
};
 
int main(void)
{
	Computer com;
	//com._price = 5000;//error
	com.setBrand("战神");//public区域的成员可以在类之外访问
	com.setPrice(9000);//private/protected不可以在类之外进行访问

	return 0;
}

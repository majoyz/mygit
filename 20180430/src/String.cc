 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 11:38:35
 ///
 
#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


class String
{
public:
	String(): _pstr(new char[1]()){
		cout << "String()" << endl;
	}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
		cout << "String(const char *)" << endl;
	}

	//复制构造函数的参数无法判断传递过来的实参是左值还是右值
	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr + 1)]())
	{
		strcpy(_pstr, rhs._pstr);
		cout << "String(const String &)"<< endl;
	}
	//定义了移动构造函数和移动赋值运算符函数的类，称其为具有移动语义的类

	//移动构造函数
	String(String && rhs) // 右值引用的诞生就意味着修改
	: _pstr(rhs._pstr)
	{
		rhs._pstr = NULL;
		cout << "String(String&&)" << endl;
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String&)" << endl;
		if(this != & rhs){
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	//移动赋值运算符函数
	String & operator=(String && rhs)
	{	//这里的右值引用本身已经成为了左值
		cout <<"String & operator=(String &&)" << endl;
		if(this != &rhs)
		{
			delete [] _pstr;
			_pstr = rhs._pstr;
			rhs._pstr = NULL;
		}
		return *this;
	}


	~String()
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}

	friend std::ostream & operator<<(std::ostream & os, const String & rhs);
private:
	char * _pstr;
};
 
std::ostream & operator<<(std::ostream & os, const String & rhs)
{
	os << rhs._pstr;
	return os;
}


String && getString(){
	return String("hello");
}

int main(void)
{	// 右值引用本身是左值还是右值，取决于其有没有名字
	getString();//右值
	String && ref1 = getString();//ref1 左值
}

int test0(void)
{
	vector<String> vecStr;
	vecStr.push_back("hello");
	cout << "vecStr[0] = " << vecStr[0] << endl;

	String s1("hello");
	s1 = String("wangdao");
	cout << "s1 = " << s1 << endl;
	cout << endl;

	String s2("world");
	cout << "移动s1之后：" << endl;
	s2 = std::move(s1);//std::move就是显式将一个左值转换成一个右值, 之后原来的左值不能再正常使用
					   //std::move本质上来说就是一个强制转换
	//cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;

	//s2 = std::move(s2);

	return 0;
}

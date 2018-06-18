 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 09:42:53
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class String
{
public:
	String()
	//: _pstr(NULL)
	: _pstr(new char[1]())
	{
		//_pstr[0] = '\0';
		cout << "String()" << endl;
	}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
		cout << "String(const char *) " << endl;
	}

	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr, rhs._pstr);
		cout << "String(const String &)" << endl;
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		//自复制
		if(this != &rhs)
		{
			//回收左操作数的空间
			delete [] _pstr;
			//深拷贝
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}


	void print() const
	{
			cout << _pstr << endl;//cout 如果直接输出空指针，程序直接崩溃
	}


	~String()
	{
		cout << "~String()" << endl;
		delete [] _pstr;
	}
	
private:
	char * _pstr;
};
 
int main(void)
{
	String s1;
	s1.print();

	String s2("hello");
	s2.print();
	cout << endl;

	s1 = s2;
	s1.print();

	cout << endl;
	String s3 = s2;
	s3.print();

	String s4("world");
	s2 = s4;
	s2.print();

	return 0;
}

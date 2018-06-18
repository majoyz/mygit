 ///
 /// @file    COWString.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-19 11:29:34
 ///
 
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class String
{
public:
	String();
	String(const char *);
	String(const String & rhs);
	String & operator=(const String & rhs);
	~String();

	const char & operator[](size_t idx) const{	return _pstr[idx];	}
	char & operator[](size_t idx);

	size_t size(){	return strlen(_pstr);}
	const char * c_str() const {	return _pstr;	}

	size_t refcount() const
	{	return ((int*)(_pstr - 4))[0]; }

	friend std::ostream & operator<<(std::ostream & os, const String & rhs);
private:
	void initRefcount()
	{	((int*) (_pstr - 4))[0] = 1;
		//int * pInt = reinterpret_cast<int *>(_pstr - 4);
		//int * pInt = (int *)(_pstr - 4);
		//*pInt = 1;
		//pInt[0] = 1;
	}

	void increaseRefcount()
	{	
		++(((int*)(_pstr - 4))[0]); 
		//char * pRef =  _pstr - 4;
		//int * pInt = (int *) pRef;
		//++(*pInt);
	}

	void decreaseRefcount()
	{	
		--(((int*)(_pstr - 4))[0]); 
		//char * pRef =  _pstr - 4;
		//int * pInt = (int *) pRef;
		//--(*pInt);
	}

	void release()
	{
		decreaseRefcount();
		if(refcount() == 0)
		{
			delete [] (_pstr - 4);
			cout << "release data" << endl;
		}
	}
private:
	char * _pstr;
};

std::ostream & operator<<(std::ostream & os, const String & rhs)
{
	os << rhs._pstr;
	return os;
}
String::String()
: _pstr(new char[5]())
{
	cout << "String()" << endl;
	//*(int*)_pstr = 1;
	//((int *) _pstr)[0] = 1;
	_pstr += 4;
	initRefcount();
}

String::String(const char * pstr)
: _pstr(new char[strlen(pstr) + 5]())
{
	cout << "String(const char *) " << endl;
	_pstr += 4;
	initRefcount();
	strcpy(_pstr, pstr);
}

String::String(const String & rhs)
: _pstr(rhs._pstr)
{
	increaseRefcount();
}

String & String::operator=(const String & rhs)
{
	if(this != &rhs)
	{
		release();//先释放左操作数开辟的空间
		_pstr = rhs._pstr;
		increaseRefcount();
	}
	return *this;
}

String::~String()
{
	release();
	cout << "~String()" << endl;
}

//下标访问运算符无法区分出是读操作还是写操作
char & String::operator[](size_t idx)
{
	if(refcount() > 1)
	{
		decreaseRefcount();
		//深拷贝
		char * ptmp = new char[size() + 5]();
		strcpy(ptmp + 4, _pstr);
		_pstr = ptmp + 4;
		initRefcount();
	}
	return _pstr[idx];
}

int main(void)
{
#if 0
	String s1;
	String s2(s1);
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << endl;
#endif

	String s3("hello,world");
	String s4(s3);
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());

	String s5("wangdao");
	cout << "s5 = " << s5 << endl;
	cout << endl << "执行s5 = s3 " << endl;
	s5 = s3;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	//s3 = s5;
	s5[0] = 'X';
	cout << endl << "执行写操作 s5[0]=‘X’ 之后:" << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	cout << endl <<"执行读操作s4[0] = " << s4[0] << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());


	return 0;
}

 ///
 /// @file    myString.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-11 20:16:20
 ///
 
#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::endl;
using std::string;

class String{
	public:
		String()
		:_pstr(new char[1]())
		{
			*_pstr=0;
			cout<<"String()"<<endl;
		}

		String(const char *pstr)
		:_pstr(new char[strlen(pstr)+1]())
		{
			::strcpy(_pstr,pstr);
			cout<<"String(const char *)"<<endl;
		}

		String(const String & rhs)
		:_pstr(new char[strlen(rhs._pstr)+1]())
		{
			::strcpy(_pstr,rhs._pstr);
			cout<<"const String & rhs"<<endl;
		}

		String & operator=(const String & rhs)
		{
			_pstr=rhs._pstr;
			cout<<"String & operator"<<endl;
			return(*this);
		}
		
		~String(){
			delete [] _pstr;
			cout<<"~String"<<endl;
		}

		void print(){
			cout<<"I'm "<<_pstr<<endl;
		}

	private:
		char * _pstr;
};

int main(){
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4 = str3;
	str4.print();

	String str5;
	str5 = str2;
	str5.print();

	return 0;
}

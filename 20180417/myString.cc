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
		String()//无参构造函数
			:_pstr(new char[1]())
		{
			*_pstr=0;
			cout<<"String()"<<endl;
		}

		String(const char *pstr)//构造函数
			:_pstr(new char[strlen(pstr)+1]())
		{
			::strcpy(_pstr,pstr);
			cout<<"String(const char *)"<<endl;
		}

		String(const String & rhs)//复制构造函数
			:_pstr(new char[strlen(rhs._pstr)+1]())
		{
			::strcpy(_pstr,rhs._pstr);
			cout<<"const String & rhs"<<endl;
		}

		~String(){//析构函数
			delete [] _pstr;
			cout<<"~String"<<endl;
		}

		String & operator=(const String & rhs)//赋值运算符重载
		{
			if(this != &rhs){
				delete [] _pstr;
				_pstr = new char[strlen(rhs._pstr) + 1]();
				strcpy(_pstr,rhs._pstr);
			}
			cout<<"String & operator=(const String & rhs)"<<endl;
			return(*this);
		}

		String & operator=(const char * rhs){//赋值运算符重载
			if(_pstr != rhs){
				delete [] _pstr;
				_pstr = new char[strlen(rhs)+1]();
				strcpy(_pstr,rhs);
			}
			cout<<"String & operator=(const char * rhs)"<<endl;
			return(*this);
		}

		String & operator+=(const String & rhs){//+=重载
			std::size_t tmpn = size();
			char tmpc[tmpn];
			strcpy(tmpc,_pstr);
			delete [] _pstr;
			_pstr = new char[tmpn + strlen(rhs._pstr) + 1]();
			strcpy(_pstr,tmpc);
			strcat(_pstr,rhs._pstr);
			cout<<"String & operator+=(const String & rhs)"<<endl;
			return(*this);
		}

		String & operator+=(const char *rhs){//+=重载
			std::size_t tmpn = size();
			char tmpc[tmpn];
			strcpy(tmpc,_pstr);
			delete [] _pstr;
			_pstr = new char[tmpn + strlen(rhs) + 1]();
			strcpy(_pstr,tmpc);
			strcat(_pstr,rhs);
			cout << "String & operator+=(const char *rhs)" << endl;
			return(*this);
		}

		char & operator[](std::size_t index){//[]重载
			cout << "char & operator[](std::size_t index)" << endl;
			if(index < size()){
				return _pstr[index];
			}else{
				static char nullchar = '\0';
				return nullchar;
			}
		}

		const char & operator[](std::size_t index) const{//[]重载
			cout << "const char & operator[](std::size_t index) const" << endl;
			if(index < size()){
				return _pstr[index];
			}else{
				static char nullchar = '\0';
				return nullchar;
			}
		}

		std::size_t size() const{//size函数
			return strlen(_pstr);
		}
		const char * c_str() const{//c_str函数
			return _pstr;
		}

		friend bool operator==(const String &, const String &);
		friend bool operator!=(const String &, const String &);

		friend bool operator<(const String &, const String &);
		friend bool operator>(const String &, const String &);
		friend bool operator<=(const String &, const String &);
		friend bool operator>=(const String &, const String &);

		friend std::ostream &operator<<(std::ostream &os,const String &s);
		friend std::istream &operator>>(std::istream &is,String &s);

		void print(){//打印函数
			cout<<_pstr<<endl;
		}

	private:
		char * _pstr;
};

bool operator==(const String & lhs,const String & rhs){//==
	if(!strcmp(lhs._pstr,rhs._pstr)){
		return true;
	}else{
		return false;
	}
}

bool operator!=(const String & lhs,const String & rhs){//!=
	if(strcmp(lhs._pstr,rhs._pstr)){
		return true;
	}else{
		return false;
	}
}

bool operator<(const String & lhs,const String & rhs){
	std::size_t i = 0; 
	while(1){
		if(lhs._pstr[i]<rhs._pstr[i]){
			return true;
		}else if(lhs._pstr[i]==rhs._pstr[i]){
			if(lhs._pstr[i]==0){
				return false;
			}
			++i;
		}else{
			return false;
		}
	}
}

bool operator>(const String & lhs,const String & rhs){
	std::size_t i = 0; 
	while(1){
		if(lhs._pstr[i]>rhs._pstr[i]){
			return true;
		}else if(lhs._pstr[i]==rhs._pstr[i]){
			if(lhs._pstr[i]==0){
				return false;
			}
			++i;
		}else{
			return false;
		}
	}
}

bool operator<=(const String & lhs,const String & rhs){
	std::size_t i = 0; 
	while(1){
		if(lhs._pstr[i]<rhs._pstr[i]){
			return true;
		}else if(lhs._pstr[i]==rhs._pstr[i]){
			if(lhs._pstr[i]==0){
				return true;
			}
			++i;
		}else{
			return false;
		}
	}
}

bool operator>=(const String & lhs,const String & rhs){
	std::size_t i = 0; 
	while(1){
		if(lhs._pstr[i]>rhs._pstr[i]){
			return true;
		}else if(lhs._pstr[i]==rhs._pstr[i]){
			if(lhs._pstr[i]==0){
				return true;
			}
			++i;
		}else{
			return false;
		}
	}
}

std::ostream &operator<<(std::ostream &os,const String &s){
	os << s._pstr;
	return os;
}

std::istream &operator>>(std::istream &is, String &s){
	is >> s._pstr;
	return is;
}

String operator+(const String & lhs, const String & rhs){
	String tmp;
	tmp += lhs;
	tmp += rhs;
	return tmp;
}

String operator+(const String & lhs, const char * rhs){
	String tmp;
	tmp += lhs;
	tmp += rhs;
	return tmp;
}

String operator+(const char * lhs, const String & rhs){
	String tmp;
	tmp += lhs;
	tmp += rhs;
	return tmp;
}

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
	str5 = "Can you see str5?";
	str5.print();
	str5 = str2;
	str5.print();

	String str6 = "one";
	String str7 = "two";
	str6 += str7;
	str6.print();
	str7 += "three";
	str7.print();

	String str8 = "test []";
	int j = 0;
	while(str8[j]){
		cout << str8[j++];
	}
	cout << endl;

	String str66 = str6;
	String str77 = str7;
	if(str6 == str66)
		cout << "== right" << endl;
	if(str6 == str7)
		cout << "== wrong" << endl;
	if(str6 < str7)
		cout << "< right" << endl;
	else
		cout << "< wrong" << endl;
	if(str77 > str66)
		cout << "> right" << endl;
	else
		cout << "> wrong" << endl;
	if(str6 <= str6)
		cout << "<= right" << endl;
	else
		cout << "<= wrong" << endl;

	String str9;
	str9 = str6 + str7;
	str9.print();
	str9 = str7 + "three";
	str9.print();
	str9 = "one" + str7;
	str9.print();

	return 0;
}

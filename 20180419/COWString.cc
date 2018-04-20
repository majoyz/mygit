///
/// @file    COWString.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-11 20:16:20
///

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::endl;
using std::string;

class String{
	public:
		class MyChar{
			public:
				MyChar(String & cstring,size_t cindex)
					:_cstring(cstring)
					 ,_cindex(cindex)
				{
					cout << "MyChar(String & cstring,size_t cindex)" << endl;
				}

				MyChar & operator=(const char & c){
					cout << "MyChar & operator=(const cahr & c)" << endl;
					if(_cindex < _cstring.size()){
						if(_cstring.refcount() > 1){
							--((int *)(_cstring._pstr - 4))[0];
							char * ptmp = new char[_cstring.size() + 5]();
							((int *)ptmp)[0] = 1;
							ptmp += 4;
							strcpy(ptmp,_cstring._pstr);
							_cstring._pstr = ptmp;
							_cstring._pstr[_cindex] = c;
						}
						return *this;
					}else{
						static MyChar nullchar(_cstring,0);
						return nullchar;
					}
				}

				operator char(){
					return _cstring._pstr[_cindex];
				}

			private:
				String & _cstring;
				size_t _cindex;
		};
	public:
		String()//无参构造函数
			:_pstr(new char[5]())
		{
			((int *)_pstr)[0] = 1;
			_pstr += 4;
			cout<<"String()"<<endl;
		}

		String(const char *pstr)//构造函数
			:_pstr(new char[strlen(pstr)+5]())
		{
			((int *)_pstr)[0] = 1;
			_pstr += 4;
			::strcpy(_pstr,pstr);
			cout<<"String(const char *)"<<endl;
		}

		String(const String & rhs)//复制构造函数
		{
			cout<<"const String & rhs"<<endl;
			_pstr = rhs._pstr;
			++((int *)(_pstr - 4))[0];
		}

		~String(){//析构函数
			if(--((int *)(_pstr - 4))[0] == 0){
				delete [] (_pstr - 4);
			}
			cout<<"~String"<<endl;
		}

		String & operator=(const String & rhs)//赋值运算符重载
		{
			cout<<"String & operator=(const String & rhs)"<<endl;
			if(this != &rhs){
				if(--((int *)(_pstr - 4))[0] == 0){
					delete [] (_pstr - 4);
				}
				_pstr = new char[strlen(rhs._pstr) + 5]();
				_pstr = rhs._pstr;
				++((int *)(_pstr - 4))[0];
			}
			return(*this);
		}

		String & operator=(const char * rhs){//赋值运算符重载
			if(_pstr != rhs){
				delete [] (_pstr - 4);
				_pstr = new char[strlen(rhs)+5]();
				((int *)_pstr)[0] = 1;
				_pstr += 4;
				strcpy(_pstr,rhs);
			}
			cout<<"String & operator=(const char * rhs)"<<endl;
			return(*this);
		}
#if 0
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
#endif
		MyChar operator[](std::size_t index){
			cout << "MyChar & operator[](std::size_t index)" << endl;
			return MyChar(*this,index);
		}
#if 0
		char & operator[](std::size_t index){//[]重载
			cout << "char & operator[](std::size_t index)" << endl;
			if(index < size()){
				return _pstr[index];
			}else{
				static char nullchar = '\0';
				return nullchar;
			}
		}
#endif
		std::size_t size() const{//size函数
			return strlen(_pstr);
		}
		std::size_t refcount() const{
			return ((int *)(_pstr - 4))[0];
		}
		const char * c_str() const{//c_str函数
			return _pstr;
		}
#if 0
		friend bool operator==(const String &, const String &);
		friend bool operator!=(const String &, const String &);

		friend bool operator<(const String &, const String &);
		friend bool operator>(const String &, const String &);
		friend bool operator<=(const String &, const String &);
		friend bool operator>=(const String &, const String &);
#endif
		friend std::ostream &operator<<(std::ostream &os,const String &s);
		friend std::istream &operator>>(std::istream &is,String &s);

		void print(){//打印函数
			cout<<_pstr<<endl;
		}

	private:
		char * _pstr;
};
#if 0
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
#endif
std::ostream &operator<<(std::ostream &os,const String &s){
	os << s._pstr;
	return os;
}

std::istream &operator>>(std::istream &is, String &s){
	is >> s._pstr;
	return is;
}

int main(){
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;

	String str4 = str3;
	str4.print();
	cout << "str4's refcount = " << str4.refcount() << endl;

	String str5;
	str5 = "Can you see str5?";
	str5.print();
	cout << "str5's refcount = " << str5.refcount() << endl;
	str5 = str2;
	str5.print();
	cout << "str5's refcount = " << str5.refcount() << endl;

	String str6 = "test read/write[]";
	String str7 = str6;
	cout << "str6's refcount = " << str6.refcount() << endl;
	cout << "str7's refcount = " << str7.refcount() << endl;
	cout << "str6 = " << str6 << endl;
	cout << "str7 = " << str7 << endl;
	printf("str6's address = %p\n",str6.c_str());
	printf("str7's address = %p\n",str7.c_str());

	cout << endl << "after read str7[0] == " << str7[0] << endl << endl;
	cout << "str6's refcount = " << str6.refcount() << endl;
	cout << "str7's refcount = " << str7.refcount() << endl;
	cout << "str6 = " << str6 << endl;
	cout << "str7 = " << str7 << endl;
	printf("str6's address = %p\n",str6.c_str());
	printf("str7's address = %p\n",str7.c_str());

	str7[0] = 'T';
	cout << endl << "after write []" << endl << endl;
	cout << "str6's refcount = " << str6.refcount() << endl;
	cout << "str7's refcount = " << str7.refcount() << endl;
	cout << "str6 = " << str6 << endl;
	cout << "str7 = " << str7 << endl;
	printf("str6's address = %p\n",str6.c_str());
	printf("str7's address = %p\n",str7.c_str());

	return 0;
}

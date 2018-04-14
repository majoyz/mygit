 ///
 /// @file    stackonly.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-13 19:09:27
 ///
 
#include <iostream>
#include <string.h>
#include <stdlib.h>
using std::cout;
using std::endl;

class Phone{
	public:
		Phone(const char * name,int price)
		:_name(new char[strlen(name)+1]())
		,_price(price)
		{
			strcpy(_name,name);
			cout << "Phone(char *,int)" << endl;
		}

		void print() const
		{
			cout << _name << "'s price is " << _price <<endl;
		}

		~Phone(){
			cout << "~Phone()" << endl;
			delete [] _name;
		}

	private:
		void * operator new(size_t size);
		void operator delete(void * ret);
	private:
		char * _name;
		int _price;
};

int main(){
	Phone phone1("iphone",8388);
	phone1.print();

	Phone phone2("xiaomi",2499);
	phone2.print();

	Phone phone3("huawei",13888);
	phone3.print();

	return 0;
}

 ///
 /// @file    heaponly.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-13 20:20:27
 ///

#include <string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Phone{
	public:
		Phone(const char * name,int price)
		: _name(new char[strlen(name +1)]())
		, _price(price)
		{
			strcpy(_name,name);
			cout << "Phone(const char *,int)" << endl;
		}

		void print(){
			cout << _name <<"'s price is " << _price << endl;
		}

		void destroy(){
			delete this;
		}

	private:
		~Phone(){
			delete [] _name;
			cout << "~Phone()" << endl;
		}

		char * _name;
		int _price;
};

int main(){
	Phone * myphone = new Phone("iphone",4000);
	myphone -> print();
	myphone -> destroy();

	return 0;
}

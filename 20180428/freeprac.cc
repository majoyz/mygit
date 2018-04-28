 ///
 /// @file    freeprac.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-28 16:31:20
 ///
 
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Major{
	public:
		Major(string name,int age)
		:_name(name)
		,_age(age)
		{
			cout << "Major(...)" << endl;
		}

		~Major()
		{
			cout << "~Major()" << endl;
		}

		void print(){
			cout << "Name: " << _name << endl
				 << "Age: " << _age << endl;
		}
	private:
		string _name;
		int _age;
};

int main(){
	cout << "今天主要讲了std空间配置器的源码" << endl;
	cout << "没什么作业，自由练习" << endl;
	
	Major majoy("zmj",23);
	majoy.print();

	return 0;
}

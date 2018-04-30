 ///
 /// @file    auto_ptr.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-30 16:02:07
 ///
 
#include <iostream>
#include <memory>
using namespace std;

class Child;
class Parent{
	public:
		Parent(){}
		~Parent(){}

		shared_ptr<Child> _childPtr;
};

class Child{
public:
	Child(){}
	~Child(){}

	shared_ptr<Parent> _parentPtr;
};

int main(){
	//auto_ptr已经不用了
	unique_ptr<int> up(new int(77));//不能进行复制或赋值
	//具有移动语义，内部定义了移动构造函数和移动赋值运算符函数
	cout << "up = " << *up << endl;
	cout << "up.get() = " << up.get() << endl;

	return 0;
}

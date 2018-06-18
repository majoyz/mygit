 ///
 /// @file    shared_ptr2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 16:40:49
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;//强引用智能指针
using std::weak_ptr;//若引用智能指针

class Child;
class Parent
{
public:
	Parent(){	cout << "Parent()" << endl;	}
	~Parent() {	cout << "~Parent()" << endl;}

	shared_ptr<Child> _childPtr;
};

class Child
{
public:
	Child(){	cout << "Child()" << endl;	}
	~Child(){	cout << "~Child()" << endl;	}

	weak_ptr<Parent> _parentPtr;
};


int main(void)
{
	//shared_ptr的循环引用会导致内存泄漏
	//使用weak_ptr会打破循环引用,可以解决shared_ptr的问题
	shared_ptr<Parent> pParent(new Parent());
	shared_ptr<Child> pChild(new Child());

	cout << "pParent ' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;

	pParent->_childPtr = pChild;//shared_ptr = shared_ptr
	pChild->_parentPtr = pParent;//weak_ptr = shared_ptr
	cout << "pParent ' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;

	return 0;
}

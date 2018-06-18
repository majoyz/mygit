 ///
 /// @file    shared_ptr2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 16:40:49
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

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

	shared_ptr<Parent> _parentPtr;
};


int main(void)
{
	//shared_ptr的循环引用会导致内存泄漏
	shared_ptr<Parent> pParent(new Parent());
	shared_ptr<Child> pChild(new Child());

	cout << "pParent ' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;

	pParent->_childPtr = pChild;
	pChild->_parentPtr = pParent;
	cout << "pParent ' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;

	return 0;
}

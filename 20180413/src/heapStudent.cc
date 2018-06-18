 ///
 /// @file    Student.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-13 10:21:35
 ///
 
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Student
{
public:
	Student(double id, const char * name)
	: _id(id)
	, _name(new char[strlen(name) + 1]())
	{
		strcpy(_name, name);
		cout << "Student(int, const char *)" << endl;
	}

	void print() const
	{
		cout << "id: " << _id << endl
			 << "name:" << _name << endl;
	}
	
	void destroy()
	{
		//this->~Student();
		delete this;
	}

private:
	~Student()
	{
		cout << "~Student()" << endl;
		delete [] _name;
	}

private:
	double _id;
	char * _name;
};


 
int main(void)
{
	cout << "sizeof(Student) = " << sizeof(Student) << endl;
	Student * pstu = new Student(1001, "Jackie");//要求构造函数是public的
	pstu->print();
	pstu->destroy();
	
	//error  希望该语句运行时会发生编译错误
	//Student stu(1002, "Lucy");//error, 创建栈对象，同时要求构造函数和析构函数都是public的
	//stu.print();

	//delete pstu;//error
	return 0;
}

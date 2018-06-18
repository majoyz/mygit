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

	~Student()
	{
		cout << "~Student()" << endl;
		delete [] _name;
	}

private:
//只能生成栈对象
	void * operator new(size_t sz) ;
	void operator delete(void * ret);
private:
	double _id;
	char * _name;
};


 
int main(void)
{
	cout << "sizeof(Student) = " << sizeof(Student) << endl;
	//Student * pstu = new Student(1001, "Jackie");//error  希望该语句运行时会发生编译错误
	//pstu->print();

	Student stu(1002, "Lucy");//创建栈对象，同时要求构造函数和析构函数都是public的
	stu.print();

	//delete pstu;
	return 0;
}

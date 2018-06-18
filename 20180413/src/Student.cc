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

	//sz如何传递, 是由系统完成
	void * operator new(size_t sz)
	{ // operator new就是一个自定义开辟内存方式的接口
		cout << "void * operator new(size_t sz)" << endl;
		void * ret = malloc(sz);
		return ret;
	}

	void operator delete(void * ret)
	{
		cout << "void operator delete(void *)" << endl;
		free(ret);
	}

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
	Student * pstu = new Student(1001, "Jackie");
	pstu->print();

	delete pstu;
	return 0;
}

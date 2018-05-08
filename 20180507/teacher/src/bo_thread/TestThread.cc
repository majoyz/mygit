 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 09:54:43
 ///
 
#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

struct Task
{
	void getNumber(void)
	{
		::srand(::time(NULL));
		int cnt = 10;
		while(cnt--)
		{

			int number = ::rand() % 100;
			cout << "> " << pthread_self() << ":number = " << number << endl;
			::sleep(1);
		}
	}
};

void getNumber(void)
{
	::srand(::time(NULL));
	int cnt = 10;
	while(cnt--)
	{

		int number = ::rand() % 100;
		cout << "> " << pthread_self() << ":number = " << number << endl;
		::sleep(1);
	}
}

int main(void)
{
	cout << "main " << pthread_self() << endl;

	//Task task;

	//wd::Thread thread(std::bind(&Task::getNumber, &task));
	wd::Thread thread(getNumber);

	thread.start();//开启子线程

	thread.join();

	return 0;
}

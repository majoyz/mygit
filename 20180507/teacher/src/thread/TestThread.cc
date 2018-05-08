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

class MyThread
: public wd::Thread
{
public:
	~MyThread(){	cout << "~MyThread()" << endl;	}

private:
	void run()
	{
		//cout << " MyThread::run()" << endl;
		
		::srand(::time(NULL));
		int cnt = 10;
		while(cnt--)
		{

			int number = ::rand() % 100;
			cout << "> " << pthread_self() << ":number = " << number << endl;
			::sleep(1);
		}
	}
private:
	double _d;
};

int main(void)
{
	unique_ptr<wd::Thread> pThread(new MyThread);
	cout << "main " << pthread_self() << endl;

	pThread->start();//开启子线程

	pThread->join();

	return 0;
}

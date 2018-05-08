 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 09:54:43
 ///
 
#include "Thread.h"
#include "TaskQueue.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Producer
: public wd::Thread
{
public:
	Producer(wd::TaskQueue & taskque)
	: _taskque(taskque)
	{
	
	}
	~Producer(){	cout << "~Producer()" << endl;	}

private:
	void run()
	{
		::srand(::time(NULL));
		int cnt = 20;
		while(cnt--)
		{
			int number = ::rand() % 100;
			cout << "> " << pthread_self() << "produce a number = " << number << endl;
			_taskque.push(number);
			::sleep(1);
		}
	}

private:
	wd::TaskQueue & _taskque;
};

class Consumer
: public wd::Thread
{
public:
	Consumer(wd::TaskQueue & taskque)
	: _taskque(taskque)
	{}

	void run()
	{
		while(true)
		{
			int number = _taskque.pop();
			cout << pthread_self() << " consume a number : " << number <<endl;
			::sleep(2);
		}
	}

private:
	wd::TaskQueue & _taskque;
};

int test0(void)
{
	return 0;
}

#if 0
void test1(void)
{

	MyThread thread1;
	MyThread thread2;
	thread2 = thread1;
}
#endif

int main(void)
{
	wd::TaskQueue queue(10);

	unique_ptr<wd::Thread> pProducer(new Producer(queue));
	unique_ptr<wd::Thread> pConsumer(new Consumer(queue));

	pProducer->start();
	pConsumer->start();
	pProducer->join();
	pConsumer->join();

	return 0;
}

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
{
public:
	void produce(wd::TaskQueue & taskque)
	{
		::srand(::time(NULL));
		//int cnt = 20;
		///while(cnt--)
		while(true)
		{
			int number = ::rand() % 100;
			cout << "> " << pthread_self() << " produce a number = " << number << endl;
			taskque.push(number);
			::sleep(1);
		}
	}
};

class Consumer
{
public:
	void consume(wd::TaskQueue & taskque)
	{
		while(true)
		{
			int number = taskque.pop();
			cout << pthread_self() << " consume a number : " << number <<endl;
			::sleep(2);
		}
	}
};


int main(void)
{
	wd::TaskQueue queue(10);



	Producer producer;
	Consumer consumer;

	wd::Thread producerThread(std::bind(&Producer::produce, &producer, std::ref(queue)));
	//bind是值传递，而queue不能复制，要用ref包装引用
	wd::Thread consumerThread(std::bind(&Consumer::consume, &consumer, std::ref(queue)));

	producerThread.start();
	consumerThread.start();

	producerThread.join();
	consumerThread.join();

	return 0;
}

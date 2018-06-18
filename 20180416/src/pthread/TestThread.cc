 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 16:21:44
 ///
 
#include "MutexLock.h"
#include "Condition.h"

#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl; 

MutexLock mutex;
//MutexLock mutex2(mutex);//error 对于系统资源，不能进行复制, 表达的是对象语义
Condition cond(mutex);
int count = 0;
int flag = true;

void * func1(void * arg)
{
	int number = 10;
	while(number--)
	{
		MutexLockGuard autolock(mutex);//利用栈对象被销毁时会自动调用析构函数去解锁
		//mutex.lock();
		if(flag)
		{
			cond.wait();
		}

		//.... exit
		//flag 是false时候，执行加1
		++count;
		cout << "> " << pthread_self() << " count = " << count << endl;
		sleep(1);
		if(flag == false)
		{
			flag = true;
			cond.notify();
		}
		//mutex.unlock();
	}
	return NULL;
}

void * func2(void * arg)
{
	int number = 10;
	while(number--)
	{
		MutexLockGuard autoLock(mutex);
		//mutex.lock();
		if(!flag)
		{
			cond.wait();
		}
		
		//flag 为true时，执行加1
		++count;
		cout << "> " << pthread_self() << " count = " << count << endl;
		sleep(1);
		if(flag == true)
		{
			flag = false;
			cond.notify();
		}
		//mutex.unlock();
	}

	return NULL;
}
 
int main(void)
{
	pthread_t pthid1, pthid2;
	pthread_create(&pthid1, NULL, func1, NULL);
	pthread_create(&pthid2, NULL, func2, NULL);

	pthread_join(pthid1, NULL);
	pthread_join(pthid2, NULL);
	
	return 0;
}

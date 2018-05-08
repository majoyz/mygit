 ///
 /// @file    WorkerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-19 11:41:29
 ///
 
#ifndef __WD_WORKDERTHREAD_H__
#define __WD_WORKDERTHREAD_H__
 
#include "Thread.h"
#include "Threadpool.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{


class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{
		std::cout << "WorkerThread()" << std::endl;
	}

	~WorkerThread()
	{	std::cout << "~WorkerThread()" << std::endl;	}

private:
	void run()
	{
		_threadpool.threadFunc();
	}
private:
	Threadpool & _threadpool;
};

}//end of namespace wd

#endif

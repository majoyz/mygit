 ///
 /// @file    WorkerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 15:54:59
 ///
 
#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__
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
		cout << "WorkerThread()" << endl;
	}

	~WorkerThread()
	{	cout << "~WorkerThread()" << endl;	}
private:
	void run(){
		_threadpool.threadFunc();
	}

	Threadpool & _threadpool;
};


}


#endif

 ///
 /// @file    WorkerThread.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 23:10:59
 ///

#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__
#include "Thread.h"
#include "Threadpool.h"
#include <iostream>
using std::cout;
using std::endl;
namespace wd{
	class WorkerThread
	:public Thread
	{
		public:
			WorkerThread(Threadpool & threadpool)
			:_threadpool(threadpool)
			{
				cout << "WorkerThead(Threadpool & threadpool)" << endl;
			}

			~WorkerThread(){
				cout << "~WorkerThead()" << endl;
			}
		private:
			void run(){
				_threadpool.threadFunc();
			}
		private:
			Threadpool & _threadpool;
	};
}

#endif

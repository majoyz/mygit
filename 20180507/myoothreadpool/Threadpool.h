 ///
 /// @file    Threadpool.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 22:54:20
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__
#include "TaskQueue.h"
#include <vector>
#include <memory>
using std::unique_ptr;
using std::vector;

namespace wd{
class Task{
	virtual void process() = 0;
};

class Thread;
class WorkerThread;
class Threadpool{
	friend WorkerThread;
	public:
		Threadpool(size_t,size_t);
		~Threadpool();
		void start();
		void stop();
		void addTask(Task*);
	private:
		Task * getTask();
		void threadFunc();
	private:
		size_t _threadNum;
		size_t _queSize;
		vector<unique_ptr<Thread>> _threads;
		TaskQueue _taskQue;
		bool _isExit;
};
}
#endif

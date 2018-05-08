 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-19 11:37:05
 ///
 
#include "Threadpool.h"
#include "WorkerThread.h"
#include <unistd.h>


namespace wd
{

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit)
		stop();
}

void Threadpool::start()
{
	//创建n个子线程对象
	for(size_t idx = 0; idx != _threadNum; ++idx)
	{
		shared_ptr<Thread> sp(new WorkerThread(*this));
		_threads.push_back(sp);
		//_threads[idx] = sp;//error
	}

	//开启n个子线程
	for(auto & subThread : _threads)
	{
		subThread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_taskque.empty())
		{
			::sleep(2);
		}

		_isExit = true;

		for(auto & subThread : _threads)
		{
			subThread->join();
		}
	}
}

void Threadpool::addTask(Task * ptask)
{
	_taskque.push(ptask);
}

Task * Threadpool::getTask()
{
	return _taskque.pop();
}


//每一个子线程要做的事儿
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task * ptask = getTask();
		if(ptask)
			ptask->process();
	}
}



}//end of namespace wd

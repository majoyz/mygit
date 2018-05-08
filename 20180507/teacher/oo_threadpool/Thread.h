 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 09:51:49
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{

class Thread
: Noncopyable
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

private:
	static void * threadFunc(void * arg);

	virtual 
	void run()=0;//线程要执行的任务, 作为接口存在
private:
	pthread_t _pthId;
	bool _isRunning;
};

}//end of namespace wd

#endif

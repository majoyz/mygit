 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:50:54
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

	bool isRunning() const{	return _isRunning;	}

private:
	virtual void run()=0;//线程真正要执行的任务

	static void * threadFunc(void * arg);//线程的执行体//静态后this指针被消除掉了//void*实参可以任意类型
	
private:
	pthread_t _pthid;
	bool _isRunning;
};

}//end of namespace wd
#endif 




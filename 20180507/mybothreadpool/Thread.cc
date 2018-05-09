 ///
 /// @file    Thread.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 18:57:49
 ///
 
#include "Thread.h"
#include <iostream>

namespace wd{
	Thread::Thread()
	:_pthid(0)
	,_isRunning(false)
	{
		std::cout << "Thread()" << std::endl;
	}

	Thread::~Thread(){
		if(_isRunning){
			pthread_detach(_pthid);
			_isRunning = false;
		}
		std::cout << "~Thread()" << std::endl;
	}

	void Thread::start(){
		pthread_create(&_pthid,NULL,threadFunc,this);//传进来一个Thread类本身
		_isRunning = true;
	}

	void Thread::join(){
		if(_isRunning){
			pthread_join(_pthid,NULL);//用NULL是只等待不回收来着吗？
		}
	}

	void * Thread::threadFunc(void * arg){
		Thread * pthread = static_cast<Thread*> (arg);
		if(pthread){
			pthread->run();
		}
		return NULL;
	}
}

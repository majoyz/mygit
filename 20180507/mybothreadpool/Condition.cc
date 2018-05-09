 ///
 /// @file    Condition.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:19:52
 ///
 
#include "Condition.h"
#include "Mutex.h"

using namespace wd;

Condition::Condition(Mutex & mutex)
:_mutex(mutex)
{
	pthread_cond_init(&_cond,NULL);
}

Condition::~Condition(){
	pthread_cond_destroy(&_cond);
}

void Condition::wait(){
	pthread_cond_wait(&_cond,_mutex.getMutexP());
}

void Condition::notify(){
	pthread_cond_signal(&_cond);
}

void Condition::notifyAll(){
	pthread_cond_broadcast(&_cond);
}

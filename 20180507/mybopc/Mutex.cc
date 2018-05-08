 ///
 /// @file    Mutex.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:08:30
 ///
 
#include "Mutex.h"

using namespace wd;

Mutex::Mutex()
:_isLocking(false)
{}

Mutex::~Mutex(){
	pthread_mutex_destroy(&_mutex);
}

void Mutex::lock(){
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void Mutex::unlock(){
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}

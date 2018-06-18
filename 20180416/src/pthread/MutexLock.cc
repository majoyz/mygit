 ///
 /// @file    MutexLock.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 15:58:36
 ///
 
#include "MutexLock.h"
#include <iostream>
using std::cout;
using std::endl;

MutexLock::MutexLock()
: _isLocking(false)
{
	pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}

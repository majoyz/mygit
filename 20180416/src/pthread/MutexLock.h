 ///
 /// @file    MutexLock.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 15:56:32
 ///
 
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__
#include <pthread.h>

class MutexLock
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	pthread_mutex_t * getMutexPtr() {	return &_mutex;	}
	bool isLocking() const{	return _isLocking;	}

	//C++11的用法
	MutexLock(const MutexLock &) = delete;
	MutexLock & operator=(const MutexLock &) = delete;
	
private:
	//禁止复制
	//MutexLock(const MutexLock &);
	//MutexLock & operator=(const MutexLock &);

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	MutexLock & _mutex;
};
 
#endif

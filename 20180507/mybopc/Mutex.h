 ///
 /// @file    Mutex.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 19:37:00
 ///
 
#ifndef __WD_MUTEX_H__
#define __WD_MUTEX_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wd{
	class Mutex
	:Noncopyable
	{
		public:
			Mutex();
			~Mutex();

			void lock();
			void unlock();
			bool isLocking() const{
				return _isLocking;
			}

			pthread_mutex_t * getMutexP(){
				return &_mutex;
			}

		private:
			pthread_mutex_t _mutex;
			bool _isLocking;
	};

	class AutoMutex
	:Noncopyable
	{
		public:
			AutoMutex(Mutex & mutex)
			:_mutex(mutex)
			{
				_mutex.lock();
			}

			~AutoMutex(){
				_mutex.unlock();
			}

		private:
			Mutex & _mutex;
	};
}

#endif

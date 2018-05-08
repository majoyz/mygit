 ///
 /// @file    Thread.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 17:43:38
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"
#include <pthread.h>
namespace wd{
	class Thread{
		public:
			Thread();
			~Thread();

			void start();
			void join();
			bool isRunning() const{
				return _isRunning;
			}
		private:
			virtual void run() = 0;
			static void * threadFunc(void * arg);
		private:
			pthread_t _pthid;
			bool _isRunning;
	};
}
#endif

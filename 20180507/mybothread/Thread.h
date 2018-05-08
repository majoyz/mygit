 ///
 /// @file    Thread.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 17:43:38
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include <functional>
#include <pthread.h>
namespace wd{
	class Thread{
		public:
			typedef std::function<void()> ThreadCallBack;//无参的问题用bind解决
			Thread(ThreadCallBack && tcb);//右值引用
			~Thread();

			void start();
			void join();
			bool isRunning() const{
				return _isRunning;
			}
		private:
			static void * threadFunc(void * arg);
		private:
			pthread_t _pthid;
			bool _isRunning;
			ThreadCallBack _tcb;
	};
}
#endif

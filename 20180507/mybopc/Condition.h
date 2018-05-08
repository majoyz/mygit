 ///
 /// @file    Condition.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:12:16
 ///
 
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"
#include <pthread.h>
namespace wd{
	class Mutex;
	class Condition{
		public:
			Condition(Mutex & _mutex);
			~Condition();

			void wait();
			void notify();
			void notifyAll();
	
		private:
			pthread_cond_t _cond;
			Mutex & _mutex;
	};
}

#endif

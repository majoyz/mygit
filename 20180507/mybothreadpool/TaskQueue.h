 ///
 /// @file    TaskQueue.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:24:59
 ///
 
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "Mutex.h"
#include "Condition.h"
#include <queue>
#include <functional>
namespace wd{
	class TaskQueue{
		public:
			using Type = std::function<void()>;
			TaskQueue(size_t quesize);

			bool full() const;
			bool empty() const;

			void push(Type && type);
			Type pop();
			void wakeup();
		private:
			size_t _quesize;
			std::queue<Type> _que;
			Mutex _mutex;
			Condition _notfull;
			Condition _notempty;
			bool _flag;
	};
}

#endif

 ///
 /// @file    pack_log4cpp.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-15 20:43:46
 ///

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

#if 1
class Mutex{
	public:
		void mutexLock(){
			pthread_mutex_lock(&_mutex);
			cout << "I have locked" << endl;
		}

		void mutexUnlock(){
			pthread_mutex_unlock(&_mutex);
			cout << "I have unlocked" << endl;
		}

		Mutex(){
			pthread_mutex_init(&_mutex,NULL);
		}

		~Mutex(){
			pthread_mutex_destroy(&_mutex);
		}

		pthread_mutex_t * getMutes(){
			return &_mutex;
		}

	private:
		pthread_mutex_t _mutex;
};
#endif

class Condition{
	public:
		Condition(Mutex & mutex)
		:_mutex(mutex)
		{
			pthread_cond_init(& _cond,NULL);
		}

		~Condition(){
			pthread_cond_destroy(& _cond);
		}

		void cWait(){
			pthread_cond_wait(& _cond,_mutex.getMutes());
			cout << "Stop wait" << endl;
		}

		void cNotify(){
			pthread_cond_signal(& _cond);
			cout << "Signal one" << endl;
		}

		void cNotifyall(){
			pthread_cond_broadcast(& _cond);
			cout << "Signal all" << endl;
		}

	private:
		pthread_cond_t _cond;
		Mutex & _mutex;
};

int main(){

#if 1
	Mutex ml;
	ml.mutexLock();
	ml.mutexUnlock();
#endif

	return 0;
}

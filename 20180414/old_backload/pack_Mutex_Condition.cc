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
		static Mutex * getMutex(){
			if(XX == NULL){
				XX = new Mutex();
			}
			return XX;
		}

		void mutexLock(){
			pthread_mutex_lock(&_mutex);
			cout << "I have locked" << endl;
		}

		void mutexUnlock(){
			pthread_mutex_unlock(&_mutex);
			cout << "I have unlocked" << endl;
		}
	private:	
		Mutex()
		{
			pthread_mutex_init(&_mutex,NULL);
		}

		~Mutex(){
			pthread_mutex_destroy(&_mutex);
		}

	private:
		static Mutex * XX;
		pthread_mutex_t _mutex;
};
Mutex * Mutex::XX = NULL;

void lock(){
	Mutex * name = Mutex::getMutex();
	name->mutexLock();
}

void unlock(){
	Mutex * name = Mutex::getMutex();
	name->mutexUnlock();
}

#endif

class Condition{
	public:
		static Condition * getCondition(){
			if(CC == NULL){
				CC = new Condition();
			}
			return CC;
		}

		void cWait(){
			pthread_mutex_lock(& _mutex);
			pthread_cond_wait(& _cond,& _mutex);
			pthread_mutex_unlock(& _mutex);
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
		Condition(){
			pthread_mutex_init(&_mutex,NULL);
			pthread_cond_init(& _cond,NULL);
		}

		~Condition(){
			pthread_mutex_destroy(&_mutex);
			pthread_cond_destroy(& _cond);
		}

	private:
		static Condition * CC;
		pthread_cond_t _cond;
		pthread_mutex_t _mutex;
};

Condition * Condition::CC = NULL;

void wait(){
	Condition * name = Condition::getCondition();
	name->cWait();
}

void notify(){
	Condition * name = Condition::getCondition();
	name->cNotify();
}

void notifyall(){
	Condition * name = Condition::getCondition();
	name->cNotifyall();
}


int main(){

#if 1
	lock();
	unlock();
#endif

	wait();
	notifyall();
	return 0;
}

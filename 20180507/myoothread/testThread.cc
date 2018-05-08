 ///
 /// @file    testThread.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 19:12:28
 ///
 
#include "Thread.h"

#include <iostream>
#include <memory>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class MyThread
:public wd::Thread
{
	public:
		MyThread(){
			cout << "MyThread()" << endl;
		}

		~MyThread(){
			cout << "~MyThread()" << endl;
		}

	private:
		void run(){
			srand(clock());
			int number = 7;
			int nrand;
			while(number--){
				nrand = rand()%100;
				//cout << "I got a " << nrand << endl;
				printf("I got a %d\n",nrand);
				sleep(1);
			}
		}
	
};

int main(){
	unique_ptr<wd::Thread> thread1(new MyThread);
	unique_ptr<wd::Thread> thread2(new MyThread);
	thread1->start();
	thread2->start();
	thread1->join();
	thread2->join();
	return 0;
}

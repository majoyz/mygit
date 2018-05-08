 ///
 /// @file    testpc.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:58:42
 ///
 
#include "Thread.h"
#include "TaskQueue.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using namespace std;
using namespace wd;

class Producer
:public Thread
{
	public:
		Producer(TaskQueue & taskQue)
		:_taskQue(taskQue)
		{}

	private:
		void run(){
			srand(clock());
			int num = 10;
			int number;
			while(num--){
				number = rand()%100;
				_taskQue.push(number);
				printf("TaskQueue got a %d\n",number);
				sleep(1);
			}
		}
	private:
		TaskQueue & _taskQue;
};

class Consumer
:public Thread
{
	public:
		Consumer(TaskQueue & taskQue)
		:_taskQue(taskQue)
		{}
	private:
		void run(){
			int num = 10;
			while(num--){
				int gettmp = _taskQue.pop();
				printf("Consumer got a %d\n",gettmp);
				sleep(3);
			}
		}
	private:
		TaskQueue & _taskQue;
};

int main(){

	TaskQueue taskQue(5);
	unique_ptr<Thread> producer(new Producer(taskQue));
	unique_ptr<Thread> consumer(new Consumer(taskQue));
	producer->start();
	consumer->start();
	producer->join();
	consumer->join();

	return 0;
}

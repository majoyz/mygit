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
{
	public:
		Producer(){
			cout << "Producer()" << endl;
		}

		void producer(TaskQueue & taskQue){
			srand(clock());
			int num = 10;
			int number;
			while(num--){
				number = rand()%100;
				taskQue.push(number);
				printf("TaskQueue got a %d\n",number);
				sleep(1);
			}
		}
};

class Consumer
{
	public:
		Consumer(){
			cout << "Consumer()" << endl;
		}
		void consumer(TaskQueue & taskQue){
			int num = 10;
			while(num--){
				int gettmp = taskQue.pop();
				printf("Consumer got a %d\n",gettmp);
				sleep(3);
			}
		}
};

int main(){

	TaskQueue taskQue(5);
	unique_ptr<Thread> producer(new Thread(std::bind(&Producer::producer,Producer(),std::ref(taskQue))));
	unique_ptr<Thread> consumer(new Thread(std::bind(&Consumer::consumer,Consumer(),std::ref(taskQue))));
	producer->start();
	consumer->start();
	producer->join();
	consumer->join();

	return 0;
}

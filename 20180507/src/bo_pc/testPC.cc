 ///
 /// @file    testThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 10:09:42
 ///
 

#include "Thread.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

using namespace wd;

class Producer 
{
public:
	Producer()
	{	
		cout << "Producer()\n";
	} 

	void produce(TaskQueue & taskQue){
		srand(clock());
		int cnt = 20;
		while(cnt--){
			int number = rand() % 100;
			taskQue.push(number);
			cout << ">>> produce a numbe : " << number << endl;
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

	void consume(TaskQueue & taskQue){
		int cnt = 20;
		while(cnt--){
			int number = taskQue.pop();
			cout << "> consume a number " << number << endl;
			sleep(2);
		}
	}
};
int main(void)
{
	TaskQueue taskQueue(10);
	//std::bind绑定参数时，采用的是值传递，会进行复制; 而TaskQueue 不能进行复制
	unique_ptr<Thread> producer(
		new Thread(
			std::bind(&Producer::produce, 
				Producer(), 
				std::ref(taskQueue))
		)
	);
	unique_ptr<Thread> consumer(
		new Thread(
			std::bind(&Consumer::consume, 
				Consumer(), 
				std::ref(taskQueue))
		)
	);
	producer->start();
	consumer->start();
	producer->join();
	consumer->join();
	return 0;
}

 ///
 /// @file    testThreadpool.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-08 15:59:45
 ///
 
#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class MyTask
:public Task
{
	public:
		void process(){
			srand(clock());
			int number  = rand() % 100;
			printf("produced a number %d\n",number);
		}
};

int main(){
	Threadpool threadpool(4,10);
	unique_ptr<Task> ptask(new MyTask);
	threadpool.start();
	int num = 20;
	while(num--){
		printf("num = %d\n",num);
		threadpool.addTask(ptask.get());
	}
	threadpool.stop();
	return 0;
}

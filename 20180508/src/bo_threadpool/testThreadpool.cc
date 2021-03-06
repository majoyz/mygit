 ///
 /// @file    testThreadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 16:10:26
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
{
public:
	void process()
	{
		::srand(::clock());
		int number = ::rand() % 100;
		cout << ">>> produce a number = " << number << endl;
		::sleep(2);
	}
};

 
int main(void)
{
	Threadpool threadpool(4, 10);
	threadpool.start();
	unique_ptr<MyTask> ptask(new MyTask());
	
	int cnt = 20;
	while(cnt--){
		cout << ">>> cnt = " << cnt << endl;
		//threadpool.addTask(std::bind(&MyTask::process, ptask.get()));
		threadpool.addTask([](){
			::srand(::clock());
			int number = ::rand() % 100;
			cout << ">>> produce a number = " << number << endl;
			//::sleep(2);
		});
	}

	threadpool.stop();
	return 0;
}

 ///
 /// @file    testThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 10:09:42
 ///
 
#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;


class Task 
{
public:
	void process(){
		srand(clock());
		int cnt = 5;
		while(cnt--){
			int number = rand() % 100;
			cout << "number = " << number << endl;
			sleep(1);
		}
	}
};


void getNumber()
{
	srand(clock());
	int cnt = 5;
	while(cnt--){
		int number = rand() % 100;
		cout << "number = " << number << endl;
		sleep(1);
	}
}
 
int main(void)
{
	//Task task;
	//unique_ptr<wd::Thread> thread(new wd::Thread(std::bind(&Task::process, &task)));
	unique_ptr<wd::Thread> thread(new wd::Thread(getNumber));
	thread->start();
	thread->join();
	return 0;
}

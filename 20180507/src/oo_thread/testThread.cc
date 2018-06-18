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


class MyThread
: public wd::Thread
{
public:
	MyThread(){ cout << "MyThread()" << endl;}
	~MyThread(){ cout << "~MyThread()" << endl;}
	

private:
	void run(){
		srand(clock());
		int cnt = 5;
		while(cnt--){
			int number = rand() % 100;
			cout << "number = " << number << endl;
			sleep(1);
		}
	}
};
 
int main(void)
{
	//MyThread m1;
	//MyThread m2 = m1;//error;

	unique_ptr<wd::Thread> thread(new MyThread);
	thread->start();
	thread->join();
	return 0;
}

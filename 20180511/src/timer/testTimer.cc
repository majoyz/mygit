 ///
 /// @file    testTimer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 10:29:31
 ///
 
#include "TimerThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
 
int test0(void)
{
	wd::Timer timer(3, 6, [](){
		::srand(clock());
		int number = ::rand() % 100;
		cout << ">>> number = " << number << endl;
	});
	//timer.start();

	wd::Thread thread(std::bind(&wd::Timer::start, &timer));
	thread.start();

	::sleep(30);
	timer.stop();
	thread.join();
	return 0;
}

void test1(void)
{
	wd::TimerThread timer(3, 6, [](){
		::srand(clock());
		int number = ::rand() % 100;
		cout << ">>> number = " << number << endl;
	});

	timer.start();
	::sleep(30);
	timer.stop();
}

int main(void)
{
	test1();
	return 0;
}

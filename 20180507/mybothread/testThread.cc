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

void progress(){
	srand(clock());
	int num = 10;
	int number;
	while(num--){
		number = rand()%100;
		cout << "number = " << number << endl;
		sleep(1);
	}
}

int main(){
	unique_ptr<wd::Thread> thread(new wd::Thread(progress));
	thread->start();
	thread->join();
	return 0;
}

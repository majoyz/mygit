 ///
 /// @file    Threadpool.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-08 10:43:23
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;
using namespace wd;

Threadpool::Threadpool(size_t threadNum,size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false)
{
	_threads.reserve(_threadNum);
	
}

Threadpool::~Threadpool(){
	if(!_isExit){
		stop();
	}
}

void Threadpool::start(){
	//创建子线程对象
	for(size_t idx = 0;idx!=_threadNum;++idx){
		unique_ptr<Thread> pt(new Thread(std::bind(&Threadpool::threadFunc,this)));
		_threads.push_back(std::move(pt));
	}
	//开启子线程
	for(auto & thread : _threads){
		thread->start();
	}
}

void Threadpool::stop(){
	cout << "stopping" << endl;
	if(!_isExit){
		while(!_taskQue.empty()){
			sleep(1);
		}
		_isExit = true;
		_taskQue.wakeup();//唤醒阻塞线程
	}
	cout << "after wakeup" << endl;
	for(auto & pthread : _threads){
		pthread->join();
	}
	cout << "stopped" << endl;
}

void Threadpool::addTask(Task && task){
	_taskQue.push(std::move(task));
}

Threadpool::Task Threadpool::getTask(){
	return _taskQue.pop();
}

void Threadpool::threadFunc(){
	while(!_isExit){
		Task task = getTask();
		if(task)
			task();
	}
}

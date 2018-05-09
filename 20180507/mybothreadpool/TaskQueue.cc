///
/// @file    TaskQueue.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-07 20:46:40
///

#include "TaskQueue.h"
#include <iostream>
using namespace wd;

TaskQueue::TaskQueue(size_t quesize)
	:_quesize(quesize)
	,_mutex()
	,_notfull(_mutex)
	,_notempty(_mutex)
	 ,_flag(true)
{}

bool TaskQueue::full() const{
	return _que.size() == _quesize;
}

bool TaskQueue::empty() const{
	return _que.size() == 0;
}

void TaskQueue::push(Type && type){
	AutoMutex autolock(_mutex);
	while(full()){
		_notfull.wait();
	}
	_que.push(std::move(type));
	_notempty.notify();
}

TaskQueue::Type TaskQueue::pop(){
	AutoMutex autolock(_mutex);
	while(_flag && empty()){
		_notempty.wait();
	}
	if(_flag){
		Type tmp = _que.front();
		_que.pop();
		_notfull.notify();
		return tmp;
	}else{
		return nullptr;
	}
}

void TaskQueue::wakeup(){
	_flag = false;
	_notempty.notifyAll();
}

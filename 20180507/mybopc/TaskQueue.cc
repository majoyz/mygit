 ///
 /// @file    TaskQueue.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 20:46:40
 ///
 
#include "TaskQueue.h"
using namespace wd;

TaskQueue::TaskQueue(size_t quesize)
:_quesize(quesize)
,_mutex()
,_notfull(_mutex)
,_notempty(_mutex)
{}

bool TaskQueue::full() const{
	return _que.size() == _quesize;
}

bool TaskQueue::empty() const{
	return _que.size() == 0;
}

void TaskQueue::push(Type & type){
	AutoMutex autolock(_mutex);
	while(full()){
		_notfull.wait();
	}
	_que.push(type);
	_notempty.notify();
}

TaskQueue::Type TaskQueue::pop(){
	AutoMutex autolock(_mutex);
	while(empty()){
		_notempty.wait();
	}
	Type tmp = _que.front();
	_que.pop();
	return tmp;
}

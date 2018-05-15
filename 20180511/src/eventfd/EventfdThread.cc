 ///
 /// @file    EventfdThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 11:11:02
 ///
 
#include "EventfdThread.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;


EventfdThread::EventfdThread(EventfdCallback && cb)
: _eventfd(std::move(cb))
, _thread(std::bind(&Eventfd::start, &_eventfd))
{
}

void EventfdThread::start()
{
	_thread.start();
}

void EventfdThread::stop()
{
	_eventfd.stop();
	_thread.join();
}

void EventfdThread::wakeup()
{
	_eventfd.wakeup();
}

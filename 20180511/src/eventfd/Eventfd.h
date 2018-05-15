 ///
 /// @file    Eventfd.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 09:59:07
 ///
 
#ifndef __WD_EVENTFD_H__
#define __WD_EVENTFD_H__

#include <functional>

 
namespace wd
{
class Eventfd
{
public:
	using EventfdCallback = std::function<void()>;
	
	Eventfd(EventfdCallback && cb);
	~Eventfd();

	void start();
	void stop();

	void wakeup();
private:
	int createEventfd();
	void handleRead();

private:
	int _fd;
	bool _isStarted;
	EventfdCallback _cb;
};

}//end of namespace wd

#endif

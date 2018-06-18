 ///
 /// @file    templateSingleton.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 10:58:38
 ///
 
#include "Mylogger.h"
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

template <typename Type>
class Singleton
{
public:
	template <typename... Args>  //Args 模板参数包
	static Type * getInstance(Args... args) //args 函数参数包
	{
		pthread_once(&_once, init);// 在多线程环境下，init只会被执行一次
		if(!_pInstance->isInitEnd())
			_pInstance->init(args...);
		return _pInstance;
	}

	static void init()
	{
		LogDebug("Singleton::init()");
		atexit(destroy);
		_pInstance = new Type;
	}

	static void destroy()
	{
		LogDebug("Singleton::destroy() start");
		if(_pInstance)
			delete _pInstance;
		LogDebug("Singleton::destroy() end");
	}

private:
	Singleton();
	~Singleton();

private:
	static Type * _pInstance;
	static pthread_once_t _once;
};

template <typename Type>
Type * Singleton<Type>::_pInstance = NULL;

template <typename Type>
pthread_once_t Singleton<Type>::_once = PTHREAD_ONCE_INIT;


class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	, _isInitEnd(false)
	{
		LogDebug("Point(int ix = 0,int iy =0)");
	}

	//二段式构造
	void init(int ix, int iy)
	{
		LogDebug("Point::init(int,int)");
		_ix = ix;
		_iy = iy;
		_isInitEnd = true;
	}

	bool isInitEnd() const
	{	return _isInitEnd;	}

	~Point()
	{
		LogDebug("~Point()");
	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
	bool _isInitEnd;
};
 
std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}
int main(void)
{
	Point * pt1 = Singleton<Point>::getInstance(1, 2);
	Point * pt2 = Singleton<Point>::getInstance(1, 2);

	LogDebug("pt1 = %p", pt1);
	LogDebug("pt2 = %p", pt2);
	cout << "*pt1 = " << *pt1 << endl;
	cout << "*pt2 = " << *pt2 << endl;

	return 0;
}

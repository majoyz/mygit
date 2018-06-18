 ///
 /// @file    templateSingleton.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 10:58:38
 ///
 
#include "Mylogger.h"
#include <iostream>
using std::cout;
using std::endl;

template <typename Type>
class Singleton
{
	class AutoRelease
	{
	public:
		AutoRelease(){
			LogDebug("AutoRelease()");
		}

		~AutoRelease(){
			if(_pInstance){
				delete _pInstance;
				_pInstance = nullptr;
				LogDebug("~AutoRelease()");
			}
		}
	};
public:
	template <typename... Args>  //Args 模板参数包
	static Type * getInstance(Args... args) //args 函数参数包
	{
		if(NULL == _pInstance){
			_auto;//为了创建_auto对象，必须要调用一次(模板只有在实例化时才会去进行模板参数推导)
			_pInstance = new Type(args...);
		}
		return _pInstance;
	}

private:
	Singleton();
	~Singleton();

private:
	static Type * _pInstance;
	static AutoRelease _auto;
};

template <typename Type>
Type * Singleton<Type>::_pInstance = NULL;

template <typename Type>
typename Singleton<Type>::AutoRelease Singleton<Type>::_auto;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		LogDebug("Point(int ix = 0,int iy =0)");
	}

	~Point()
	{
		LogDebug("~Point()");
	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
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

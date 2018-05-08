 ///
 /// @file    Noncopyable.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 17:39:16
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__
namespace wd{
	class Noncopyable{
	protected:
		Noncopyable(){}
		~Noncopyable(){}

		//Noncopyable operator()(const Noncopyable &) = delete;
		Noncopyable (const Noncopyable &) = delete;
		Noncopyable &operator=(const Noncopyable &) = delete;
	};
}

#endif

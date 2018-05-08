 ///
 /// @file    Noncopyable.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-07 17:39:16
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__
namespace wd{
	class Noncopybale{
		Noncopybale(){}
		~Noncopybale(){}

		//Noncopybale operator()(const Noncopybale &) = delete;
		Noncopybale (const Noncopybale &) = delete;
		Noncopybale &operator=(const Noncopybale &) = delete;
	};
}

#endif

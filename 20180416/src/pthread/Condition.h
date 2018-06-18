 ///
 /// @file    Condition.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 16:02:52
 ///
 
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include <pthread.h>

class MutexLock;//类的前向声明, 减少头文件的依赖

class Condition
{
public:
	Condition(MutexLock & mutex);
	~Condition();
	void wait();	
	void notify();
	void notifyall();

	//禁止复制
	Condition(const Condition &) = delete;
	Condition & operator=(const Condition &) = delete;

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;//互斥锁不能成为条件变量的对象成员,因为这两者的生命周期是独立的
					   //类与类之间的关系：  单向的关联关系
};

#endif

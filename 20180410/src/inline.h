 ///
 /// @file    inline.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 16:19:24
 ///
 
#ifndef __INLINE_H__
#define __INLINE_H__

//inline函数与带参数的宏定义的差别？
//
//1. 带参数的宏定义也是简单的字符串替换
//2. inline函数还是一个函数,有检查机制,使用起来会更安全一些
//3. 推荐大家使用inline函数
 
//inline函数,功能与带参数的宏定义类似
//它会把函数体中的语句直接替换掉


#define Max(x,y)   ((x) > (y) ? (x) : (y))
#define getValue(x, y)  ((x)*(y))

inline
int func(int x, int y)
{
	return x * y;
}


#endif

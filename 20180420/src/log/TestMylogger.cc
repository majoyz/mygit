 ///
 /// @file    TestMylogger.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-20 11:48:30
 ///
 
#include "Mylogger.h"
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	int a = 3, b = 4;
	const char * pstr = "hello,world";
	LogError("error message a = %d, b = %d, %s", a, b, pstr);
	LogWarn("warn message a = %d, b = %d, %s", a, b, pstr);
	LogInfo("info message a = %d, b = %d, %s", a, b, pstr);
	LogDebug("debug message a = %d, b = %d, %s", a, b, pstr);
	return 0;
}

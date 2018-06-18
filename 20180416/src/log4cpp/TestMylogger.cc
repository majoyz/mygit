 ///
 /// @file    TestMylogger.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 14:59:56
 ///
 
#include "Mylogger.h"
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
 

void test0(void)
{ 
	Mylogger::getInstance()->info("info message");
	Mylogger::getInstance()->warn("warn message");
	Mylogger::getInstance()->error("error message");
	Mylogger::getInstance()->debug("debug message");

	Mylogger::destroy();
}
void test1(void)
{
	cout << "this is a line"
		    "hell,world"
			"shenzhen"
		 << endl;

	cout << __FILE__"hello" << endl;
	//cout << "world"__func__ << endl;
	cout << __FUNCTION__ << endl;
	cout << __LINE__ << endl;
}

void test2(void)
{ 
	Mylogger::getInstance()->info(prefix("info message"));
	Mylogger::getInstance()->warn(prefix("warn message"));
	Mylogger::getInstance()->error(prefix("error message"));
	Mylogger::getInstance()->debug(prefix("debug message"));

	Mylogger::destroy();
}

void test3(void)
{
	//int number = 10;
	//LogWarn("warn message number = %d", number);
	LogError("error message");
	LogInfo("info message");
	LogDebug("debug message");

	Mylogger::destroy();
}


int main(void)
{
	//test0();
	//test1();
	//test2();
	test3();

	return 0;
}

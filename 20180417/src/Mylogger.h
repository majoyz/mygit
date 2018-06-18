 ///
 /// @file    Mylogger.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 14:40:05
 ///
 
#ifndef __WD_MYLOGGER_H__
#define __WD_MYLOGGER_H__

#include <string>
#include <sstream>
#include <log4cpp/Category.hh>
using std::string;


class Mylogger
{
public:
	enum Priority
	{
		ERROR,
		WARN,
		INFO,
		DEBUG
	};

	static Mylogger * getInstance();
	static void destroy();

	void warn(const char * msg);
	void error(const char * msg);
	void info(const char * msg);
	void debug(const char * msg);

	void setPriority(Priority priority);

private:
	Mylogger();
	~Mylogger();
	
private:
	static Mylogger * _pInstance;
	log4cpp::Category & _root;
};


inline string int2str(int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

#define prefix(msg) string("[").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(int2str(__LINE__))\
		.append("] :").append(msg).c_str()

#define LogWarn(msg)  Mylogger::getInstance()->warn(prefix(msg))
#define LogError(msg)  Mylogger::getInstance()->error(prefix(msg))
#define LogInfo(msg)  Mylogger::getInstance()->info(prefix(msg))
#define LogDebug(msg)  Mylogger::getInstance()->debug(prefix(msg))

#endif

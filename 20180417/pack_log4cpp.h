 ///
 /// @file    pack_log4cpp.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-15 20:43:46
 ///

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

class Mylog{
	public:
		static Mylog * getmylog();
		static void destory();
		void warn(const char * msg);
		void error(const char * msg);
		void debug(const char * msg);
		void info(const char * msg);
	private:
		Mylog();
		~Mylog();
	private:
		static Mylog * XX;
		log4cpp::OstreamAppender * _ostreamAppender;
		log4cpp::FileAppender * _fileAppender;
		log4cpp::PatternLayout * pLayout;
		log4cpp::PatternLayout * qLayout;
		log4cpp::Category & _root = log4cpp::Category::getRoot();
};

inline string myitoa(int num){//数字转字符串，仅用于获取行号添加到日志
	ostringstream oss;
	oss << num;
	return oss.str();
}

#define prefix(msg) string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(myitoa(__LINE__)).append("]:").append(msg)

#define logInfo(msg) Mylog::getmylog()->info(prefix(msg).c_str())
#define logError(msg) Mylog::getmylog()->error(prefix(msg).c_str())
#define logWarn(msg) Mylog::getmylog()->warn(prefix(msg).c_str())
#define logDebug(msg) Mylog::getmylog()->debug(prefix(msg).c_str())


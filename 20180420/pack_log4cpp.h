 ///
 /// @file    pack_log4cpp.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-15 20:43:46
 ///

#ifndef __WD_PACK_LOG4CPP_H__
#define __WD_PACK_LOG4CPP_H__

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
		enum Priority{
			ERROR,
			WARN,
			INFO,
			DEBUG
		};

		static Mylog * getmylog();
		static void destory();

		void warn(const char * msg);
		template <typename... Args>
		void warn(const char * msg,Args... args){
			_root.warn(msg,args...);
		}

		void error(const char * msg);
		template <typename... Args>
		void error(const char * msg,Args... args){
			_root.warn(msg,args...);
		}

		void debug(const char * msg);
		template <typename... Args>
		void debug(const char * msg,Args... args){
			_root.warn(msg,args...);
		}

		void info(const char * msg);
		template <typename... Args>
		void info(const char * msg,Args... args){
			_root.warn(msg,args...);
		}

		void setPriority(Priority priority);

	private:
		Mylog();
		~Mylog();
	private:
		static Mylog * _pInstance;
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

#define logInfo(msg,...) Mylog::getmylog()->info(prefix(msg).c_str(),##__VA_ARGS__)
#define logError(msg,...) Mylog::getmylog()->error(prefix(msg).c_str(),##__VA_ARGS__)
#define logWarn(msg,...) Mylog::getmylog()->warn(prefix(msg).c_str(),##__VA_ARGS__)
#define logDebug(msg,...) Mylog::getmylog()->debug(prefix(msg).c_str(),##__VA_ARGS__)

#endif

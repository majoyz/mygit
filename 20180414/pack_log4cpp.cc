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
		static Mylog * getmylog(){
			if(XX == NULL){
				XX = new Mylog();
			}
			return XX;
		}
		static void destory(){
			if(XX){
				delete XX;
			}
			cout << "destory" << endl;
		}
		void warn(const char * msg){
			_root.warn(msg);
		}
		void error(const char * msg){
			_root.error(msg);
		}
		void debug(const char * msg){
			_root.debug(msg);
		}
		void info(const char * msg){
			_root.info(msg);
		}
	private:
		Mylog(){
			_ostreamAppender = new log4cpp::OstreamAppender("_ostreamAppender",&cout);
			_fileAppender = new log4cpp::FileAppender("_fileAppender","logfile");
			pLayout = new log4cpp::PatternLayout();
			qLayout = new log4cpp::PatternLayout();//need new again,or it will delete twice
			pLayout->setConversionPattern("%d : %8p : %m%n");
			qLayout->setConversionPattern("%d : %8p : %m%n");
			_ostreamAppender->setLayout(pLayout);
			_fileAppender->setLayout(qLayout);
			_root.addAppender(_ostreamAppender);
			_root.addAppender(_fileAppender);
			_root.setPriority(log4cpp::Priority::DEBUG);
		}
		~Mylog(){
			log4cpp::Category::shutdown();
			cout << "~Mylog()" << endl;
		}
	private:
		static Mylog * XX;
		log4cpp::OstreamAppender * _ostreamAppender;
		log4cpp::FileAppender * _fileAppender;
		log4cpp::PatternLayout * pLayout;
		log4cpp::PatternLayout * qLayout;
		log4cpp::Category & _root = log4cpp::Category::getRoot();
};

Mylog * Mylog::XX = NULL;

inline string myitoa(int num){
	ostringstream oss;
	oss << num;
	return oss.str();
}

#define prefix(msg) string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(myitoa(__LINE__)).append("]:").append(msg)

#define logInfo(msg) Mylog::getmylog()->info(prefix(msg).c_str())
#define logError(msg) Mylog::getmylog()->error(prefix(msg).c_str())
#define logWarn(msg) Mylog::getmylog()->warn(prefix(msg).c_str())
#define logDebug(msg) Mylog::getmylog()->debug(prefix(msg).c_str())

int main(){
	cout << "Hello log4cpp!" << endl;

	logInfo("Can you see the info message?");
	logError("Can you see the error message?");
	logWarn("Can you see the warn message?");
	logDebug("Can you see the debug message?");
	
	Mylog::destory();
	return 0;
}

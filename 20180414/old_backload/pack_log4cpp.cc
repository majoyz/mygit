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
using std::stringstream;

class Mylog{
	public:
		static Mylog * getmylog(){
			if(XX == NULL){
				XX = new Mylog();
			}
			return XX;
		}
		static void destory(){
			delete XX;
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
//			_ostreamAppender->setLayout(new log4cpp::BasicLayout());
//			_fileAppender->setLayout(new log4cpp::BasicLayout());
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

void logInfo(const char * msg){
	string tmp(msg);
	stringstream tss;
	tss << tmp << "  from  " << __FILE__ << "  " << __LINE__ << "  " << __FUNCTION__ << "  ";

	Mylog * cslog = Mylog::getmylog();
	cslog -> info(tss.str().c_str());
}

void logError(const char * msg){
	string tmp(msg);
	stringstream tss;
	tss << tmp << "  from  " << __FILE__ << "  " << __LINE__ << "  " << __FUNCTION__ << "  ";

	Mylog * cslog = Mylog::getmylog();
	cslog -> error(tss.str().c_str());
}

void logWarn(const char * msg){
	string tmp(msg);
	stringstream tss;
	tss << tmp << "  from  " << __FILE__ << "  " << __LINE__ << "  " << __FUNCTION__ << "  ";

	Mylog * cslog = Mylog::getmylog();
	cslog -> warn(tss.str().c_str());
}

void logDebug(const char * msg){
	string tmp(msg);
	stringstream tss;
	tss << tmp << "  from  " << __FILE__ << "  " << __LINE__ << "  " << __FUNCTION__ << "  ";

	Mylog * cslog = Mylog::getmylog();
	cslog -> debug(tss.str().c_str());
}

int main(){
	cout << "Hello log4cpp!" << endl;
	logInfo("Can you see the info message?");
	logError("Can you see the error message?");
	logWarn("Can you see the warn message?");
	logDebug("Can you see the debug message?");
	Mylog::destory();

	return 0;
}

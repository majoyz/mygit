///
/// @file    pack_log4cpp.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2018-04-15 20:43:46
///

#include "pack_log4cpp.h"

Mylog * Mylog::XX = NULL;

Mylog * Mylog::getmylog(){
	if(XX == NULL){
		XX = new Mylog();
	}
	return XX;
}
void Mylog::destory(){
	if(XX){
		delete XX;
	}
	cout << "destory" << endl;
}
void Mylog::warn(const char * msg){
	_root.warn(msg);
}
void Mylog::error(const char * msg){
	_root.error(msg);
}
void Mylog::debug(const char * msg){
	_root.debug(msg);
}
void Mylog::info(const char * msg){
	_root.info(msg);
}

Mylog::Mylog(){
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

Mylog::~Mylog(){
	log4cpp::Category::shutdown();
	cout << "~Mylog()" << endl;
}

 ///
 /// @file    log4cpp.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-15 18:55:56
 ///

#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>//目的地，日志被写到哪里
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
using std::cout;
using std::endl;

int main(){

	log4cpp::OstreamAppender * ostreamAppender = new log4cpp::OstreamAppender("ostreamAppender",&cout);//定义一个目的地，参数一是名字，参数二是指针，输到cout里
	log4cpp::PatternLayout * pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern("%d : %10p : %m%n");
	ostreamAppender->setLayout(pLayout);//设置格式，设置为基本格式，三栏：秒数，级别，日志信息

	log4cpp::Category & root = log4cpp::Category::getRoot();//设置Category类型，log4cpp的主体类型，负责写信息
	root.addAppender(ostreamAppender);//添加目的地，即上面设置的cout
	root.setPriority(log4cpp::Priority::INFO);//设置优先级，用的是DEBUG级别

	root.error("error message");
	root.info("info message");
	root.alert("alert message");
	root.debug("debug message");
	root.fatal("fatal message");
	root.crit("critical message");
	root.warn("warn message");

	log4cpp::Category::shutdown();//回收前面的new

	//执行后打印出的长串数字是1970到现在的秒数

	return 0;
}

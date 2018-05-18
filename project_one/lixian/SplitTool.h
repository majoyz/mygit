///
/// @file    SplitTool.h
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-17 15:47:13
///

#ifndef __WD_SPLITTOOL_H__
#define __WD_SPLITTOOL_H__

#include "conf.h"
#include "cppjieba/include/cppjieba/Jieba.hpp"
#include <vector>
using namespace std;

class SplitTool{
	public:
		SplitTool();
		virtual ~SplitTool();
		virtual vector<string> cut(const string & sentence)=0;
};

class SplitToolCppJieba
:public SplitTool
{
	public:
		SplitToolCppJieba();
		~SplitToolCppJieba();
		vector<string> cut(const string & sentence);
	private:
		cppjieba::Jieba *_jieba;
//		Configuration & _conf;
};

#endif

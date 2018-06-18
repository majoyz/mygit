///
/// @file    SplitTool.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-17 17:46:59
///

#include "SplitTool.h"

SplitTool::SplitTool(){}
SplitTool::~SplitTool(){}

SplitToolCppJieba::SplitToolCppJieba()
:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
{}
SplitToolCppJieba::~SplitToolCppJieba(){}
vector<string> SplitToolCppJieba::cut(const string & sentence){
	vector<string> words;

	_jieba.Cut(sentence, words, true);
	return words;
}

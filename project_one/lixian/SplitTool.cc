///
/// @file    SplitTool.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-17 17:46:59
///

#include "SplitTool.h"

SplitTool::SplitTool(){}
SplitTool::~SplitTool(){}

SplitToolCppJieba::SplitToolCppJieba(){
	const char* const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
	const char* const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
	const char* const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
	const char* const IDF_PATH = "cppjieba/dict/idf.utf8";
	const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

	_jieba = new cppjieba::Jieba(DICT_PATH,
			HMM_PATH,
			USER_DICT_PATH,
			IDF_PATH,
			STOP_WORD_PATH);
	vector<string> words;

}
SplitToolCppJieba::~SplitToolCppJieba(){}
vector<string> SplitToolCppJieba::cut(const string & sentence){
	vector<string> words;

	_jieba->Cut(sentence, words, true);
	return words;
}

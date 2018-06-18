///
/// @file    SplitTool.h
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-17 15:47:13
///

#ifndef __WD_SPLITTOOL_H__
#define __WD_SPLITTOOL_H__

#include "./cppjieba/include/cppjieba/Jieba.hpp"
#include <vector>
#include <string>
using namespace std;

const char* const DICT_PATH = "./cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "./cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "./cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "./cppjieba/dict/stop_words.utf8";
#if 0
class SplitTool{
	public:
		SplitTool(){};
		virtual ~SplitTool(){};
		virtual vector<string> cut(const string & sentence)=0;
};
#endif
class SplitToolCppJieba
{
		cppjieba::Jieba *_jieba;
	public:
		SplitToolCppJieba()
//			:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
		{
			_jieba = new cppjieba::Jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
		}
		vector<string> cut(const string & sentence){
			vector<string> words;
			_jieba->Cut(sentence, words, true);
			return words;
		}
};

#endif

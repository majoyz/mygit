 ///
 /// @file    MakeDict.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 15:08:20
 ///
 
#ifndef __WD_MAKEDICT_H__
#define __WD_MAKEDICT_H__

#include "SplitTool.h"
#include "cppjieba/include/cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <iterator>
#include <unordered_map>
using namespace std;

class DictProducer{
	public:
		DictProducer(string &,string &);//构造函数，输入一个文件流
		DictProducer(string &,string &,SplitTool *);//构造函数，处理中文
		void makeDict(ifstream &);//产生map词典
		void make_cn_Dict(ifstream &);//产生中文词典
		void dictFile();//产生词典文件
		void dict_cn_File();
		void makeIndex();//产生unordered_map索引
		void make_cn_Index();
		void indexFile();//产生索引文件
		void index_cn_File();
	private:
		unordered_map<string,set<int>> _index;
		shared_ptr<vector<string>> _file; //储存输入文件的每一行
		map<string,shared_ptr<set<unsigned int>>> _wm;//每个单词到它所在行号的集合的映射
		map<string,int> _dict;//存储单词词频
		map<string,int> _dict_cn;
		string _dictfile;
		string _indexfile;
		SplitTool * _splitTool;//分词工具类
};

int getOnlyWord(string &);//单词处理函数

#endif

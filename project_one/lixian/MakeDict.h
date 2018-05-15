 ///
 /// @file    MakeDict.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 15:08:20
 ///
 
#ifndef __WD_MAKEDICT_H__
#define __WD_MAKEDICT_H__

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

class TextQuery{
	public:
		using line_no = vector<string>::size_type;//size_type是unsigned int型的，是容器的大小
		TextQuery(string &,string &);//构造函数，输入一个文件流
		void addBinTxt(ifstream &);
		void makeDict();
		void makeQDict();
		vector<pair<string,int>> & get_qdict();
		void makeIndex();
		void indexFile();
	private:
		unordered_map<string,set<int>> _index;
		shared_ptr<vector<string>> _file; //储存输入文件的每一行
		map<string,shared_ptr<set<line_no>>> wm;//每个单词到它所在行号的集合的映射
		map<string,int> _dict;//存储单词词频
		vector<pair<string,int>> _qdict;//读取时用这个存储词典
		string _dictfile;
		string _indexfile;
};

int getOnlyWord(string &);//单词处理函数

#endif

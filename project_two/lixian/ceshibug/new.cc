 ///
 /// @file    new.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-29 17:20:46
 ///
 
#include "webPage.h"
//#include "simhash/Simhasher.hpp"
#include <iostream>
#include <fstream>

using namespace simhash;

int main(){
	Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
    size_t topN = 20;
    uint64_t u64 = 0;
    string _docContent("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
    vector<pair<string ,double> > res;
	cout << "problem 0" << endl;
    simhasher.extract(_docContent, res, topN);
	cout << "problem 1" << endl;
    simhasher.make(_docContent, topN, u64);
    cout << "关键词序列是: " << res << endl;
    cout<< "simhash值是: " << u64<<endl;
/*
    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
    string s("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
    size_t topN = 5;
    uint64_t u64 = 0;
    vector<pair<string ,double> > res;
	cout << "problem 0" << endl;
    simhasher.extract(s, res, topN);
	cout << "problem 1" << endl;
    simhasher.make(s, topN, u64);
    cout<< "文本：\"" << s << "\"" << endl;
    cout << "关键词序列是: " << res << endl;
    cout<< "simhash值是: " << u64<<endl;
*/
	return 0;
}

 ///
 /// @file    pageLibPreprocessor.cpp
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-23 11:10:46
 ///
 
#include "pageLibPreprocessor.h"

#include <string.h>
#include <cmath>
#include <sstream>

PageLibPreprocessor::PageLibPreprocessor(Configuration & conf)
:_conf(conf)
{}
//
void PageLibPreprocessor::doProcess(){
	readInfoFromFile();
//	cutRedundantPages();
//	cout << "in doProcess,before 3,4" << endl;
//	void buildInvertIndexTable();
//	void storeOnDisk();
}

#if 0
void PageLibPreprocessor::readInfoFromFile(){
	string s = "ceshi";
	cout << "before " << s << endl;
	WebPage tmpweb(s);
	cout << "after " << s << endl;
}
#endif
#if 1
void PageLibPreprocessor::readInfoFromFile(){
	ifstream ifsripepage(_conf.getConfigMap()["myripepagelib"]);
	ifstream ifsoffset(_conf.getConfigMap()["myoffsetlib"]);
	string tmpoffset;
	int docid,tmpstart,tmpsize;
	Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
	while(getline(ifsoffset,tmpoffset)){
		stringstream ss(tmpoffset);
		ss >> docid;
		ss >> tmpstart;
		ss >> tmpsize;
		string tmpdoc(tmpsize,'\0');
		ifsripepage.read(&tmpdoc[0],tmpsize);
		WebPage tmpWeb(tmpdoc,simhasher,_jieba);
//		_pageLib.push_back(tmpWeb);
	}
}
#endif
#if 0
void PageLibPreprocessor::cutRedundantPages(){
	auto it1 = _pageLib.begin();
	auto it2 = _pageLib.begin();
	auto every = _pageLib.begin();
	while(every!=_pageLib.end()){
		cout << "every : " << every->getDocId() << endl;
		++it1;
		it2 = it1;
		while(it2!=_pageLib.end()){
			//cout << it2->getDocId();
			++it2;
			if(*it2 == *every){
				cout << "find a same " << every->getDocId() << "----" << it2->getDocId() << endl;
				auto tmpit = it2--;
				_pageLib.erase(tmpit);
				cout << "erase one " << endl;
			}
		}
		++every;
	}
}

void PageLibPreprocessor::buildInvertIndexTable(){
	unordered_map<string,int> DF;
	unordered_map<string,int> ws;
	for(auto every : _pageLib){
		for(auto everyone : every.getWordMap()){
			++DF[everyone.first];
		}
	}
	
	map<string,int> TF;
	for(auto every : _pageLib){//对于每一篇文章
		TF = every.getWordMap();
		for(auto everyone : TF){
			ws[everyone.first] = log(_pageLib.size()/(DF[everyone.first]+1))/log(2);
		}
		
		int pingfanghe = 0;
		for(auto everytwo : ws){
			pingfanghe += (ws[everytwo.first])*(ws[everytwo.first]);
		}

		for(auto everythree : ws){
			_invertIndexTable[everythree.first].push_back(make_pair(every.getDocId(),everythree.second/sqrt(pingfanghe)));
		}
	}
}

void PageLibPreprocessor::storeOnDisk(){
	ofstream of1(_conf.getConfigMap()["mynewripepagelib"]);
	ofstream of2(_conf.getConfigMap()["mynewoffsetlib"]);
	ofstream of3(_conf.getConfigMap()["myinvertindexlib"]);
	int tmpsite = 0;
	for(auto every : _pageLib){
		of1 << every.getDoc();
		_offsetLib.insert(make_pair(every.getDocId(),make_pair(tmpsite,every.getDoc().size())));
		tmpsite+=every.getDoc().size();
	}
	of1.close();

	for(auto every : _offsetLib){
		of2 << every.first << " " << every.second.first << " " << every.second.second << endl;
	}
	of2.close();

	for(auto every : _invertIndexTable){
		of3 << every.first << endl;
		for(auto everyone : every.second){
			of3 << everyone.first << " " << everyone.second << " ";
		}
		of3 << endl;
	}
	of3.close();
}
#endif

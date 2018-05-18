///
/// @file    Mydict.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-15 10:03:09
///

#include "Mydict.h"

Mydict::Mydict(){}
Mydict::~Mydict(){}

void Mydict::init(const char * dictEnPath,const char * indexEnPath,const char * dictCnPath,const char * indexCnPath){
	fstream defs(dictEnPath);
	fstream iefs(indexEnPath);
	fstream dcfs(dictCnPath);
	fstream icfs(indexCnPath);
	string aline;
	string aword;
	int afrequent;
	int ennum = 0;
	while(getline(defs,aline)){//vector词典
		istringstream sline(aline);
		sline >> aword;
		sline >> afrequent;
		_dict.push_back(make_pair(aword,afrequent));
		++ennum;
	}
	while(getline(dcfs,aline)){//vector中文词典
		istringstream sline(aline);
		sline >> aword;
		sline >> afrequent;
		_dict.push_back(make_pair(aword,afrequent));
	}
	
	string numline;
	string tmpnull;
	int linenum;
	while(getline(iefs,aword),getline(iefs,numline)){//index索引
		istringstream snumline(numline);
		while(snumline >> linenum){
			_index_table[aword].insert(linenum);
		}
	}
	while(getline(icfs,aword),getline(icfs,numline)){//index中文索引
		cout << aword << endl;
		istringstream snumline(numline);
		while(snumline >> linenum){
			_index_table[aword].insert(linenum+ennum);
		}
	}
}

vector<pair<string,int>> & Mydict::getDict(){
	return _dict;
}

unordered_map<string,set<int>> & Mydict::getIndexTable(){
	return _index_table;
};

Mydict * Mydict::_getclass = createInstance();
Mydict::AutoRelease Mydict::_auto;


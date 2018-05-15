///
/// @file    Mydict.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-15 10:03:09
///

#include "Mydict.h"

void Mydict::init(const char * dictEnPath,const char * indexEnPath){
	fstream defs(dictEnPath);
	fstream iefs(indexEnPath);
	string aline;
	string aword;
	int afrequent;
	while(getline(defs,aline)){
		istringstream sline(aline);
		sline >> aword;
		sline >> afrequent;
		_dict.push_back(make_pair(aword,afrequent));
	}
	
	string numline;
	string tmpnull;
	int linenum;
	while(true){
		getline(iefs,aword);
		getline(iefs,numline);
		istringstream snumline(numline);
		while(snumline >> linenum){
			_index_table[aword].insert(linenum);
		}
	}
}

vector<pair<string,int>> & Mydict::getDict(){
	return _dict;
}

unordered_map<string,set<int>> & Mydict::getIndexTable(){
	return _index_table;
};

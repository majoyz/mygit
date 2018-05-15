 ///
 /// @file    MakeIndex.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 22:17:11
 ///
 
#include "MakeIndex.h"

MakeIndex::MakeIndex(vector<pair<string,int>> & qdict){
	auto it = qdict.begin();
	string tmp;
	string ctmp;
	int dictnum = 0;
	while(it!=qdict.end()){
		tmp = (*it).first;
		for(unsigned long i = 0;i<tmp.size();i++){
			ctmp = tmp[i];
			_index[ctmp].insert(dictnum);
		}
		++dictnum;
		++it;
		cout << "finish" << ctmp << endl;
	}
}

void MakeIndex::indexFile(){
	ofstream ofs("index");
	for(auto every : _index){
		ofs << every.first << endl;
		for(auto everynum : every.second){
			ofs << everynum << " ";
		}
		ofs << endl;
		ofs << endl;
	}
}

 ///
 /// @file    MakeIndex.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 15:08:20
 ///
 
#ifndef __WD_MAKEINDEX_H__
#define __WD_MAKEINDEX_H__

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

class MakeIndex{
	public:
		MakeIndex(vector<pair<string,int>>&);
		void indexFile();
	private:
		unordered_map<string,set<int>> _index;
};

#endif

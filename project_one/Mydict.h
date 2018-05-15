 ///
 /// @file    Mydict.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-15 09:47:27
 ///
 
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <utility>
using namespace std;

class Mydict{
	public:
		static Mydict * createInstance(){
			if(_getclass == NULL){
				_getclass = new Mydict;
			}
			return _getclass;
		}
		void init(const char * dictEnPath,const char * dictCnPath);
		vector<pair<string,int>> & getDict();
		unordered_map<string,set<int>> & getIndexTable();
	private:
		Mydict();
		static Mydict * _getclass;
		vector<pair<string,int>> _dict;
		unordered_map<string,set<int>> _index_table;
};

Mydict * Mydict::_getclass = NULL;

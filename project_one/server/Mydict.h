 ///
 /// @file    Mydict.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-15 09:47:27
 ///
 
#ifndef __WD_MYDICT_H__
#define __WD_MYDICT_H__

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
	class AutoRelease{
		public:
			AutoRelease(){}
			~AutoRelease(){
				if(_getclass){
					delete _getclass;
				}
			}
	};
	public:
		static Mydict * createInstance(){
			if(_getclass == NULL){
				_getclass = new Mydict;
			}
			return _getclass;
		}
		void init(const char *,const char *,const char *,const char *);
		vector<pair<string,int>> & getDict();
		unordered_map<string,set<int>> & getIndexTable();
	private:
		Mydict();
		~Mydict();
		static Mydict * _getclass;
		static AutoRelease _auto;
		vector<pair<string,int>> _dict;
		unordered_map<string,set<int>> _index_table;
};

//extern Mydict * Mydict::_getclass;

#endif

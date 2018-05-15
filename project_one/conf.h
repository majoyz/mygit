 ///
 /// @file    conf.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-14 11:02:41
 ///
 
#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class Configuration{
	public:
		Configuration(const string & filepath);
		map<string,string> & getConfigMap();
	private:
		string _filepath;
		map<string,string> _configMap;
};

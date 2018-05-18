///
/// @file    conf.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-14 11:05:59
///

#include "conf.h"

Configuration::Configuration(const string & filepath)
	:_filepath(filepath)
{
	fstream fs(_filepath);
	if(!fs.is_open()){
		cout << "open false" << endl;
		return;
	}
	char tmp[256] = {0};
	string tmpkey;
	string tmpvalue;
	while(!fs.eof()){
		fs.getline(tmp,256);
		string line(tmp);
		size_t pos = line.find("=");
		if(pos == string::npos){
			cout << "read false or finish" << endl;
			return;
		}
		tmpkey = line.substr(0,pos);
		tmpvalue = line.substr(pos+1);
		_configMap.insert(make_pair(tmpkey,tmpvalue));
	}
	fs.close();
}

map<string,string> & Configuration::getConfigMap(){
	return _configMap;
}

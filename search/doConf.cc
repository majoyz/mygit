///
/// @file    doConf.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-29 11:54:07
///

#include <iostream>
#include <string>  
#include <fstream>  
using namespace std;

static bool readConfigFile(const char * cfgfilepath, const string & key, string & value)  
{  
	fstream cfgFile;  
	cfgFile.open(cfgfilepath);//打开文件      
	if( ! cfgFile.is_open())  
	{  
		cout<<"can not open cfg file!"<<endl;  
		return false;  
	}  
	char tmp[1000];  
	while(!cfgFile.eof())//循环读取每一行  
	{  
		cfgFile.getline(tmp,1000);//每行读取前1000个字符，1000个应该足够了  
		string line(tmp);  
		size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value  
		if(pos==string::npos) return false;  
		string tmpKey = line.substr(0,pos);//取=号之前  
		if(key==tmpKey)  
		{  
			value = line.substr(pos+1);//取=号之后  
			return true;  
		}  
	}  
	return false;  
}  

 ///
 /// @file    main.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 16:17:39
 ///
 
#include "MakeDict.h"
#include "conf.h"
#define CONFPATH "../conf/my.conf"

void makeDict(){
	Configuration config(CONFPATH);
	ifstream firText("../bin/english.txt");
	ifstream secText("../bin/The_Holy_Bible.txt");
	TextQuery textquery(config.getConfigMap()["mydict"],config.getConfigMap()["myindex"]);
	textquery.addBinTxt(firText);
	textquery.addBinTxt(secText);
	textquery.makeDict();//建立词典文件
	textquery.makeQDict();//存到vector里面去
	firText.close();
	secText.close();
	textquery.makeIndex();
	textquery.indexFile();
}

int main(){
	makeDict();
	
	return 0;
}

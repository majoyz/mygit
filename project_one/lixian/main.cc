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
	ifstream firText("../lib/english.txt");
	ifstream secText("../lib/The_Holy_Bible.txt");
	DictProducer textquery(config.getConfigMap()["mydict"],config.getConfigMap()["myindex"]);
	textquery.makeDict(firText);
	textquery.makeDict(secText);
	textquery.dictFile();//建立词典文件
	firText.close();
	secText.close();
	textquery.makeIndex();
	textquery.indexFile();
}

void makeDict_cn(){
	Configuration config(CONFPATH);
	SplitTool *st = new SplitToolCppJieba;
	ifstream firText("../lib/art/C3-Art0039.txt");
	DictProducer dpcn(config.getConfigMap()["mydictcn"],config.getConfigMap()["myindexcn"],st);
	dpcn.make_cn_Dict(firText);
	dpcn.dict_cn_File();
	firText.close();
	dpcn.make_cn_Index();
	dpcn.index_cn_File();
}

int main(){
	makeDict();
	makeDict_cn();
	
	return 0;
}

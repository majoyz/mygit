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
	ifstream firText1("../lib/art/C3-Art0002.txt");
	ifstream firText2("../lib/art/C3-Art0003.txt");
	ifstream firText3("../lib/art/C3-Art0005.txt");
	ifstream firText4("../lib/art/C3-Art0007.txt");
	ifstream firText5("../lib/art/C3-Art0009.txt");
	ifstream firText6("../lib/art/C3-Art0011.txt");
	ifstream firText7("../lib/art/C3-Art0013.txt");
	ifstream firText0("../lib/stop-words-list/stop_words_zh.txt");
	DictProducer dpcn(config.getConfigMap()["mydictcn"],config.getConfigMap()["myindexcn"],st);
	dpcn.make_cn_Dict(firText0);
	dpcn.make_cn_Dict(firText1);
	dpcn.make_cn_Dict(firText2);
	dpcn.make_cn_Dict(firText3);
	dpcn.make_cn_Dict(firText4);
	dpcn.make_cn_Dict(firText5);
	dpcn.make_cn_Dict(firText6);
	dpcn.make_cn_Dict(firText7);
	dpcn.dict_cn_File();
	firText0.close();
	firText1.close();
	firText2.close();
	firText3.close();
	firText4.close();
	firText5.close();
	firText6.close();
	firText7.close();
	dpcn.make_cn_Index();
	dpcn.index_cn_File();
}

int main(){
	makeDict();
	makeDict_cn();
	
	return 0;
}

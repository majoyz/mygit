///
/// @file    getPagelib.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2018-04-22 10:06:05
///

#include "tinyxml2.h"

#include <regex>
#include <iterator>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using namespace tinyxml2;
using std::regex;

#define OPATH "pagelib.dat"

struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};

class RssReader
{
	public:
		RssReader(){
			_rss.reserve(10);
		}
		void parseRss(const char *);//解析
		void dump();//输出

	private:
		vector<RssItem> _rss;
		int _i;
};

void RssReader::parseRss(const char * arg){//解析
	XMLDocument doc;
	string tmp;
	string tmpdes1,tmpdes2;
	regex r("<.{0,999}>");
	regex re("&.{0,99};");
	struct RssItem tmpst;
	int i=0;
	int res = doc.LoadFile(arg);
	if(res!=0){
		cout << "load xml file failed" << endl;
		return;
	}

	XMLElement* root = doc.RootElement();
	XMLElement* channelroot = root->FirstChildElement("channel");
	XMLElement* docone = channelroot->FirstChildElement("item");
	XMLElement* everynode;
	while(docone){
		everynode = docone->FirstChildElement("title");
		tmp = everynode->GetText();
		tmpst.title = tmp;
		everynode = docone->FirstChildElement("link");
		tmp = everynode->GetText();
		tmpst.link = tmp;
		everynode = docone->FirstChildElement("description");
		tmpdes1 = everynode->GetText();
		tmpdes2 = regex_replace(tmpdes1,r,"");
		tmp = regex_replace(tmpdes2,re,"");
		tmpst.description = tmp;
		everynode = docone->FirstChildElement("content");
		if(everynode){
			tmp = everynode->GetText();
			cout << tmp << endl;
			_rss[i].content = tmp;
		}
		_rss.push_back(tmpst);
		++i;
		docone = docone->NextSiblingElement();
	}
	RssReader::_i = i;
	return;
}

void RssReader::dump(){//输出
	XMLDocument doc;
	int res = doc.LoadFile(OPATH);
	if(res!=0){
		cout << "load xml file failed" << endl;
		return;
	}
	XMLElement * root;
	for(int i = 0;i<RssReader::_i;i++){
		root = doc.NewElement("doc");//从加载的xml文件里取根//不不不，改成每次新建一个根doc
		doc.InsertEndChild(root);

		XMLElement * docid = doc.NewElement("docid");
		char tmpi[2];
		sprintf(tmpi,"%d%s",i+1,"\0");
		docid->InsertEndChild(doc.NewText(tmpi));
		root->InsertEndChild(docid);

		XMLElement * title = doc.NewElement("title");
		title->InsertEndChild(doc.NewText(_rss[i].title.c_str()));
		root->InsertEndChild(title);

		XMLElement * link = doc.NewElement("link");
		link->InsertEndChild(doc.NewText(_rss[i].link.c_str()));
		root->InsertEndChild(link);

		XMLElement * description = doc.NewElement("description");
		description->InsertEndChild(doc.NewText(_rss[i].description.c_str()));
		root->InsertEndChild(description);

		XMLElement * content = doc.NewElement("content");
		content->InsertEndChild(doc.NewText(_rss[i].content.c_str()));
		root->InsertEndChild(content);
	}
	doc.SaveFile(OPATH);
	return;
}

int creatXML(const char * xmlPath){
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	XMLDocument doc;
	doc.Parse(declaration);
	return doc.SaveFile(xmlPath);
}

int main(int argc,char * argv[]){
	if(argc!=2){
		cout << "rssfile" << endl;
		return -1;
	}
	creatXML(OPATH);
	RssReader rssa;
	rssa.parseRss(argv[1]);
	rssa.dump();

	return 0;
}

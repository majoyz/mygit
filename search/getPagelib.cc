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
		void parseRss();//解析
		void dump();//输出

	private:
		vector<RssItem> _rss;
};

void RssReader::parseRss(){//解析
	XMLDocument doc;
	string tmp;
	struct RssItem tmpst;
	int i=0;
	int res = doc.LoadFile("rss/36kr.xml");
	if(res!=0){
		cout << "load xml file failed" << endl;
		return;
	}

    XMLElement* root = doc.RootElement();
    XMLElement* channelnode = root->FirstChildElement("channel");
    XMLElement* docnode = channelnode->FirstChildElement("item");
	while(docnode){
    XMLElement* querynode = docnode->FirstChildElement("title");
	tmp = querynode->GetText();
	tmpst.title = tmp;
	cout << tmpst.title << endl;
    querynode = docnode->FirstChildElement("link");
	tmp = querynode->GetText();
	cout << tmp << endl;
	tmpst.link = tmp;
    querynode = docnode->FirstChildElement("description");
	tmp = querynode->GetText();
	cout << tmp << endl;
	tmpst.description = tmp;
//	querynode = docnode->FirstChildElement("content");
//	tmp = querynode->GetText();
//	cout << tmp << endl;
//	_rss[i].content = tmp;
	_rss.push_back(tmpst);
	++i;
	docnode = docnode->NextSiblingElement();
	}
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
for(int i = 0;i<10;i++){
	root = doc.NewElement("doc");//从加载的xml文件里取根//不不不，改成每次新建一个根doc
	doc.InsertEndChild(root);

	XMLElement * docid = doc.NewElement("docid");
	//	docid->SetAttribute("ID",i);
	char tmpi[2];
	sprintf(tmpi,"%d%s",i+1,"\0");
	docid->InsertEndChild(doc.NewText(tmpi));
	root->InsertEndChild(docid);

	XMLElement * title = doc.NewElement("title");
	title->InsertEndChild(doc.NewText(_rss[i].title.c_str()));
	root->InsertEndChild(title);
	cout << _rss[i].title << endl;

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

	//	XMLElement * root=doc.NewElement("doc");
	//	doc.InsertEndChild(root);

	return doc.SaveFile(xmlPath);
}
#if 0
int insertXMLNode(const char * xmlPath,const RssItem & rssitem,int i){//插入一个doc
	XMLDocument doc;
	int res = doc.LoadFile(xmlPath);
	if(res!=0){
		cout << "load xml file failed" << endl;
		return res;
	}

	XMLElement * root = doc.NewElement("doc");//从加载的xml文件里取根//不不不，改成每次新建一个根doc
	doc.InsertEndChild(root);

	XMLElement * docid = doc.NewElement("docid");
	//	docid->SetAttribute("ID",i);
	char tmpi[2];
	sprintf(tmpi,"%d%s",i,"\0");
	docid->InsertEndChild(doc.NewText(tmpi));
	root->InsertEndChild(docid);

	XMLElement * title = doc.NewElement("title");
	title->InsertEndChild(doc.NewText(rssitem.title.c_str()));
	root->InsertEndChild(title);

	XMLElement * description = doc.NewElement("description");
	description->InsertEndChild(doc.NewText(rssitem.description.c_str()));
	root->InsertEndChild(description);

	XMLElement * content = doc.NewElement("content");
	content->InsertEndChild(doc.NewText(rssitem.content.c_str()));
	root->InsertEndChild(content);

	return doc.SaveFile(xmlPath);
}

int try_pipei(const char * rootfile){
	XMLDocument doc;
	string tmp;
	int res = doc.LoadFile(rootfile);
	if(res!=0){
		cout << "load xml file failed" << endl;
		return res;
	}

    XMLElement* root = doc.RootElement();
    XMLElement* channelnode = root->FirstChildElement("channel");
    XMLElement* docnode = channelnode->FirstChildElement("item");
	while(docnode){
    XMLElement* querynode = docnode->FirstChildElement("title");
	tmp = querynode->GetText();
	cout << tmp << endl;
    querynode = docnode->FirstChildElement("link");
	tmp = querynode->GetText();
	cout << tmp << endl;
    querynode = docnode->FirstChildElement("description");
	tmp = querynode->GetText();
	cout << tmp << endl;
//	querynode = docnode->FirstChildElement("content");
//	tmp = querynode->GetText();
//	cout << tmp << endl;
	docnode = docnode->NextSiblingElement();
	}
	return 0;

//	string tmp,xml;
//	ifstream ifs(rootfile);
//	while(getline(ifs,tmp)){
//		tmp += "\n";
//		xml += tmp;
//	}
//
//	string pattern("<.{0,9}>");
//	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
//	regex r(pattern);
//	for (std::sregex_iterator it(xml.begin(), xml.end(), r), end;//end是尾后迭代器，regex_iterator是regex_iterator的string类型的版本
//			it != end;
//			++it)
//	{
//		std::cout << it->str() << std::endl;
//	}
}


int main(){
	creatXML(OPATH);
	struct RssItem rssitem;
	rssitem.title = "Ceshi";
	rssitem.link = "https://www.baidu.com";
	rssitem.description = "I'm baidu";
	rssitem.content = "I have all";
	insertXMLNode(OPATH,rssitem,1);

	struct RssItem rssitem2;
	rssitem2.title = "Ceshi2";
	rssitem2.link = "https://www.google.com";
	rssitem2.description = "I'm google";
	rssitem2.content = "I have all";
	insertXMLNode(OPATH,rssitem2,2);

//	try_pipei("rss/36kr.xml");
	return 0;
}
#endif

int main(){
	creatXML(OPATH);
	RssReader rssa;
	rssa.parseRss();
	rssa.dump();

	return 0;
}

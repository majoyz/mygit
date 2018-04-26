 ///
 /// @file    RssReader.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 15:02:42
 ///
 
#include "tinyxml2.h"
//#include "Mylogger.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <regex>
using std::cout;
using std::endl;
using std::string;

 
void test0(void)
{
	using namespace tinyxml2;
	
	XMLDocument doc;
	doc.LoadFile("coolshell.xml");

	XMLElement * proot = doc.FirstChildElement("rss");
	XMLElement * pchannel = proot->FirstChildElement("channel");
	XMLElement * pitem = pchannel->FirstChildElement("item");
	XMLElement * ptitle = pitem->FirstChildElement("title");
	XMLElement * plink = pitem->FirstChildElement("link");
	XMLElement * pdescription = pitem->FirstChildElement("description");
	XMLElement * pcontent = pitem->FirstChildElement("content:encoded");

	string title;
	string link;
	string descriptition;
	string content;
	if(ptitle) title = string(ptitle->GetText());
	if(plink) link = string(plink->GetText());
	if(pdescription) descriptition = string(pdescription->GetText());
	if(pcontent) content = string(pcontent->GetText());

	cout << "tile:" << title << endl
		 << "link:" << link << endl
		 << "descriptition:" << descriptition << endl;
		 //<< "content:" << content << endl;
	//std::regex re("</?[^>]+>");
	boost::regex re("<.+?>");
	cout << endl;
	cout << boost::regex_replace(content, re, string()) << endl;
	int cnt = 1;

	string page = 
		"<doc>\n"
		"   <docid>" + std::to_string(cnt) + "</docid>\n"
		"	<title>" + title + "</title>\n"
		"	<link>"  + link + "</link>\n"
		"	<content>" + content + "</content>\n"
		"</doc>\n";
}

void test2(void)
{
	string s1 = "I Don't Know";
	cout << boost::to_upper_copy(s1) << endl;
}

int main(void)
{
	//test0();
	test2();

	return 0;
}

///
/// @file    pageLib.cpp
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-21 21:26:27
///

#include "pageLib.h"
#include "tinyxml2.h"

#include <boost/regex.hpp>

PageLib::PageLib(Configuration & conf,DirScanner & dirScanner)
	:_conf(conf)
	 ,_dirScanner(dirScanner)
{}

void PageLib::create(){
	using namespace tinyxml2;
	int docid = 1;
	int itemplace = 0;
	XMLDocument doc;
	for(auto every : _dirScanner.files()){
		doc.LoadFile(every.c_str());

		XMLElement * proot = doc.FirstChildElement("rss");
		XMLElement * pchannel = proot->FirstChildElement("channel");
		XMLElement * pitem = pchannel->FirstChildElement("item");
		while(pitem){
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

			string page = 
				"<doc><docid>" + std::to_string(docid) + 
				"</docid><url>"  + link + 
				"</url><title>" + title + 
				"</title><content>" + content + 
				"</content></doc>";
			_vecFilefiles.push_back(page);

			++docid;
			pitem = pitem->NextSiblingElement();
		}
	}
}

#include "tinyxml2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;
using namespace tinyxml2;
typedef struct RssItem {
    string title;
    string link;
    string description;
    string content;
} RssItem;
class RssReader {
public:
    //RssReader();

    void parseRss(const char*);
    void dump(const char*);
    string getString(XMLElement*, const char*);
private:
    string rePlace(const string &);
    vector<RssItem> _rss;
};

string RssReader::rePlace(const string& str)
{
    //string s="&lt;[[:alpha:]]*&gt;";
    string s="<.{0,9}>";
    regex r(s);
    string fmt("");
    return regex_replace(str,r,fmt);
}

void RssReader::parseRss(const char* filename)
{
    XMLDocument doc;
    doc.LoadFile(filename);
    XMLElement* root = doc.RootElement();
    XMLElement* channelnode = root->FirstChildElement("channel");
    XMLElement* docnode = channelnode->FirstChildElement("item");
    while (docnode) {
        RssItem rss;
        rss.title =rePlace(getString(docnode, "title"));
        rss.link = rePlace(getString(docnode, "link"));
        rss.description = rePlace(getString(docnode, "description"));
        rss.content = rePlace(getString(docnode, "content:encoded"));
        _rss.push_back(rss);
        docnode = docnode->NextSiblingElement();
    }
}

void RssReader::dump(const char* filename)
{
    XMLDocument doc;
    int docid=0;
    char id[10]={0};
    for (auto i = _rss.begin(); i != _rss.end(); i++) {
        bzero(id,sizeof(id));
        XMLElement* docnode = doc.NewElement("doc");
        doc.InsertEndChild(docnode);
        
        sprintf(id,"%d",++docid);
        XMLElement* docidnode=doc.NewElement("docid");
        docidnode->InsertEndChild(doc.NewText(id));
        docnode->InsertEndChild(docidnode);

        XMLElement* titlenode=doc.NewElement("title");
        titlenode->InsertEndChild(doc.NewText(i->title.c_str()));
        docnode->InsertEndChild(titlenode);

        XMLElement* linknode=doc.NewElement("link");
        linknode->InsertEndChild(doc.NewText(i->link.c_str()));
        docnode->InsertEndChild(linknode);

        XMLElement* descriptionnode=doc.NewElement("description");
        descriptionnode->InsertEndChild(doc.NewText(i->description.c_str()));
        docnode->InsertEndChild(descriptionnode);

        XMLElement* contentnode=doc.NewElement("content");
        contentnode->InsertEndChild(doc.NewText(i->content.c_str()));
        docnode->InsertEndChild(contentnode);
    }
    doc.SaveFile(filename);
}


string RssReader::getString(XMLElement* docnode, const char* query)
{
    XMLElement* querynode = docnode->FirstChildElement(query);
    if (querynode)
        return querynode->GetText();
    else
        return "\0";
}
int main(int argc,char **argv)
{
    RssReader rr;
    rr.parseRss(argv[1]);
    rr.dump("pagelib.dat");
    return 0;
}

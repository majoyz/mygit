 ///
 /// @file    webPage.cpp
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-22 15:59:31
 ///
 
#include "webPage.h"
#include "boost/regex.hpp"

WebPage::WebPage(string & doc,Simhasher & simhasher,SplitToolCppJieba & jieba)
:_doc(doc)
{
#if 0
	Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
    size_t topN = 20;
    uint64_t u64 = 0;
    string _docContent("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
    vector<pair<string ,double> > res;
	cout << "problem 0" << endl;
    simhasher.extract(_docContent, res, topN);
	cout << "problem 1" << endl;
    simhasher.make(_docContent, topN, u64);
    cout << "关键词序列是: " << res << endl;
    cout<< "simhash值是: " << u64<<endl;
#endif
	boost::regex getDocid("(?<=<docid>).*?(?=</docid>)");
	boost::regex getTitle("(?<=<title>).*?(?=</title>)");
	boost::regex getUrl("(?<=<url>).*?(?=</url>)");
	boost::regex getContent("(?<=<content>).*?(?=</content>)");
	boost::smatch result;
	boost::regex_search(_doc,result,getDocid);
	cout << result[0].str() << endl;
	_docId = stoi(result[0].str());
	boost::regex_search(_doc,result,getTitle);
	_docTitle = result.str();
	cout << _docTitle << endl;
	boost::regex_search(_doc,result,getUrl);
	_docUrl = result.str();
	//cout << _docUrl << endl;
	boost::regex_search(_doc,result,getContent);
	_docContent = result.str();
	//cout << _docContent << endl;
//	Simhasher simhasher1("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
//	string docContent("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
    size_t topN = TOPK_NUMBER;
    uint64_t u64 = 0;
    vector<pair<string ,double> > res;
	cout << "problem 0" << endl;
    simhasher.extract(_docContent, res, topN);
	cout << "problem 1" << endl;
    simhasher.make(_docContent, topN, u64);
	_simhash = u64;
    cout << "关键词序列是: " << res << endl;
    cout<< "simhash值是: " << u64<<endl;

	vector<string> tmpmap = jieba.cut(_docContent);
	for(auto every : tmpmap){
		++_wordsMap[every];
	}
}

int WebPage::getDocId(){
	return _docId;
}

string WebPage::getDoc(){
	return _doc;
}

uint64_t WebPage::getSimhash(){
	return _simhash;
}

bool operator==(WebPage & lhs,WebPage & rhs){
	return simhash::Simhasher::isEqual(lhs.getSimhash(),rhs.getSimhash());
}

bool operator<(WebPage & lhs,WebPage & rhs){//对文档按docid进行排序
	return lhs.getDocId()<rhs.getDocId();
}
/*
map<string,int> & WebPage::getWordMap(){//获取文档的词频统计map
	return _wordsMap;
}
*/

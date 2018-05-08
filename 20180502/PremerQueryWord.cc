 ///
 /// @file    QueryWord.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-25 15:27:43
 ///
 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
using namespace std;

string make_plural(int ctr,const string & word,const string &ending){
	return ctr==1? word:word+ending;//复数判断是否加s
}

class QueryResult;//query的返回类型
class TextQuery{
	public:
		using line_no = vector<string>::size_type;
		TextQuery(ifstream&);
		QueryResult query(const string&) const;
	private:
		shared_ptr<vector<string>> _file; //输入文件
		//每个单词到它所在行号的集合的映射
		map<string,shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is)
: _file(new vector<string>)
{
	string text;
	while(getline(is,text)){//对文件中的每一行
		_file->push_back(text);//保存此行文本
		int n = _file->size()-1;//当前行号
		istringstream line(text);//将行文本分解为单词
		string word;
		while(line >> word){//对行重的每个单词
			auto &_lines = wm[word];//_lines是一个shared_ptr
			if(!_lines)//第一次遇到这个单词，指针为空
				_lines.reset(new set<line_no>);//分配一个新set
			_lines->insert(n);//将此行号插入set中
		}
	}
}

class QueryResult{
	friend ostream& print(ostream&,const QueryResult&);
	public:
		QueryResult(string s,
					shared_ptr<set<TextQuery::line_no>> p,
					shared_ptr<vector<string>> f):
			sought(s),_lines(p),_file(f){}
	private:
		string sought;//查询单词
		shared_ptr<set<TextQuery::line_no>> _lines;//出现的行号
		shared_ptr<vector<string>> _file;//输入文件
};

QueryResult
TextQuery::query(const string &sought) const//查询单词sought
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
		return QueryResult(sought,nodata,_file);
	else
		return QueryResult(sought,loc->second,_file);
}

ostream &print(ostream & os,const QueryResult &qr){
	os << qr.sought << " occurs" << qr._lines->size() << " "
		<< make_plural(qr._lines->size(),"time","s") << endl;
	for(auto num:*qr._lines)
		os << "(line " << num + 1 << ") "
			<< *(qr._file->begin() + num) << endl;
	return os;
}

int main(int argc,char * argv[]){
	if(argc != 2){
		cout << "query word" << endl;
		return -1;
	}

	ifstream mytext("china_daily.txt");
	string sq = argv[1];
	TextQuery tq(mytext);

	print(cout,tq.query(sq));

	return 0;
}

///
/// @file    QueryWord.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-30 15:27:43
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

class TextQuery
{
	public:
		void readFile(const string filename);
		void query(const string & word);
	private:
		vector<string> _lines;//存储文章的每一行
		map<string,set<int>> _word2Line;//存储单词的每一个所在行，不算重复
		map<string,int> _dict;//存储单词词频
};

int getOnlyWord(string & oword){//单词处理函数
	int olen = oword.size();
	while(!((oword[olen-1]>64&&oword[olen-1]<91)||(oword[olen-1]>96&&oword[olen-1]<123))){//头部处理
		oword = oword.substr(0,olen-1);
		olen--;
		if(olen==0)
			return -1;
	}
	while(!((oword[0]>64&&oword[0]<91)||(oword[0]>96&&oword[0]<123))){//尾部处理
		oword = oword.substr(1,olen-1);
		olen--;
		if(olen==0)
			return -1;
	}
//	if(oword[0]>64&&oword[0]<91){//大写处理
//		oword[0] += 32;
//	}
	return 0;
}

void TextQuery::readFile(const string filename){//读取文件
	int num_line = 0;
	string line;
	string word;
	ifstream ifs(filename);
	while(getline(ifs,line)){
		_lines.push_back(line);//存储文章的每一行
		stringstream ss;
		ss << line;
		while(ss >> word){
			int ret = getOnlyWord(word);
			if(ret==-1){
				continue;
			}
			_dict[word]++;//存储单词词频
			_word2Line[word].insert(num_line);//存储单词的每一个所在行
		}
		num_line++;
	}
}

void TextQuery::query(const string & word){//单词查询
	cout << word << " occurs " << _dict[word] << " times." << endl;
	set<int>::iterator st = _word2Line[word].begin();
	while(st != _word2Line[word].end()){
		cout << "(line " << *st+1 << ") " << _lines[*st] << endl;
		st++;
	}
}

int main(int argc,char * argv[]){
	if(argc != 2){
		cout << "query word" << endl;
		return -1;
	}
	unique_ptr<TextQuery> sptq(new TextQuery());
	sptq -> readFile("china_daily.txt");
	sptq -> query(argv[1]);

	return 0;
}

 ///
 /// @file    MakeDict.h
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-13 15:05:23
 ///
 
#include "MakeDict.h"

int getOnlyWord(string & oword){//单词处理函数
	int olen = oword.size();
	while(!((oword[olen-1]>64&&oword[olen-1]<91)||(oword[olen-1]>96&&oword[olen-1]<123))){//头部处理
		oword = oword.substr(0,olen-1);
		--olen;
		if(olen==0)
			return -1;
	}
	while(!((oword[0]>64&&oword[0]<91)||(oword[0]>96&&oword[0]<123))){//尾部处理
		oword = oword.substr(1,olen-1);
		--olen;
		if(olen==0)
			return -1;
	}
	for(int i = 0;i<olen;++i){
		if(!((oword[i]>64&&oword[i]<91)||(oword[i]>96&&oword[i]<123)))
			return -1;
		if(oword[i]>64&&oword[i]<91){//大写处理
			oword[i] += 32;
		}
	}
	return 0;
}

TextQuery::TextQuery(string &dictfile,string &indexfile)//字典类构造函数
: _file(new vector<string>)
, _dictfile(dictfile)
, _indexfile(indexfile)
{}

void TextQuery::addBinTxt(ifstream &ifile){
	string textline;
	int ret;
	int ceshi = 0;
	int n;
	while(getline(ifile,textline)){//对文件中的每一行
		_file->push_back(textline);//保存此行文本
		n = _file->size()-1;//当前行号
		istringstream line(textline);//将行文本分解为单词
		string word;
		while(line >> word){//对行重的每个单词
			ret = getOnlyWord(word);
			if(ret == -1)
				continue;
			auto &_lines = wm[word];//_lines是一个shared_ptr
			if(!_lines){//第一次遇到这个单词，指针为空
				_lines.reset(new set<line_no>);//分配一个新set
			}
			++_dict[word];
			_lines->insert(n);//将此行号插入set中
		}
		++ceshi;
		if(!(ceshi%1000))
			cout << ceshi << endl;
	}
	cout << "Text finish" << endl;
}

void TextQuery::makeDict(){//输出词典文件
	ofstream ofs(_dictfile,std::ios::app);
	for(auto & mywords : _dict){
		ofs << mywords.first << " " << mywords.second << endl;
	}
	cout << "dic finish" << endl;
	ofs.close();
}

void TextQuery::makeQDict(){//建立vector词典
	auto it = _dict.begin();
	while(it!=_dict.end()){
		_qdict.push_back(*it);
		++it;
	}
}

vector<pair<string,int>> & TextQuery::get_qdict(){//返回vector词典
	return _qdict;
}

void TextQuery::makeIndex(){//建立索引
	auto it = _qdict.begin();
	string tmp;
	string ctmp;
	int dictnum = 0;
	while(it!=_qdict.end()){
		tmp = (*it).first;
		for(unsigned long i = 0;i<tmp.size();i++){
			ctmp = tmp[i];
			_index[ctmp].insert(dictnum);
		}
		++dictnum;
		++it;
		cout << "finish" << ctmp << endl;
	}
}

void TextQuery::indexFile(){//输出索引文件
	ofstream ofs(_indexfile);
	for(auto every : _index){
		ofs << every.first << endl;
		for(auto everynum : every.second){
			ofs << everynum << " ";
		}
		ofs << endl;
	}
}

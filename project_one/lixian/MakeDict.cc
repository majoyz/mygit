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

int getOnlyCn(string & oword){
	int olen = oword.size();
	if(olen%3)
		return -1;//暂时通过3的倍数让后面的能用
	return 0;
}

DictProducer::DictProducer(string &dictfile,string &indexfile)//字典类构造函数
: _file(new vector<string>)
, _dictfile(dictfile)
, _indexfile(indexfile)
{}

DictProducer::DictProducer(string &dictfile,string &indexfile,SplitTool *st)//字典类构造函数
: _file(new vector<string>)
, _dictfile(dictfile)
, _indexfile(indexfile)
,_splitTool(st)
{}

void DictProducer::makeDict(ifstream &ifile){
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
			ret = getOnlyWord(word);//单词处理函数
			if(ret == -1)
				continue;
			auto &_lines = _wm[word];//_lines是一个shared_ptr
			if(!_lines){//第一次遇到这个单词，指针为空
				_lines.reset(new set<unsigned int>);//分配一个新set
			}
			++_dict[word];
			_lines->insert(n);//将此行号插入set中
		}
		++ceshi;
		if(!(ceshi%1000))
			cout << ceshi << endl;
	}
}

void DictProducer::make_cn_Dict(ifstream &ifile){
	string textline;
	string word;
	int ret;
	vector<string> tmpForLine;
	SplitTool *st = new SplitToolCppJieba;
	while(getline(ifile,textline)){
		istringstream line(textline);
		tmpForLine = st->cut(textline);
		for(auto every : tmpForLine){
			ret = getOnlyCn(every);
			if(ret == -1)
				continue;
			++_dict_cn[every];
		}
	}
}

void DictProducer::dictFile(){//输出词典文件
	ofstream ofs(_dictfile,std::ios::app);
	for(auto & mywords : _dict){
		ofs << mywords.first << " " << mywords.second << endl;
	}
	cout << "dic finish" << endl;
	ofs.close();
}

void DictProducer::dict_cn_File(){//输出词典文件
	ofstream ofs(_dictfile,std::ios::app);
	for(auto & mywords : _dict_cn){
		ofs << mywords.first << " " << mywords.second << endl;
	}
	cout << "dic_cn finish" << endl;
	ofs.close();
}

void DictProducer::makeIndex(){//建立索引
	auto it = _dict.begin();
	string tmp;
	string ctmp;
	int dictnum = 0;
	while(it!=_dict.end()){
		tmp = (*it).first;
		for(unsigned long i = 0;i<tmp.size();i++){
			ctmp = tmp[i];
			_index[ctmp].insert(dictnum);
		}
		++dictnum;
		++it;
	}
}

void DictProducer::make_cn_Index(){//建立中文索引
	auto it = _dict_cn.begin();
	string tmp;
	string ctmp;
	int dictnum = 0;
	while(it!=_dict_cn.end()){
		tmp = (*it).first;
		cout << "tmp = " << tmp << endl;
		for(unsigned long i = 0;i<tmp.size();i+=3){
			ctmp = tmp.substr(i,3);
			cout << "ctmp = " << ctmp << endl;
			_index[ctmp].insert(dictnum);
		}
		++dictnum;
		++it;
	}
}

void DictProducer::indexFile(){//输出中文索引文件
	ofstream ofs(_indexfile);
	for(auto every : _index){
		ofs << every.first << endl;
		for(auto everynum : every.second){
			ofs << everynum << " ";
		}
		ofs << endl;
	}
}

void DictProducer::index_cn_File(){//输出索引文件
	ofstream ofs(_indexfile);
	for(auto every : _index){
		ofs << every.first << endl;
		for(auto everynum : every.second){
			ofs << everynum << " ";
		}
		ofs << endl;
	}
}

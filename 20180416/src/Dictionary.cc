 ///
 /// @file    Dictionary.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 11:04:56
 ///

#include <string.h>
 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record
{
	Record(const string & word, int freq)
	: _word(word)
	, _freq(freq)
	{}
	string _word;
	int _freq;
};


bool operator<(const Record & lhs, const Record & rhs)
{
	return lhs._word < rhs._word;
}

class Dictionary
{
public:
	Dictionary()
	{
		_dict.reserve(1000);
	}

	void read(const string & filename)
	{
		ifstream ifs(filename);
		//ifstream ifs2(ifs);//所有的流对象都不能进行复制
		if(!ifs)
		{
			cout << "ifstream open error!" << endl;
			return;
		}

		string line;
		int cnt = 0;
		while(getline(ifs, line)) 
		{
			istringstream iss(line);
			string word;
	
			while(iss >> word)
			{
				if(isWord(word))
					processWord(word);
			}
			++cnt;
			if((cnt % 100) == 0)
			{
				cout << "cnt = " << cnt << endl;
			}
		}
		ifs.close();
		std::sort(_dict.begin(), _dict.end());
	}

	void store(const string & filename)
	{
		ofstream ofs(filename);
		if(!ofs){
			cout << "ofstream open error!" << endl;
			return;
		}
		for(auto & record : _dict)
		{
			ofs << record._word << " " << record._freq << "\n";
		}

		ofs.close();
	}
private:
	bool isWord(const string & word)
	{
		for(size_t idx = 0; idx != word.size(); ++idx)	
		{
			if(isdigit(word[idx]))
				return false;
		}
		return true;
	}

	void processWord(const string & word)
	{
		size_t idx;
		for(idx = 0; idx != _dict.size(); ++idx)
		{
			if(_dict[idx]._word == word)
			{
				++_dict[idx]._freq;
				break;
			}
		}

		if(idx >= _dict.size())
		{
			_dict.push_back(Record(word, 1));
		}
	}
private:
	vector<Record> _dict;
};
 
int main(void)
{
	Dictionary dictionary;
	dictionary.read("The_Holy_Bible.txt");
	dictionary.store("dictionary.dat");
	return 0;
}

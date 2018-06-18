 ///
 /// @file    Dictionary.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 11:04:56
 ///

#include <string.h>
 
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

class Dictionary
{
public:
	Dictionary()
	{}

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
		while(getline(ifs, line)) 
		{
			istringstream iss(line);
			string word;
	
			while(iss >> word)
			{
				if(isWord(word))
					processWord(word);
			}
#if 0
			++cnt;
			if((cnt % 100) == 0)
			{
				cout << "cnt = " << cnt << endl;
			}
#endif
		}
		ifs.close();
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
			ofs << record.first << " " << record.second << "\n";
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
		//++_dict[word];
		auto it = _dict.find(word);// O(logN)
		if(it != _dict.end())
			++(it->second);
		else{
			_dict.insert(std::make_pair(word, 1));
		}
	}

private:
	map<string, int> _dict;
};
 
int main(void)
{
	Dictionary dictionary;
	dictionary.read("The_Holy_Bible.txt");
	dictionary.store("dictionary.dat");
	return 0;
}

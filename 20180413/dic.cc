 ///
 /// @file    dic.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-13 20:58:22
 ///

#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::stringstream;

class Dictionary{
	public:
		Dictionary()
		:_sum(0)
		{
			_words.reserve(100);
			_num.reserve(100);
		}

		void read(const string & filename){
			string line;
			string word;
			ifstream ifs(filename);
			while(getline(ifs,line)){
				stringstream ss;
				ss << line;
				while(ss >> word){
					if(word[0]<49||word[0]>57){//去除数字
						for(int snum=0;snum<=_sum;snum++){//遍历已存词表
							if(word==_words[snum]){//单词已存
								_num[snum]+=1;
								break;
							}else if(snum==_sum){//单词未存
								_sum++;
								_words.push_back(word);
								_num.push_back(1);
								break;
							}
						}
					}
				}
			}
			ifs.close();
			cout << "read all" << endl;
		}

		void store(const string & filename){
			ofstream ofs(filename,std::ios::app);
			for(int i=0;i<_sum;i++){
				ofs << _words[i] << " " << _num[i] << "\n";
				cout << _words[i] << " " << _num[i] << "\n";
			}
			ofs.close();
		}
		
	private:
		vector<string> _words;
		vector<int> _num;
		int _sum;
};

int main(){
	string filename("The_Holy_Bible.txt");
	Dictionary mydic;
	mydic.read(filename);
	mydic.store("zidian.txt");
	return 0;
}

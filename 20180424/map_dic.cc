 ///
 /// @file    map_dic.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-13 20:58:22
 ///

#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
using std::stringstream;

class Dictionary{
	public:
		Dictionary()
		:_sum(0)
		{}

		void read(const string & filename){
			string line;
			string word;
			ifstream ifs(filename);
			while(getline(ifs,line)){
				stringstream ss;
				ss << line;
				while(ss >> word){
					if(word[0]<49||word[0]>57){//去除数字
						_word[word]++;
					}
				}
			}
			ifs.close();
			cout << "read all" << endl;
		}

		void store(const string & filename){
			ofstream ofs(filename,std::ios::app);
			for(auto & mywords : _word){
				ofs << mywords.first << " " << mywords.second << endl;
			}
			cout << "dic finish" << endl;
			ofs.close();
		}
		
	private:
		map<string,int> _word;
		int _sum;
};

int main(){
	string filename("The_Holy_Bible.txt");
	Dictionary mydic;
	mydic.read(filename);
	mydic.store("zidian.txt");
	return 0;
}

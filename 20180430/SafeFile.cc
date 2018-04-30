 ///
 /// @file    SafeFile.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-30 15:07:19
 ///
 
#include <iostream>
using namespace std;

class SafeFile{
	public:
		//RAII技术
		//实现原理：利用（栈）对象管理资源
		SafeFile(FILE * fp)
		:_fp(fp)
		{
			cout << "SafeFile(FILE*)" << endl;
		}

		void write(const string & msg){
			fwrite(msg.c_str(),msg.size(),1,_fp);
		}

		~SafeFile(){
			if(_fp){
				fclose(_fp);
			}
			cout << "~SafeFile(FILE*)" << endl;
		}
	private:
		FILE * _fp;
};

int main(){
	SafeFile sf(fopen("test.txt","w+"));
	sf.write("helloworld");

	return 0;
}

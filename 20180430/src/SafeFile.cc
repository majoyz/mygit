 ///
 /// @file    SafeFile.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 15:05:27
 ///
 
#include <stdio.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class SafeFile
{
public:
	//RAII技术
	//实现原理: 就是利用(栈)对象管理资源
	SafeFile(FILE * fp)
	: _fp(fp)
	{
		cout << "SafeFile(FILE*)" << endl;
	}

	void write(const string & msg)
	{
		fwrite(msg.c_str(), msg.size(), 1, _fp);
	}
	
	~SafeFile()
	{
		if(_fp)
		{
			fclose(_fp);
		}
		cout << "~SafeFile()" << endl;
	}

private:
	FILE * _fp;
};
 
int main(void)
{
	SafeFile sf(fopen("test.txt", "w+"));
	sf.write("hello,world\n");

	return 0;
}

 ///
 /// @file    deleter.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 17:42:33
 ///
 
#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;
using std::string;


struct FilePointerCloser
{
	void operator()(FILE * fp){
		if(fp)
		{
			fclose(fp);
			cout << "> fclose(fp)" << endl;
		}
	}	
};
 
void test0(void)
{
	shared_ptr<FILE> sp(fopen("test.txt", "w+"), FilePointerCloser());
	string msg("hello,world\n");
	fwrite(msg.c_str(), msg.size(), 1, sp.get());
}

void test1(void)
{
	unique_ptr<FILE, FilePointerCloser> up(fopen("test.txt", "w+"), FilePointerCloser());
	string msg("hello,world\n");
	fwrite(msg.c_str(), msg.size(), 1, up.get());
}

int main(void)
{
	test1();

	return 0;
}

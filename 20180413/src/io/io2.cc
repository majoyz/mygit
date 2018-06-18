 ///
 /// @file    io2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-13 14:38:28
 ///

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::vector;
 
int test0(void)
{
	//ifstream要求打开的文件必须存在
	ifstream ifs("io1.cc");
	if(!ifs.good())
	{
		cout << "ifstream open error!" << endl;
		return -1;
	}
	//char buff[1024] = {0};
	//ifs.getline(buff, 10);
	//ifs.read(buff, 10);
	//cout << buff << endl;
	
	vector<string> lines;
	string line;
	while(std::getline(ifs, line))
	{
		//cout << line << endl;
		lines.push_back(line);
	}

	ifs.close();
	return 0;
}

void test1(void)
{
	ifstream ifs;
	ifs.open("io1.cc");
	if(!ifs)
	{
		cout << "ifstream open error!" << endl;
		return ;
	}

	string filename("test.dat");
	ofstream ofs(filename, std::ios::out);//ofstream不需要文件存在，如果不存在，直接创建文件;
						   //如果该文件存在，直接清空文件中的内容
	if(!ofs)
	{
		cout << "ofstream open error" << endl;
		return;
	}

	string line;
	while(getline(ifs, line))
	{
		ofs << line << "\n";
	}

	ifs.close();
	ofs.close();
}

void test2(void)
{
	ofstream ofs("test.dat", std::ios::app);	
	//ofstream ofs("test.dat", std::ios::ate);	
	if(!ofs)
	{
		cout << "ofstream open error" << endl;
		return;
	}

	int pos = ofs.tellp();
	cout << "pos = " << pos << endl;

	string line("that's new line");
	ofs << line << "\n";

	ofs.close();
}

void test3(void)
{
	//ate模式是针对于输入流起作用
	ifstream ifs("test.dat", std::ios::ate);	
	if(!ifs)
	{
		cout << "ofstream open error" << endl;
		return;
	}
	int pos = ifs.tellg();
	cout << "pos = " << pos << endl;

	ifs.close();
}

void test4(void)
{
	fstream fs("wangdao.txt");
	if(!fs)
	{
		cout << "fstream open error!" << endl;
		return;
	}

	int number;
	for(size_t idx = 0; idx != 10; ++idx)
	{
		cin >> number;
		fs << number << " ";
	}
	cout << "pos = " << fs.tellg() << endl;
	//fs.seekg(0, std::ios::beg);
	fs.seekg(0);

	for(size_t idx = 0; idx != 10; ++idx)
	{
		fs >> number;
		cout << number << " ";
	}
	cout << endl;
	
	fs.close();
}


int main(void)
{
	//test1();
	//test2();
	test4();
	return 0;
}


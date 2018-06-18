 ///
 /// @file    io3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-13 16:34:08
 ///
 
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
 
void test0(void)
{
	int n1 = 10;
	int n2 = 20;

	stringstream ss;
	ss << "n1= " << n1 << " n2= " << n2;
	string str = ss.str();//得到了字符串流中的缓冲区中的数据
	cout << str << endl;

	string word;
	int number;
	while(ss >> word >> number)
	{
		cout << word << " " << number << endl;
	}
}

//将整型数据转换成字符串
string int2str(int number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

//读取配置文件
void readConfiguration(const string & filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout << "ifstream open error!" << endl;
		return;
	}
	string key;
	string value;

	string line;
	while(getline(ifs, line))
	{
		istringstream iss(line);	
		iss >> key >> value;

		cout << key << " --> " << value << endl;
	}
	
	ifs.close();
}

int main(void)
{
	//test0();
	
	int n = 100;
	string number = int2str(n);
	cout << "number = " << number << endl;

	string filename("server.conf");

	readConfiguration(filename);
	
	return 0;
}

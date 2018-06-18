 ///
 /// @file    io1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-13 11:24:41
 ///
 
#include <iostream>
#include <string>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void printStreamStatus()
{
	cout << "cin's badbit = " << cin.bad() << endl;
	cout << "cin's failbit = " << cin.fail() << endl;
	cout << "cin's eofbit = " << cin.eof() << endl;
	cout << "cin's goodbit = " << cin.good() << endl;
}
 
int test0(void)
{
#if 0
	cout << "sizeof(cin) = " << sizeof(cin) << endl;
	cout << "sizeof(cout) = " << sizeof(cout) << endl;
	printStreamStatus();
	int a;
	//流的状态如果不是good的，则该流不能正常工作
	while(cin >> a)
	{
		cout << "a = " << a << endl;
	}
	printStreamStatus();
	cin.clear();//恢复错误
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//清空缓冲区

	cout << endl;
	printStreamStatus();
#endif

	string s1;
	//while(cin >> s1)
	while(std::getline(cin, s1))//获取一行数据
	{
		//cin >> s1;//流中是有缓冲区
		cout << "s1 = " << s1 << endl;
	}
 
	//cout << "s1 = " << s1 << endl;

	return 0;
}


void test1(void)
{
	int number;
	while(cin >> number, !cin.eof())
	{
		if(cin.bad())
		{
			cout << "cin corrupted!" << endl;
			return;
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "> pls input an integer:" << endl;
			continue;
		}
		cout << "number = " << number << endl;
	}
}

int main(void)
{
	test0();
	//test1();
	return 0;
}

 ///
 /// @file    string.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 17:04:34
 ///
 
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

void test0(void)
{
	char str[] = "hello";//字符数组
	const char * pstr = "world";//C风格的字符串
	//*pstr = 'X';
	cout << "str = " << str << endl;
	cout << "pstr = " << pstr << endl;
	cout << "sizeof(str) = " << sizeof(str) << endl;
	//str = 0x010;//数组名是常量，不能修改

	char * p1 = (char *)malloc(sizeof(str) + strlen(pstr));
	strcpy(p1, str);
	strcat(p1, pstr);

	cout << "p1 = " << p1 << endl;

	for(int idx = 0; idx != sizeof(str); ++idx)
	{
		cout << str[idx] << " ";
	}
	cout << endl;

	free(p1);
}

void test1(void)
{
	using std::string;
	cout << "C++风格字符串" << endl;

	string s1 = "hello";//可以理解为把C风格的字符串转换成C++风格的字符串
	string s2 = "world";
	string s3 = s1 + s2;
	string s4;
	s4.append(s1).append(s2);//通过std::string的成员函数实现
	
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;

	//求取字符串的长度
	cout << "s4.size() = " << s4.size() << endl;
	cout << "s3.length() = " << s3.length() << endl;

	//遍历字符串的方式一
	for(size_t idx = 0; idx != s4.size(); ++idx)
	{
		cout << s4[idx] << " ";
	}
	cout << endl;
	//截取字符串中的子串
	string s5 = s4.substr(5, 3);
	cout << "s5 = " << s5 << endl;
	cout << endl;

	//字符串的比较,比较的是内容
	string s6 = s5;
	cout << "s6 = " << s6 << endl;
	cout << (s1 == s2) << endl;
	cout << (s1 != s2) << endl;
	cout << (s5 == s6) << endl;
	//把C++风格的字符串转换成C风格的字符串
	const char * p1 = s6.c_str();
	const char * p2 = s6.data();
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
}
 
int main(void)
{
	//test0();
	test1();

	return 0;
}

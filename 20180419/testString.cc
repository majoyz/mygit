 ///
 /// @file    testString.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-19 11:08:42
 ///
 
#include <iostream>
#include <string>
#include <stdio.h>
using std::cout;
using std::endl;
using std::string;

int main(){
	string s1 = "Hello";
	string s2 = s1;
	string s3 = "chaojiwudidaceshichaochang";

	printf("%p\n",s1.c_str());
	printf("%p\n",s2.c_str());
	printf("%p\n",s3.c_str());

	return 0;
}

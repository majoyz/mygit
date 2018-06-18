 ///
 /// @file    templateDefaultArg.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-20 11:12:20
 ///
 
#include <iostream>
using std::cout;
using std::endl;


template <typename T, int number = 10>
T add(T t)
{
	return t + number;
}
 
int main(void)
{
	int a = 1;
	cout << add(a) << endl;

	return 0;
}

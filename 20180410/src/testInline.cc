 ///
 /// @file    testInline.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 16:20:59
 ///
 
#include "inline.h"

#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	int a = 3, b = 4;

	cout << "a + b = " << func(a, b) << endl;
	cout << "a和b中较大的值是:" << Max(a, b) << endl;
	cout << Max(a + b, b) << endl;
	cout << getValue(a + b, b) << endl; // a + b * b
	cout << func(a + b, b) << endl;

	return 0;
}

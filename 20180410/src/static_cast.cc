 ///
 /// @file    static_cast.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 15:08:09
 ///
 
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
 
int test0(void)
{
	double d1 = 5.55;
	int a = (int)d1;
	int b = int(d1);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	return 0;
}

void test1(void)
{
	double d1 = 5.55;
	int a = static_cast<int>(d1);
	cout << "a = " << a << endl;

	int * p1 = static_cast<int *>(malloc(sizeof(int)));
	* p1 = 10;
	
	free(p1);
	//const_cast/dynamic_cast/reinterpret_cast
}

int main(void)
{
	test1();

	return 0;
}

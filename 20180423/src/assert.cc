 ///
 /// @file    assert.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 14:48:52
 ///
 
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	int * p = new int(1);
	assert(p);

	cout << "hello, world" << endl;
	delete p;
	return 0;
}

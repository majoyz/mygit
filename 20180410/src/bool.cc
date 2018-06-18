 ///
 /// @file    bool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 16:44:17
 ///
 
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	bool b1 = 0;
	bool b2 = 1;
	bool b3 = 100;
	bool b4 = -1;
	bool b5 = true;
	bool b6 = false;

	cout << "b1 = " << b1 << endl
		 << "b2 = " << b2 << endl
		 << "b3 = " << b3 << endl
		 << "b4 = " << b4 << endl
		 << "b5 = " << b5 << endl
		 << "b6 = " << b6 << endl;
	cout << "sizeof(bool) = " << sizeof(bool) << endl;

	return 0;
}

 ///
 /// @file    empty.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 09:53:38
 ///
 
#include <iostream>
using std::cout;
using std::endl;


//即使是空类，也需要占据一个字节的空间
class Empty
{
};
 
int main(void)
{
	cout << "sizeof(Empty) = " << sizeof(Empty) << endl;
	Empty e1;
	Empty e2;

	//10;//右值不能取地址
	Empty();

	return 0;
}

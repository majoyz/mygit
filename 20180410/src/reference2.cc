 ///
 /// @file    reference2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 11:40:29
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//值传递
#if 0
void swap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}
#endif

//地址传递 --> 本质还是值传递
void swap(int * px, int * py)
{
	int temp = *px;
	*px = *py;
	*py = temp;
}

//引用传递 --> 直接操作实参，更直观
void swap(int & x, int & y)
{
	int temp = x;
	x = y;
	y = temp;
}
 
int main(void)
{
	int a = 3, b = 4;
	cout << "a = " << a << endl
		 << "b = " << b << endl;
	//swap(&a, &b);
	swap(a, b);
	cout << "交换后: " << endl;
	cout << "a = " << a << endl
		 << "b = " << b << endl;
	return 0;
}

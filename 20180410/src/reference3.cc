 ///
 /// @file    reference3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 11:40:29
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//引用与指针的区别？
//相同点：都有地址的概念,引用底层实现还是指针
//
//不同点:
//	1. 引用必须要进行初始化, 而指针不一定
//	2. 引用是别名，不能单独存在；指针是独立的实体
//	3. 引用一经初始化之后，不会再改变指向；而指针可以

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



 
int test0(void)
{
	int a = 3, b = 4;
	cout << "a = " << a << endl
		 << "b = " << b << endl;
	swap(a, b);
	cout << "交换后: " << endl;
	cout << "a = " << a << endl
		 << "b = " << b << endl;
	return 0;
}

int arr[5] = {1, 2, 3, 4, 5};//全局数组

//引用作为函数的返回值, return 时不会进行复制
int & getValue(int idx)
{
	return arr[idx];
}

int getValue()
{
	int a = 10;
	return a;//return时会进行复制
}


int & func()
{
	int a = 10;
	return a;//不要返回局部变量的引用, 因为当函数执行结束之后，
			//局部变量的生命周期已经结束
}


int * func2()
{
	int a = 10;
	return &a;//
}

//不要轻易返回一个指向堆空间变量的引用
int & func3()
{
	int * p = new int(12);
	return *p;
}

void test1(void)
{
	int * p;//野指针,没有初始化的指针指向的位置就是不确定的
	//*p = 10;//error
	cout << "p = " << p << endl;
	cout << "arr[0] = " << getValue(0) << endl;

	getValue(0) = 10;
	cout << "arr[0] = " << arr[0] << endl;
}

int main(void)
{
	int * p;//野指针
	cout << "p = " << p << endl;
	test1();
	
	int & ref = func();
	//....do something
	cout << " ref = " << ref << endl;

	int & ref3 = func3();
	cout << "ref3 = " << ref3 << endl;
	delete & ref3;//不够直观


	int a = 3, b = 4;
	int c = a + func3() + b;//在表达式中执行一次func3，就会发生一次内存泄漏
	cout << "c = " << c << endl;


	return 0;
}

 ///
 /// @file    lrvalue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 11:24:01
 ///
 
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;

void display(int && m);

void display(const int & m)
{
	m;// 形参m并不能区分出实参传递过来时是左值还是右值 
}
 
int main(void)
{
	int a = 1;
	display(1);
	display(a);


	int b = 2;
	int * pflag = &a;

	&a;
	&b;
	//&(a+b);//error, 右值
	//&(a++);//error, 右值
	&(++a);
	&pflag;
	&(*pflag);

	vector<int> numbers;
	numbers.push_back(1);
	&numbers[0];
	//&100;//error 右值
	
	//&string("hello");//error
	const int & m = 1;//const引用可以绑定到右值
	const int & n = a;//const引用也可以绑定到左值
	//int & n = 1;// 非const引用不能绑定到右值
	

	//c++11提出了 右值引用, 只能绑定到右值
	
	//int && x = a;//右值引用不能绑定左值
	int && x = 1;

 
	return 0;
}

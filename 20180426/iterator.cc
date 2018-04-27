 ///
 /// @file    iterator.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-26 10:51:57
 ///
 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using namespace std;

void print(){
	cout << "print()" << endl;
}

void add(int x,int y){
	cout << x+y << endl;
}

typedef void(*Function)(void);

void test0(void)
{	
	printf("&print = %p\n",&print);
	Function f=print;//注册回调函数
	f();//执行回调函数
}

void test1()
{
	function<void()> f=print;//把function看作函数的容器
	f();
	f=print;
	f();
	auto f1=std::bind(add,7,8);
		//std_palceholders_1//占位符//后面再传参//只能占一位
		//位置问题
		//看视频
		
		//std::ref()//转换成引用值
		
		//mem_fn
		//for_each
		//remove_if
	f1();
}

int main(){

	test1();

	test0();
	return 0;

	vector<int> myvec{0,1,2,3,4,5,6,7,8,9};
	
	sort(myvec.begin(),myvec.end());
	copy(myvec.begin(),myvec.end(),ostream_iterator<int>(cout," "));
	cout << endl;

	cout << endl;

	vector<int> numbers1{1,2,3,4,5,6};
	vector<int> numbers2{3,5,7,9};
	std::set_intersection(numbers1.begin(),numbers1.end()//same element
						,numbers2.begin(),numbers2.end(),
						ostream_iterator<int> (cout , " "));
	cout << endl;
	set_difference(numbers1.begin(),numbers1.end()//different element
						,numbers2.begin(),numbers2.end(),
						ostream_iterator<int> (cout , " "));
	cout << endl;
	
	cout << endl;

	

	return 0;
}

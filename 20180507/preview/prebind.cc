 ///
 /// @file    prebind.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-05-06 19:42:58
 ///
 
#include <functional>
#include <memory>
#include <random>
#include <iostream>
using namespace std;

void f(int n1,int n2,int n3,const int &n4,int n5){
	cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1){
	return n1;
}

struct Foo{
	void print_sum(int n1,int n2){
		cout << n1 + n2 << '\n';
	}
	int _data = 10;
};

int main(){
	using namespace::placeholders;

	int n = 7;
	auto f1 = bind(f,_2,_1,42,cref(n),n);
	n = 10;
	f1(10,11,12);

	auto f2 = bind(f,_3,bind(g,_3),_3,4,5);
	f2(10,11,12);

	Foo foo;
	auto f3 = bind(&Foo::print_sum,&foo,95,_1);
	f3(5);

	auto f4 = bind(&Foo::_data,_1);
	cout << f4(foo) << '\n';

	return 0;
}

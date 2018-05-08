///
/// @file    prefunction.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-06 18:56:33
///

#include <functional>
#include <iostream>
using namespace std;

struct Foo{
	Foo(int num)
		:_num(num){}
	void print_add(int i) const
	{
		cout<<_num+i<<'\n';
	}
	int _num;
};

void print_num(int i){
	cout<<i<<'\n';
}

struct PrintNum{
	void operator()(int i) const{
		cout<<i<<'\n';
	}
};

int main(){
	function<void(int)> f_display = print_num;
	f_display(-9);

	function<void()> f_display_42 = [](){print_num(42);};
	f_display_42();

	function<void()> f_display_31 = bind(print_num,31);
	f_display_31();

	function<void(const Foo&,int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	f_add_display(foo,1);
	f_add_display(31,1);

	function<int(Foo const&)> f_num = &Foo::_num;
	cout << "num = " << f_num(foo) << '\n';

	using std::placeholders::_1;
	function<void(int)> f_add_display2 = bind(&Foo::print_add,foo,_1);
	f_add_display2(2);

	function<void(int)> f_add_display3 = bind(&Foo::print_add,&foo,_1);
	f_add_display3(3);

	function<void(int)> f_display_obj = PrintNum();
	f_display_obj(17);

	return 0;
}

 ///
 /// @file    pracTemplate.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-20 16:40:49
 ///
 
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
void show_list0(T t){
	cout << t << endl;
}

template<typename T,typename... Args>
void show_list0(T t,Args... args){
	cout << t << endl;
	show_list0(args...);
}

int main(){
	show_list0(2.15,8,"name");
	return 0;
}

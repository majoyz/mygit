 ///
 /// @file    set_map.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-24 14:29:12
 ///
 
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

void test_set(){
	
}

void test_map(){
	map<int,string> mm{
		pair<int,string> (1,"shanghai"),
		pair<int,string> (2,"shenzhen")
	};
	cout << mm[1] << mm[2] << endl;
}

int main(){
	test_map();

	return 0;
}

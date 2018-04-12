 ///
 /// @file    string.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-10 20:56:52
 ///
 
#include <iostream>
using std::cout;
using std::endl;

void test(void){
	using std::string;
	cout<<"C++风格字符串："<<endl;
	string s1="hello";
	string s2="world";
	string s3="I'm s3,";
	s3=s3+s1+s2;//字符串拼接
	string s4="I'm s4,";//字符串拼接
	s4.append(s1).append(s2);
	cout<<"s3="<<s3<<endl;
	cout<<"s4="<<s4<<endl;
	
	string s5=s4.substr(7,100);//字符串截取
	cout<<"s5="<<s5<<endl;

	string s6=s5;//字符串比较
	cout<<"s6="<<s6<<endl;
	cout<<(s1==s2)<<endl;
	cout<<(s1!=s2)<<endl;
	cout<<(s5==s6)<<endl;

	const char *p1=s6.c_str();
	const char *p2=s6.data();
	cout<<"p1="<<p1<<endl;
	cout<<"p2="<<p2<<endl;
	return;
}

int main(){
	test();
	return 0;
}

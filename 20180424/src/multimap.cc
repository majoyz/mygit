 ///
 /// @file    multimap.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-24 15:00:42
 ///
 
#include <map>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::multimap;
using std::string;
using std::pair;

template <typename Container>
void printContainer(const Container & container)
{
	for(auto & elem : container)
	{
		cout << elem.first << " --> " << elem.second << endl;
	}
}
 
void test0(void) { 
	//multimap之中不能存放关键字相同的元素,该元素是一个pair类型
	//默认情况下按关键字的升序方式进行排列
	multimap<string, int> multimapStrInt{
		pair<string,int>("hello", 66),
		std::make_pair("world", 77),
		std::make_pair("happy", 88),
		std::make_pair("good luck", 99),
		std::make_pair("happy", 88)
	};

	printContainer(multimapStrInt);

	//multimap不提供了下标访问运算符
	//cout << multimapStrInt["hello"] << endl;

	//只做查找操作
	//count 
	cout << endl;
	int ret = multimapStrInt.count("happy");
	cout << "ret = " << ret << endl;
	if(ret)
		cout << "key: hello is exist " << endl;
	else
		cout << "key is not exist" << endl;

	//find
	auto it = multimapStrInt.find("wangdao");
	if(it != multimapStrInt.end()) {
		cout << "key: hello is exist " << endl;
		cout << it->first << " --> " << it->second << endl;
	}
	else
		cout << "key is not exist" << endl;

}

void test1(void) { 
	//multimap之中不能存放关键字相同的元素
	//默认情况下按关键字的升序方式进行排列
	multimap<string, int, std::greater<string>> multimapStrInt{
		pair<string,int>("hello", 66),
		std::make_pair("world", 77),
		std::make_pair("happy", 88),
		std::make_pair("good luck", 99),
		std::make_pair("happy", 88)
	};
	printContainer(multimapStrInt);


	cout << endl << "equal_range test:" << endl;
	auto ret = multimapStrInt.equal_range("happy");
	for(;ret.first != ret.second; ++ret.first)
	{
		cout << ret.first->first << " ---> " 
			 << ret.first->second << endl;
	}
	
	cout << endl << "lower_bound/uppder_bound test:" << endl;
	auto lit = multimapStrInt.lower_bound("happy");
	auto uit = multimapStrInt.upper_bound("happy");

	cout << lit->first << " ---> " << lit->second << endl;
	cout << uit->first << " ---> " << uit->second << endl;
}
int main(void)
{
	//test0();
	//cout << endl;
	test1();
	return 0;
}

 ///
 /// @file    map.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-24 15:00:42
 ///
 
#include <map>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::map;
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
	//map之中不能存放关键字相同的元素,该元素是一个pair类型
	//默认情况下按关键字的升序方式进行排列
	map<string, int> mapStrInt{
		pair<string,int>("hello", 66),
		std::make_pair("world", 77),
		std::make_pair("happy", 88),
		std::make_pair("good luck", 99),
		std::make_pair("happy", 88)
	};

	printContainer(mapStrInt);

	//map提供了下标访问运算符
	cout << mapStrInt["hello"] << endl;// 时间复杂度为O(logN)
	//下标访问运算符执行时，若关键字存在，直接返回对应的value;
	//若关键字不存在，则会根据关键字创建一个元素(pair)
	cout << "search 'have fun' " << mapStrInt["hava fun"] << endl;
	printContainer(mapStrInt);


	//只做查找操作
	//count 
	cout << endl;
	int ret = mapStrInt.count("wangdao");
	cout << "ret = " << ret << endl;
	if(ret)
		cout << "key: hello is exist " << endl;
	else
		cout << "key is not exist" << endl;

	//find
	auto it = mapStrInt.find("wangdao");
	if(it != mapStrInt.end()) {
		cout << "key: hello is exist " << endl;
		cout << it->first << " --> " << it->second << endl;
	}
	else
		cout << "key is not exist" << endl;

}

void test1(void) { 
	//map之中不能存放关键字相同的元素
	//默认情况下按关键字的升序方式进行排列
	map<string, int, std::greater<string>> mapStrInt{
		pair<string,int>("hello", 66),
		std::make_pair("world", 77),
		std::make_pair("happy", 88),
		std::make_pair("good luck", 99),
		std::make_pair("happy", 88)
	};
	printContainer(mapStrInt);

	//查找元素
	cout << "lower_bound/upper_bound test: " << endl;
	auto lit = mapStrInt.lower_bound("happy");
	auto uit = mapStrInt.upper_bound("happy");
	cout << lit->first << " ---> " << lit->second << endl;
	cout << uit->first << " ---> " << uit->second << endl;
	
	//添加元素
	cout << "insert test" << endl;
	//std::pair<map<string, int, std::greater<string>>::iterator, bool> ret;
	auto ret = mapStrInt.insert(std::make_pair("wangdao", 100));
	if(ret.second){
		cout << "insert success" << endl;
		cout << ret.first->first << " ---> " << ret.first->second << endl;
	}
}
int main(void)
{
	//test0();
	test1();
	return 0;
}

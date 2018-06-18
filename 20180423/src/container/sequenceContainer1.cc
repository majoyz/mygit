 ///
 /// @file    sequenceContainer1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 16:55:34
 ///
 
#include <iostream>
#include <vector>
#include <list>
#include <deque>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;
 
int test0(void)
{
	int arr[5] = {10, 11, 12, 13, 14};
	//vector<int> vecInt(5, 1);
	//vector<int> vecInt(arr, arr + 4);
	vector<int> vecInt{1, 2, 3, 4};
	cout << "vector:" << endl;
	for(auto & number : vecInt)
	{	cout << number << " ";}
	cout << endl;
	cout << vecInt[3] << endl;//vector支持随机访问，其时间复杂度是O(1)
	//vector<int>::iterator it = vecInt.begin();
	auto it = vecInt.begin();
	++it;
	//vecInt.insert(it, 5);// vector的insert时间复杂度是O(N)
	cout << "vecInt'size = " << vecInt.size() << endl;
	cout << "capacity = " << vecInt.capacity() << endl;//只有vector拥有capacity方法
	vecInt.insert(it, 3, 5);//当insert方法执行结束之后，it已经失效

	it = vecInt.begin(); ++it;
	vecInt.insert(it, arr, arr + 5);
	vecInt.push_back(22);//push_back是O(1)
	it = vecInt.begin(); ++it;
	vecInt.erase(it);// 时间复杂度为O(N)
	vecInt.clear();//清空所有的元素, 但是并不会回收空间
	cout << "vecInt'size = " << vecInt.size() << endl;
	cout << "capacity = " << vecInt.capacity() << endl;

	for(auto & number : vecInt)
	{	cout << number << " ";}
	cout << endl;

	cout << endl << endl;


	list<int> liInt{1, 2, 3, 4};
	cout << "list:" << endl;
	auto lit = liInt.begin();
	liInt.insert(lit, 5);//时间复杂度为O(1)
	liInt.insert(lit, 3, 5);
	liInt.insert(lit, arr, arr + 5);

	liInt.push_front(0);
	liInt.push_back(33);

	for(auto & number : liInt)
	{	cout << number << " ";}
	cout << endl;
	//cout << liInt[0] << endl;//list并不支持随机访问
	


	deque<int> deInt{1, 2, 3, 4};
	cout << "deque:" << endl;
	auto dit = deInt.begin();
	deInt.insert(dit, 5);//时间复杂度为O(N)
	deInt.insert(dit, 3, 5);
	deInt.insert(dit, arr, arr + 5);
	deInt.push_front(0);
	deInt.push_back(33);

	for(auto & number : deInt)
	{	cout << number << " ";}
	cout << endl;
	cout << deInt[0] << endl;//deque支持随机访问

	return 0;
}

int main(void)
{
	test0();
	return 0;
}

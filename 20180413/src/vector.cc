 ///
 /// @file    vector.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-13 14:51:15
 ///
 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void printVectorCapacity(vector<int> & vec)
{
	cout << "vec's size = " << vec.size() << endl
		 << "vec's capacity = " << vec.capacity() << endl;
}


//vector是动态数组,实现原理:
//当size() == capacity(), 如果再要往数组里面添加新的元素，
//此时，就会进行动态扩容:  先申请 2 * capacity()的空间，
//然后复制原来空间里面的数据，再添加新的元素，最后释放
//原来申请的空间
 
int main(void)
{
	//int arr[10];//数组的大小是固定的
	//Point points[10];

	vector<int> numbers;
	cout << "sizeof(numbers) = " << sizeof(numbers) << endl;

	numbers.reserve(1000);//只开空间,并不会创建对象

	printVectorCapacity(numbers);

	numbers.push_back(1);
	printVectorCapacity(numbers);
	numbers.push_back(2);
	printVectorCapacity(numbers);
	numbers.push_back(3);
	printVectorCapacity(numbers);
	numbers.push_back(4);
	printVectorCapacity(numbers);
	numbers.push_back(5);
	printVectorCapacity(numbers);
	numbers.push_back(6);
	printVectorCapacity(numbers);
	numbers.pop_back();
	cout << "sizeof(numbers) = " << sizeof(numbers) << endl;
	cout << endl;

	//数组的遍历方式之一
	for(size_t idx = 0; idx != numbers.size(); ++idx)
	{
		cout << numbers[idx] << " ";
	}
	cout << endl;

	//之二:c++11的遍历方式
	for(auto & number : numbers)
	{
		cout << number << " ";
	}
	cout << endl;

	//之三: 迭代器(指针)
	vector<int>::iterator it;
	for(it = numbers.begin(); it != numbers.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}

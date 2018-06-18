 ///
 /// @file    ostream_iterator.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-25 11:16:41
 ///
 
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::ostream_iterator;
 
int main(void)
{
	vector<int> numbers{1, 2, 3, 4, 5, 6};
	//输出流迭代器 做写操作
	//
	//ostream_iterator是一个迭代器适配器
	ostream_iterator<int> osi(cout, " ");
	std::copy(numbers.begin(), numbers.end(), osi);
	cout << endl;

	return 0;
}

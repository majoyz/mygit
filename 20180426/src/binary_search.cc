 ///
 /// @file    binary_search.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-26 15:12:20
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
 
int main(void)
{
	vector<int> numbers{2, 3, 1, 4, 5, 2, 1, 6, 9, 7, 6, 2, 4, 6};
	std::sort(numbers.begin(), numbers.end());
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
	
	cout << std::boolalpha << std::binary_search(numbers.begin(), numbers.end(), 10) << endl;
	cout << std::binary_search(numbers.begin(), numbers.end(), 2) << endl << endl;

	auto it1 = std::lower_bound(numbers.begin(), numbers.end(), 2);
	auto it2 = std::upper_bound(numbers.begin(), numbers.end(), 2);
	while(it1 != it2)
	{
		cout << * it1 << ",";
		++it1;
	}
	cout << endl;

	auto ret = std::equal_range(numbers.begin(), numbers.end(), 2);
	while(ret.first != ret.second)
	{
		cout << * ret.first<< ",";
		++ret.first;
	}
	cout << endl;



	return 0;
}

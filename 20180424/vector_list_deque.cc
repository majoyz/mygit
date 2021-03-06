 ///
 /// @file    vector_list_deque.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-23 20:27:30
 ///
 
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using std::vector;
using std::list;
using std::deque;
using std::cout;
using std::endl;

void test_vector(){
	vector<int> x;
	x.push_back(0);
	cout << "x's size = " << x.size() << endl;
	cout << "x's capacity = " << x.capacity() << endl;
	int arr[5] = {2,4,6,8,10};
	auto it = x.begin();
	x.insert(it,arr,arr + 5);
	cout << "x's size = " << x.size() << endl;
	cout << "x's capacity = " << x.capacity() << endl;
	x.shrink_to_fit();
	cout << "x's size = " << x.size() << endl;
	cout << "x's capacity = " << x.capacity() << endl;
	for(auto & number : x){
		cout << number << " ";
	}
	cout << endl;
}
  
void test_list(){
	list<int> y;
	int tmp = 7;
	y.push_front(tmp);
	int arr[5] = {1,3,5,7,9};
	auto it = y.begin();
	y.insert(it,arr,arr + 5);
	it = y.begin();
	it ++;
	it ++;
	cout << *it << endl;
}

int main(){
	test_vector();
	test_list();

	return 0;
}

 ///
 /// @file    HeapSort.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-30 10:01:06
 ///
 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

template <typename T, typename Compare = std::less<T> >
class HeapSort
{
public:
	HeapSort(const vector<T> & array)
	: _array(array)
	{
	}

	void heapAjust(int idx, int size);
	void makeHeap();
	void sort();
	void display();
	
private:
	vector<T> _array;
};

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAjust(int idx, int size)
{
	int parent = idx;
	int child = 2 * parent + 1;
	Compare compare;
	while(child < size)
	{
		if(child + 1 < size && compare(_array[child], _array[child + 1]))
			++child;
		if(compare(_array[parent], _array[child]))
		{
			std::swap(_array[parent], _array[child]);
			parent = child;
			child = 2 * child + 1;
		}
		else
			break;
	}
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::makeHeap()
{
	int sz = _array.size();
	for(int idx = sz; idx >=0; --idx){
		heapAjust(idx, sz);
	}
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort(){
	makeHeap();
	for(int idx = _array.size() - 1; idx >= 0; --idx)
	{
		std::swap(_array[idx], _array[0]);
		heapAjust(0, idx);
	}
}
 
template <typename T, typename Compare>
void HeapSort<T, Compare>::display(){
	for(auto rit = _array.rbegin(); rit != _array.rend(); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;
}
int main(void)
{
	vector<int> numbers{2, 7, 26, 25, 19, 17, 1, 90, 3, 36};
	HeapSort<int> hs(numbers);
	hs.sort();
	hs.display();
	return 0;
}

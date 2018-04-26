///
/// @file    myHeapsort.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-24 20:25:29
///

#include <functional>
#include <iostream>
using std::cout;
using std::endl;

template <typename T,typename Compare = std::less<T>>
class HeapSort
{
	public:
		HeapSort(T * arr,int size);
		void heapAdjust(int start,int end,Compare compare = Compare());
		void sort();
	private:
		T * _arr;
		int _size;
		void _swap(T &x,T &y){
			T tmp = x;
			x = y;
			y = tmp;
		}
};

template <typename T,typename Compare>
HeapSort<T,Compare>::HeapSort(T * arr,int size){
	_arr = arr;
	_size = size;
}

template <typename T,typename Compare>
void HeapSort<T,Compare>::heapAdjust(int start,int end,Compare compare){
	compare = Compare();
	int dad = start;
	int son = dad * 2 + 1;
	while(son <= end){
		if(son + 1 <= end && compare(_arr[son],_arr[son + 1]))
			son++;
		if(compare(_arr[son],_arr[dad])){
			return;
		}
		else{
			_swap(_arr[dad],_arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

template <typename T,typename Compare>
void HeapSort<T,Compare>::sort(){
	for(int i = _size/2 - 1;i >= 0;i--)//调整为大根堆
		heapAdjust(i,_size - 1);
	for(int j = _size - 1;j > 0;j--){//将最大根值拍到有序尾，剩余的调整回大根堆继续
		_swap(_arr[0],_arr[j]);
		heapAdjust(0,j-1);
	}
}

int main(){
	int arr[] = {2,5,7,3,356,2,45,123,6,989,32,1,96,23,57,88,777};
	HeapSort<int> myhs(arr,sizeof(arr)/sizeof(int));
	myhs.sort();
	for(auto number : arr){
		cout << number << " ";
	}
	cout << endl;

	return 0;
}

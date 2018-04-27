//
/// @file    myVector.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-27 10:56:49
///

#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

template<typename T>
class Vector
{
	public:
		typedef T* value_type;
		typedef T* iterator;
		typedef const T* const_iterator;

		Vector()
		:_start(NULL)
		,_finish(NULL)
		,_end_of_storage(NULL)
		{}

		~Vector();

		void push_back(const T &); 
		void pop_back();

		const_iterator begin() const{
			return _start;
		}

		const_iterator end() const{
			return _finish;
		}

		size_t size() const{
			return _finish - _start;
		}

		size_t capacity() const{
			return _end_of_storage - _start;
		}
	private:
		void reallocate();//重新分配内存,动态扩容要用的
	private:    
		static std::allocator<T> _alloc;

		T * _start;//指向数组中的第一个元素
		T * _finish;//指向最后一个实际元素之后的那个元素
		T * _end_of_storage;//指向数组本身之后的位置
};

template<typename T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::~Vector(){
	while(_start != _finish)
		_alloc.destroy(--_finish);
	if(_start)
		_alloc.deallocate(_start,capacity());
}

template<typename T>
void Vector<T>::push_back(const T & value){
	if(size() == capacity())
		reallocate();
	_alloc.construct(_finish++,value);
}

template<typename T>
void Vector<T>::pop_back(){
	if(size())
		_alloc.destroy(--_finish);
	else
		cout << "no member" << endl;
}

template<typename T>
void Vector<T>::reallocate(){
	size_t cap = capacity();
	size_t newcap = cap ? cap*2 : 1;
	T * new_start = _alloc.allocate(newcap);
	if(_start){
		uninitialized_copy(_start,_finish,new_start);
		while(_start != _finish)
			_alloc.destroy(--_finish);
		_alloc.deallocate(_start,cap);
	}
	_start = new_start;
	_finish = new_start + cap;
	_end_of_storage = new_start + newcap;
}

class Point{
	public:
		Point(int ix = 0,int iy = 0)
		:_ix(ix)
		,_iy(iy)
		{
			cout << "Point(int ix = 0,int iy = 0)" << endl;
		}

		~Point(){
			cout << "~Point()" << endl;
		}

		friend ostream & operator<<(ostream & os, const Point & rhs);
	private:
		int _ix;
		int _iy;
};

ostream & operator<<(ostream & os,const Point & rhs){
	os << "(" << rhs._ix << "," << rhs._iy << ")";
	return os;
}

void printVapacity(const Vector<Point> & points){
	cout << "size = " << points.size() << endl;
	cout << "capacity = " << points.capacity() << endl;
}

void printVector(const Vector<Point> & points){
	for(auto & ps : points)
		cout << ps << " ";
	cout << endl;
}

int main(){
	Vector<Point> points;
	printVector(points);
	printVapacity(points);

	points.push_back(Point(1,2));
	printVapacity(points);
	points.push_back(Point(3,4));
	printVapacity(points);
	points.push_back(Point(5,6));
	printVapacity(points);
	points.push_back(Point(7,8));
	printVapacity(points);
	points.push_back(Point(9,10));
	printVapacity(points);
	points.pop_back();
	printVapacity(points);
	printVector(points);

	return 0;
}

 ///
 /// @file    Queue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 10:22:47
 ///
 
#include <iostream>
using std::cout;
using std::endl;



class Queue
{
public:
	Queue(int size = 10)
	: _size(size)
	, _front(0)
	, _rear(0)
	, _arr(new int[_size]())
	{}

	bool empty() const
	{
		return _front == _rear;
	}

	bool full() const
	{
		return  _front == (_rear + 1) % _size;
	}

	void push(int number)
	{
		if(full())
		{
			cout << "queue is full" << endl;
			return;
		} else
		{
			_arr[_rear++] = number;
			_rear %= _size;
		}
	}

	void pop()
	{
		if(empty())
		{
			cout << "queue is empty" << endl;
			return ;
		} else
		{
			++_front;
			_front %= _size;
		}
	}

	int front()
	{
		return _arr[_front];
	}

	int back()
	{
		return _arr[(_rear - 1 + _size) % _size];
	}

	~Queue()
	{
		delete [] _arr;
	}

private:
	int _size;
	int _front;
	int _rear;
	int * _arr;
};
 
int main(void)
{
	Queue queue;
	cout << "此时队列是否为空?" << queue.empty() << endl;
	queue.push(1);
	cout << "此时队列是否为空?" << queue.empty() << endl;

	for(int idx = 2; idx != 10; ++idx)
	{
		queue.push(idx);
	}
	cout << "此时队列是否已满?" << queue.full() << endl;

	queue.pop();
	queue.push(10);

	cout << "此时队头的元素为:" << queue.front() << endl;
	cout << "此时队尾的元素为:" << queue.back() << endl << endl;

	while(!queue.empty())
	{
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;
	cout << "此时队列是否为空?" << queue.empty() << endl;

	return 0;
}

 ///
 /// @file    templateQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-23 10:07:24
 ///
 
#include "Mylogger.h"
#include <iostream>
using std::cout;
using std::endl;


template <typename Type, int kSize = 10>
class Queue
{
public:
	Queue();
	~Queue();

	bool empty() const;
	bool full() const;
	void push(const Type & elem);
	void pop();
	Type & front();
	const Type & front() const
	{
		return _base[_front];
	}

	Type & back();
	const Type & back() const
	{
		return _base[(_rear - 1 + kSize) % kSize];
	}
private:
	int _front;
	int _rear;
	Type * _base;
};

template <typename Type, int kSize>
Queue<Type, kSize>::Queue()
: _front(0)
, _rear(0)
, _base(new Type[kSize]())
{
}

template <typename Type, int kSize>
Queue<Type, kSize>::~Queue()
{
	delete [] _base;
}

template <typename Type, int kSize>
bool Queue<Type, kSize>::empty() const
{
	return _front == _rear;
}

 
template <typename Type, int kSize>
bool Queue<Type, kSize>::full() const
{
	return _front == (_rear + 1) % kSize;
}

template <typename Type, int kSize>
void Queue<Type, kSize>::push(const Type & element)
{
	if(full())
	{
		LogInfo("queue is full, cannot push an element");	
	}
	else{
		_base[_rear++] = element;
		_rear %= kSize;
	}
}

// dnumberG
// ynumberG
template <typename Type, int kSize>
void Queue<Type, kSize>::pop()
{
	if(empty())
	{
		LogInfo("queue is empty, cannot pop an element");	
		return;
	}
	++_front;
	_front %= kSize;
}


template <typename Type, int kSize>
Type & Queue<Type, kSize>::front()
{
	return _base[_front];
}

template <typename Type, int kSize>
Type & Queue<Type, kSize>::back()
{
	return _base[(_rear - 1 + kSize) % kSize];
}

int main(void)
{
	Queue<int> queue;
	LogInfo("此时队是否为空: %d", queue.empty() );
	queue.push(1);
	LogInfo("此时队列是否为空:%d", queue.empty() );
	for(int idx = 2; idx != 12; ++idx)
	{
		queue.push(idx);
	}
	LogInfo("此时队列是否已满: %d", queue.full() );
	
	queue.pop();
	queue.push(10);
	LogInfo("此时队头的元素是:%d", queue.front());
	LogInfo("此时队尾的元素是:%d", queue.back());

	while(!queue.empty())
	{
		LogInfo("%d", queue.front());
		queue.pop();
	}
	LogInfo("此时队列是否为空:%d", queue.empty() );
	
	return 0;
}

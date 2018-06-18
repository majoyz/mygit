 ///
 /// @file    templateStack.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-20 14:45:04
 ///
 
#include "Mylogger.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename Type, size_t kSize = 10>
class Stack
{
public:
	Stack()
	: _top(-1)
	, _base(new Type[kSize]())
	{
		LogDebug("Stack()");
	}

	~Stack();
	
	//在类模板之中嵌套一个成员函数模板
	template <typename Arg>
	void display(const Arg & arg);

	bool full() const;
	bool empty() const;
	void push(const Type & type);
	void pop();
	Type top();

private:
	int _top;
	Type * _base;
};


template <typename Type, size_t kSize>
template <typename Arg>
void Stack<Type, kSize>::display(const Arg & arg)
{
	LogInfo("display()  arg = %d", arg);
}


template <typename Type, size_t kSize>
Stack<Type, kSize>::~Stack()
{
	LogDebug("~Stack()");
	delete [] _base;
}

template <typename Type, size_t kSize>
bool Stack<Type, kSize>::empty() const
{
	return _top == -1;
}

template <typename Type, size_t kSize>
bool Stack<Type, kSize>::full() const
{
	return _top == kSize - 1;
}

template <typename Type, size_t kSize>
void Stack<Type, kSize>::push(const Type & t) 
{
	if(full())
	{
		LogInfo("stack is full, can't push elments");
	}
	else
	{
		_base[++_top] = t;
	}
}


template <typename Type, size_t kSize>
void Stack<Type, kSize>::pop()
{
	if(empty())
	{
		LogInfo("stack is empty, no elments");
	}
	else
		--_top;
}

template <typename Type, size_t kSize>
Type Stack<Type, kSize>::top()
{
	return _base[_top];
}

void test0(void)
{
	//vector<int> numbers;
	Stack<int> stack;
	LogInfo("此时栈中是否为空?%d", stack.empty());
	stack.push(1);
	LogInfo("此时栈中是否为空?%d", stack.empty());

	for(size_t idx = 2; idx != 12; ++idx)
	{
		stack.push(idx);
	}
	LogInfo("此时栈中是否已满?%d", stack.full());

	while(!stack.empty())
	{
		LogInfo("%d", stack.top());
		stack.pop();
	}
	LogInfo("此时栈中是否为空?%d", stack.empty());
}

void test1(void)
{
	Stack<string> stack;
	LogInfo("此时栈中是否为空?%d", stack.empty());
	stack.push("AA");
	LogInfo("此时栈中是否为空?%d", stack.empty());

	for(size_t idx = 1; idx != 12; ++idx)
	{
		stack.push(string(2, 'A' + idx));
	}
	LogInfo("此时栈中是否已满?%d", stack.full());

	while(!stack.empty())
	{
		LogInfo("%s", stack.top().c_str());
		stack.pop();
	}
	LogInfo("此时栈中是否为空?%d", stack.empty());

	int number = 10;
	stack.display(number);
}

int main(void)
{
	test1();
	return 0;
}

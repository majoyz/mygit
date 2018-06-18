 ///
 /// @file    CharArray.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-17 14:38:02
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class CharArray
{
public:
	CharArray(int size = 16)
	: _size(size)
	, _data(new char[_size]())
	{
		cout << "CharArray()" << endl;
	}

	char & operator[](size_t idx)
	{
		//cout << "char & operator[](size_t)" << endl;
		if(idx < capacity())
		{
			return _data[idx];	
		}else
		{
			static char nullchar = '\0';	
			return nullchar;
		}
	}

	char & func(size_t idx)
	{
		if(idx < capacity())
		{
			return _data[idx];	
		}else
		{
			static char nullchar = '\0';	
			return nullchar;
		}
		
	}
	
	char & operator[](size_t idx) const
	{
		if(idx < size())
		{
			return _data[idx];	
		}else
		{
			static char nullchar = '\0';	
			return nullchar;
		}
	}

	size_t size() const
	{	return strlen(_data);}

	size_t capacity() const
	{	return _size;	}

	~CharArray()
	{
		delete [] _data;
	}
	



private:
	size_t _size;
	char * _data;
};
 
int main(void)
{
	const char * str = "hello,world";
	CharArray array(strlen(str) + 1);
	for(size_t idx = 0; idx != strlen(str); ++idx)
	{
		array[idx] = str[idx];
		//array.operator[](idx) = str[idx];
		//array.func(idx) = str[idx];
	}
	cout << "array'size() = " << array.size() << endl;

	for(size_t idx = 0; idx != array.size(); ++idx)
	{
		cout << array[idx];
	}
	cout << endl;
 
	return 0;
}

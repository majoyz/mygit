 ///
 /// @file    RAII.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-30 15:16:51
 ///
 
#include <iostream>
using namespace std;

template<typename T>
class RAII
{
	public:
		explicit
			RAII(T * pointer)
			:_pointer(pointer)
			{}

		T * operator->(){
			return _pointer;
		}

		T & pointer*(){
			return * _pointer;
		}

		T * get(){return _pointer;}

		RAII(const RAII & rhs) = delete;
		RAII & operator=(const RAII & rhs) = delete;

		~RAII(){
			if((_pointer)
					delete _pointer;
		}

	private:
		T * _pointer;
		
};

class Point
{
public:
	Pointer(int ix = 0, int iy - 0)
	:_ix(ix)
	,_iy(iy)
	{}

	~Point(){}
}

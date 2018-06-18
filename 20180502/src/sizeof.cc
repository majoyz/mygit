 ///
 /// @file    sizeof.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:12:22
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Example
{
public:
	Example(int & ref)
	: _ref(ref)
	{}
	virtual void display(){}
private:			// vfptr 8
	int _ia;        // 4
	double _db;	    // 8
	char _carr[3];  // 3
	short _sd[5];   //10
	int & _ref;     //8
	static int _if; //4
};
 
int main(void)
{
	cout << "sizeof(Example) = " << sizeof(Example) << endl;
}

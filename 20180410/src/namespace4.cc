 ///
 /// @file    namespace1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 09:53:43
 ///
 
#include <iostream>

using std::cout;//using 声明机制, 只会引入一个实体
using std::endl;

namespace B
{//名称空间之中可以无限存放实体,可以多次出现
void displayB();//函数声明
}


namespace A
{
//变量或者是函数或者是对象，都统称为命名空间中的实体
int a = 100;

void displayA()
{
	cout << "A::displayA()" << endl;
	B::displayB();
}

namespace C
{
	void displayC()
	{
		cout << "C::dispalyC()" << endl;
	}
}

}//end of namespace A

namespace B
{
int a = 10;

void displayB()
{
	cout << "B::displayB()" << endl;
	A::C::displayC();
}
}//end of namespace B


#if 0
void cout()
{
	//....
}
#endif

 
int main(void)
{
	//作用域限定符
	A::displayA();
	//A::C::displayC();

	cout << "A::a = " << A::a  << endl;
	cout << "B::a = " << B::a << endl;

	//cout();//实体的二义性

	return 0;
}

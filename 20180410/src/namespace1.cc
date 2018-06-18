 ///
 /// @file    namespace1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 09:53:43
 ///
 
#include <iostream>

using namespace std;//using编译指令

namespace A
{
//变量或者是函数或者是对象，都统称为命名空间中的实体
int a = 100;

void displayA()
{
	cout << "A::displayA()" << endl;
}


namespace C
{
	void displayC()
	{
		cout << "C::dispalyC()" << endl;
	}
}

}

namespace B
{
int a = 10;
}

 
int main(void)
{
	//作用域限定符
	A::displayA();
	A::C::displayC();

	return 0;
}

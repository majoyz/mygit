 ///
 /// @file    namespace1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 09:53:43
 ///
 
#include <iostream>

//using namespace std;//using编译指令(初学时不推荐使用)

namespace A
{
//变量或者是函数或者是对象，都统称为命名空间中的实体
int a = 100;

void displayA()
{
	std::cout << "A::displayA()" << std::endl;
}


namespace C
{
	void displayC()
	{
		std::cout << "C::dispalyC()" << std::endl;
	}
}

}

namespace B
{
int a = 10;
}


void cout()
{
	//....
	std::cout << "cout ()  --> hello,world" << std::endl;
}
 
int main(void)
{
	//作用域限定符
	A::displayA();
	A::C::displayC();


	cout();

	return 0;
}

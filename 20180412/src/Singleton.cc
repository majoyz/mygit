 ///
 /// @file    Singleton.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 16:07:04
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//单例模式: 要求一个类只能创建一个对象
//1. 该对象不能是栈对象/全局对象
//2. 该对象只能是堆对象
//
//使用场景: 
//1. 替换全局变量
//2. 字典类
//3. 配置文件

class Singleton
{
public:
	static Singleton * getInstance()
	{
		if(_pInstance == NULL)
		{
			_pInstance = new Singleton;
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
		{
			delete _pInstance;
		}
	}

private:
	Singleton(){ cout << "Singleton()" << endl;	}
	~Singleton(){	cout << "~Singleton()" << endl;	}
	
private:
	static Singleton * _pInstance;
};

Singleton * Singleton::_pInstance = NULL;

//Singleton s3;//error
 
int main(void)
{
	//Singleton s1;//error， 将构造函数私有化
	//Singleton s2;
	//...
	
	//Singleton * p1 = new Singleton;//error
	
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;

	//delete p1;//error
	Singleton::destroy();
	
	return 0;
}

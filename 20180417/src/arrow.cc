 ///
 /// @file    arrow.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-17 16:12:19
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Data
{
public:
	Data()
	{
		cout << "Data()" << endl;
	}
	void display()
	{
		cout << "Data::display()" << endl;
	}

	~Data()
	{
		cout << "~Data()" << endl;
	}
};

class SecondLayer
{
public:
	SecondLayer(Data * pdata)
	: _pdata(pdata)
	{
		cout << "SecondLayer(Data *)" << endl;
	}

	void print() 
	{
		cout << "SecondLayer::print()" << endl;
	}

	Data * getDataPtr()
	{
		return _pdata;
	}

	//指针访问运算符 必须是成员函数的形式
	//
	Data * operator->()
	{
		return _pdata;
	}

	//解引用运算符
	//推荐以成员函数的形式重载
#if 1
	Data & operator*()
	{
		return *_pdata;
	}
#endif

	//friend Data & operator*(SecondLayer & sl);

	~SecondLayer()
	{
		cout << "~SecondLayer()" << endl;
		delete _pdata;
	}
private:
	Data * _pdata;
};

//解引用访问运算符可以是友元形式
#if 0
Data & operator*(SecondLayer & sl)
{
	return *(sl._pdata);
}
#endif

class ThirdLayer
{
public:
	ThirdLayer(Data * pdata)
	:_sl(pdata)
	{
		cout << "ThirdLayer()" << endl;
	}
	
	SecondLayer & operator->()
	{
		return _sl;
	}

	~ThirdLayer()
	{
		cout << "~ThirdLayer()" << endl;
	}
	
private:
	SecondLayer _sl;
};



 
int main(void)
{
	Data * p = NULL;
	p->display();
	cout << endl;

	SecondLayer sl(new Data);//sl是对象
	//sl.print();
	
	//sl.getDataPtr()->display();
	sl->display();//但写法跟指针是一样的
	//sl.operator->()->display();
	(*sl).display();

	cout << endl;
	ThirdLayer tl(new Data);
	tl->display();

	return 0;
}

///
/// @file    virtual.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-02 10:19:47
///

#include <iostream>
using namespace std;

class Base
{
	public:
		Base(int ibase)
			:_ibase(ibase){
				cout << "Base(int)" << endl;
			}

		void func1(){
			this->display();
		}

		void func2(){
			Base::display();
		}

		virtual
			void display(){
				cout <<"Base display = "<<_ibase<<endl;
			}
	private:
		int _ibase;
};

class Derived
:public Base
{
	public:
		Derived(int ibase,int iderived)
			:Base(ibase)
			 ,_iderived(iderived)
		{
			cout <<"Derived(int,int)"<< endl;
		}

		void display(){
			cout << "derived display = " <<_iderived<< endl;
		}
		void print(){
			cout << "Derived print" << endl;
		}
	private:
		int _iderived;
};

int main(){
	Base base(1);
	base.func1();
	base.func2();
	Derived d1(10,11);
	d1.display();//静态联编，直接到代码区找相应函数，这里有隐藏
	//通过对象名调用，不表现出虚函数
	d1.print();

	Base & ref = d1;
	ref.display();//引用底层实现还是指针，动态联编
}

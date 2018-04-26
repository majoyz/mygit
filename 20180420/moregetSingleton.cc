///
/// @file    getSingleton.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2018-04-20 20:47:44
///

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Point{
	public:
		Point(int a = 0,int b = 0)
			:_a(a)
			 ,_b(b)
	{
		cout << "Point(int a = 0,int b = 0)" << endl;
	}

		~Point(){
			cout << "~Point()" << endl;
		}

		void print(){
			cout << "(" << _a << "," << _b << ")" << endl;
		}
	private:
		int _a;
		int _b;
};

class Computer{
	public:
		Computer(const char * name,int price)
			:_name(new char [strlen(name)+1]())
			 ,_price(price)
	{
		strcpy(_name,name);
		cout << "Computer(const char * name,int price)" << endl;
	}

		~Computer(){
			delete [] _name;
			cout << "~Computer" << endl;
		}

		void print(){
			cout << _name << "'s price = " << _price << endl;
		}
	private:
		char * _name;
		int _price;
};

template <class T>
class Singleton{
	public:
		class AutoRelease{
			public:
				AutoRelease(){
					cout << "AutoRelease()" << endl;
				}
				~AutoRelease(){
					if(_pInstance){
						delete _pInstance;
						cout << "~AutoRelease()" << endl;
					}
				}
		};
		template <typename... Args>
			static T * getInstance(Args... args){
				if(_pInstance == NULL){
					_auto;//这里为什么需要实例化？和typename有关吗？
					_pInstance = new T(args...);
				}
				return _pInstance;
			}

	private:
		static T * _pInstance;
		static AutoRelease _auto;
};

template <class T>
T * Singleton<T>::_pInstance = NULL;

template <typename T>
typename Singleton<T>::AutoRelease Singleton<T>::_auto;

//Point pt(3,4);

//Computer com("Mac",8888);

int main(){
	Computer * p1 = Singleton<Computer>::getInstance("Xiaomi",6666);
	Computer * p2 = Singleton<Computer>::getInstance("Xiaomi",6666);

	Point * p3 = Singleton<Point>::getInstance(1,2);
	Point * p4 = Singleton<Point>::getInstance(1,2);

	p1->print();
	printf("p1's address = %p\n",p1);
	p2->print();
	printf("p2's address = %p\n",p2);
	p3->print();
	printf("p3's address = %p\n",p3);
	p4->print();
	printf("p4's address = %p\n",p4);

	return 0;
}

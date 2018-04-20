 ///
 /// @file    1_autoRelease.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-19 17:19:49
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Singleton{
	public:
		class AutoRelease{
			public:
				AutoRelease(){
					cout << "AutoRelease()" << endl;
				}

				~AutoRelease(){
					if(_pInstance != NULL){
						delete _pInstance;
					}

					cout << "~AutoRelease()" << endl;
				}
		};
		
		static Singleton * getInstance(){
			if(_pInstance == NULL){
				_pInstance = new Singleton;
			}
			return _pInstance;
		}

	private:
		Singleton(){
			cout << "Singleton()" << endl;
		}
		~Singleton(){
			cout << "~Singleton()" << endl;
		}
	private:
		static Singleton * _pInstance;
		static AutoRelease _auto;
};

Singleton * Singleton::_pInstance = getInstance();
Singleton::AutoRelease Singleton::_auto;

int main(){
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();

	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;

	return 0;
}

 ///
 /// @file    AutoReleaseSingleton.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-18 15:09:17
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Singleton{
	class AutoRelease{
		public:
			AutoRelease(){
				cout << "AutoRelease()" << endl;
			}
			~AutoRelease(){
				if(_pInstance){
					delete _pInstance;
					cout << "~AuotRelease()" << endl;
				}
			}
	};

public:
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

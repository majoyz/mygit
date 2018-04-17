 ///
 /// @file    pack_log4cpp.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-15 20:43:46
 ///

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

class Mutex{
	public:
		static Mutex * getMutex(){
			if(XX == NULL){
				XX = new Mutex();
			}
			return XX;
		}

		void lock(){
			while(_islock){
			}
			_islock = 1;
			cout << "I have locked" << endl;
		}

		void unlock(){
			_islock = 0;
			cout << "I have unlocked" << endl;
		}
	private:
		Mutex()
		:_islock(0)
		{}
	private:
		static Mutex * XX;
		int _islock;
};

Mutex * Mutex::XX = NULL;

class Condition{
	public:
		void wait(){
		
		}

		void notify(){
		
		}

		void notifyall(){
		
		}

	private:

};

int main(){
	Mutex * ceshi = Mutex::getMutex();
	ceshi->lock();
//	ceshi->lock();
	ceshi->unlock();
	return 0;
}

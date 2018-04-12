 ///
 /// @file    zhan.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 17:04:35
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Stack
{
	public:
		Stack()
		:_top(0)
		{
		}

		bool emty(){
			if(_top==0){
				return 1;
			}else{
				return 0;
			}
		}

		bool full(){
			if(_top==10){
				return 1;
			}else{
				return 0;
			}
		}

		void push(int data){
			if(full()==0){
				_data[_top]=data;
				_top++;
			}else{
				cout<<"STACK FULL"<<endl;
				//程序终止？
			}
			cout<<"I have pushed"<<endl;
		}

		void pop(){
			if(emty()==0){
				_top--;
			}else{
				cout<<"STACK EMTY"<<endl;
			}
			cout<<"I have poped"<<endl;
		}

		int top(){
			if(emty()==0){
				cout<<"top = "<<_data[_top-1]<<endl;
				return _data[_top-1];
			}else{
				cout<<"STACK EMTY"<<endl;
				return -1;
			}
		}


	private:
		int _data[10];
		int _top;
};

int main(){
	int tmp;
	Stack mystack;
	mystack.push(10);
	mystack.push(12);
	mystack.push(14);
	tmp=mystack.top();
	mystack.pop();
	tmp=mystack.top();
}

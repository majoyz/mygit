 ///
 /// @file    myQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 20:10:14
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Queue{
	public:
		Queue()
		:_head(-1)
		,_tail(0)
		{
		}
		
		bool emty(){
			if(_tail-_head==1||_tail-_head==-9){
				return 1;
			}else{
				return 0;
			}
		}

		bool full(){
			if(_head==_tail){
				return 1;
			}else{
				return 0;
			}
		}

		void push(int data){
			if(full()){
				cout<<"QUEUE FULL"<<endl;
			}else if(_head==-1){
				_head++;
				_data[_tail]=data;
				_tail=(_tail+1)%10;
			}else{
				_data[_tail]=data;
				_tail=(_tail+1)%10;
			}
			cout<<"I have pushed"<<endl;
		}

		void pop(){
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
			}else{
				_head=(_head+1)%10;
			}
			cout<<"I have poped"<<endl;
		}

		int front(){
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
				return -1;
			}else{
				cout<<"You get front "<<_data[_head]<<endl;
				return _data[_head];
			}
		}

		int back(){
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
				return -1;
			}else{
				if(_tail==0){
					cout<<"You get back "<<_data[9]<<endl;
					return _data[9];
				}else{
					cout<<"You get back "<<_data[_tail-1]<<endl;
					return _data[_tail-1];
				}
			}
		}
	
	private:
		int _data[10];
		int _head;
		int _tail;
};

int main(){
	int tmp;
	Queue q;
	q.push(7);
	q.push(11);
	q.push(22);
	q.push(33);
	q.push(44);
	q.push(55);
	q.push(66);
	q.push(77);
	q.push(88);
	q.push(99);
	q.push(7);
	tmp=q.back();
	tmp=q.front();
	q.pop();
	q.pop();
	tmp=q.front();
	q.push(100);
	q.push(1000);
	q.push(7);
	tmp=q.back();
	tmp=q.front();
	return 0;
}

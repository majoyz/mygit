 ///
 /// @file    myQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-12 20:10:14
 ///
 
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T,size_t kSize = 10>
class Queue{
	public:
		Queue()//构造函数
		:_head(-1)
		,_tail(0)
		,_data(new T[kSize]())
		{
			cout << "Queue()" << endl;
		}

		~Queue(){
			cout << "~Queue()" << endl;
			delete [] _data;
		}
		
		bool emty(){//判空函数
			if(_tail-_head==1||_tail-_head==-9){
				return 1;
			}else{
				return 0;
			}
		}

		bool full(){//判满函数
			if(_head==_tail){
				return 1;
			}else{
				return 0;
			}
		}

		void push(const T & data){//入队函数
			if(full()){
				cout<<"QUEUE FULL"<<endl;
				return;
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

		void pop(){//出队函数
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
				return;
			}else{
				_head=(_head+1)%10;
			}
			cout<<"I have poped"<<endl;
		}

		T front(){//获取队头
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
			}else{
				cout<<"You get front "<<_data[_head]<<endl;
				return _data[_head];
			}
		}

		T back(){//获取队尾
			if(emty()){
				cout<<"QUEUE EMPTY"<<endl;
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
		T * _data;
		int _head;
		int _tail;
};

int main(){
	int tmp;
	Queue<int> q;
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


	string stmp;
	Queue<string> qs;
	qs.push("are");
	qs.push("you");
	qs.push("OK");
	qs.push("?");
	qs.push("can");
	qs.push("you");
	qs.push("play");
	qs.push("game");
	qs.push("with");
	qs.push("me");
	qs.push("?");
	stmp=qs.back();
	stmp=qs.front();
	qs.pop();
	qs.pop();
	stmp=qs.front();
	qs.push("ONE");
	qs.push("two");
	qs.push("seven");
	stmp=qs.back();
	stmp=qs.front();
	return 0;
}

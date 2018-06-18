 ///
 /// @file    observer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-05 11:10:58
 ///
 
#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::list;
using std::find;
using std::unique_ptr; 

typedef int State;
class Observer;
class Subject
{
public:
	Subject(): _state(-1){}
	void attach(Observer *);
	void detach(Observer *);
	void notify();

	virtual State getState()=0;
	virtual void setState(State state)=0;

	virtual ~Subject(){}

protected:
	State _state;
	list<Observer*> _observers;
	list<Observer*> _vipObservers;
};

class Observer
{
public:
	virtual void update(Subject *)=0;
	virtual ~Observer(){}
};

class ConcreteObserver
: public Observer
{
public:
	ConcreteObserver(): _obState(-1){
		cout << "ConcreteObserver()" << endl;
	}

	//void update(Message)		  // 观察者模式中的推模式
	void update(Subject * subject)// 观察者模式中的拉模式,消息的获取是由观察者自己决定
	{
		State _subState = subject->getState();
		if(_obState != _subState){
			_obState = _subState;
			cout << "Observer update state! state = " << _obState << endl;
		}
	}
	
	~ConcreteObserver(){
		cout << "~ConcreteObserver()" << endl;
	}

private:
	State _obState;
};



void Subject::attach(Observer * observer){
	auto it = std::find(_observers.begin(), _observers.end(), observer);
	if(it == _observers.end())
		_observers.push_back(observer);
}

void Subject::detach(Observer * observer){
	auto it = std::find(_observers.begin(), _observers.end(), observer);
	if(it != _observers.end())
		_observers.erase(it);
}

void Subject::notify(){
	cout << ">>> Subject notify all observers!" << endl;
	for(auto & observer : _observers)
	{
		observer->update(this);
	}
}

class ConcreateSubject
: public Subject
{
public:
	ConcreateSubject() {
		cout << "ConcreateSubject()" << endl;
	}

	State getState(){
		return _state;
	}
	void setState(State state)
	{
		_state = state;
		notify();
	}

	~ConcreateSubject(){
		cout << "~ConcreateSubject()" << endl;
	}
};

 
int main(void)
{
	unique_ptr<Observer> pObserve1(new ConcreteObserver());
	unique_ptr<Observer> pObserve2(new ConcreteObserver());
	unique_ptr<Observer> pObserve3(new ConcreteObserver());
	unique_ptr<Observer> pObserve4(new ConcreteObserver());

	unique_ptr<Subject> pSubject(new ConcreateSubject());

	pSubject->attach(pObserve1.get());
	pSubject->attach(pObserve2.get());
	pSubject->attach(pObserve3.get());
	pSubject->attach(pObserve4.get());
	pSubject->setState(1);

	pSubject->detach(pObserve1.get());
	pSubject->setState(2);

	return 0;
}

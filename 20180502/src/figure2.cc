 ///
 /// @file    figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:35:54
 ///
 
#include <math.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;


//基于对象的方式： std::function + std::bind
//优点: 扩展代码更方便,更灵活
//		

class Figure{
public:
	typedef std::function<void()> DisplayCallback;
	typedef std::function<double()> AreaCallback;

	void setDispalayCallback(DisplayCallback && cb)
	{	_cb1 = std::move(cb);	}
	void setAreaCallback(AreaCallback && cb)
	{	_cb2 = std::move(cb);	}

	void handleDisplayCallback()
	{
		if(_cb1)
			_cb1();
	}

	double handleAreaCallback(){
		if(_cb2)
			return _cb2();
		else
			return 0;
	}
private:
	DisplayCallback _cb1;
	AreaCallback _cb2;
};

class Rectangle
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{}
	void display(){
		cout << "rectangle:";
	}

	double area(){
		return _length * _width;	
	}
private:
	double _length;
	double _width;
};

const double PI = 3.14159;

class Circle
{
public:
	Circle(double radius)
	: _radius(radius)
	{}
	void print(){
		cout << "circle:";
	}

	double calcArea(){
		return PI * _radius * _radius;	
	}
private:
	double _radius;
};

class Triangle 
{
public:
	Triangle(double a, double b, double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}
	void show(){
		cout << "triangle:";
	}

	double statiticArea(){
		double p = (_a + _b + _c)/ 2;	
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}
private:
	double _a;
	double _b;
	double _c;
};

void printFigure(Figure & fig){
	fig.handleDisplayCallback();
	cout << fig.handleAreaCallback() << endl;
}
 
int main(void)
{
	Rectangle rectangle(10, 11);
	Circle circle(5);
	Triangle triangle(3, 4, 5);
	
	Figure figure;
	//注册回调函数
	figure.setDispalayCallback(std::bind(&Rectangle::display, &rectangle));
	figure.setAreaCallback(std::bind(&Rectangle::area, &rectangle));
	//执行回调函数
	printFigure(figure);

	figure.setDispalayCallback(std::bind(&Circle::print, &circle));
	figure.setAreaCallback(std::bind(&Circle::calcArea, &circle));
	printFigure(figure);

	figure.setDispalayCallback(std::bind(&Triangle::show, &triangle));
	figure.setAreaCallback(std::bind(&Triangle::statiticArea,  &triangle));
	printFigure(figure);

	return 0;
}

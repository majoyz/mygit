 ///
 /// @file    figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-02 11:35:54
 ///
 
#include <math.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;


//面向对象的方式： 继承 + 多态
//优点: 扩展代码很方便
//面向抽象进行编程
class Figure{
public:
	virtual void display()=0;
	virtual double area()=0;
};

class Rectangle
: public Figure
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
: public Figure
{
public:
	Circle(double radius)
	: _radius(radius)
	{}
	void display(){
		cout << "circle:";
	}

	double area(){
		return PI * _radius * _radius;	
	}
private:
	double _radius;
};

class Triangle 
: public Figure
{
public:
	Triangle(double a, double b, double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}
	void display(){
		cout << "triangle:";
	}

	double area(){
		double p = (_a + _b + _c)/ 2;	
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}
private:
	double _a;
	double _b;
	double _c;
};

void printFigure(Figure * fig){
	fig->display();
	cout << fig->area() << endl;
}

//工厂模式
//缺点: 1. 违反开放闭合原则
//		2. 违反了单一职责原则

class Factory
{
public:
	virtual Figure * create() =0;
};

class RectangleFactory
: public Factory
{
public:
	Figure * create()
	{
		//...Load xml
		//...
		return	new Rectangle(10, 11);
	}
};

class CircleFactory
: public Factory
{
public:
	Figure * create()
	{
		//...Load xml
		//...
		return new Circle (5);
	}
};

class TriangleFactory 
: public Factory
{
public:
	Figure * create()
	{
		//...Load xml
		//...
		return new Triangle(3, 4, 5);
	}
};
int main(void)
{
	//Point pt(1, 2);

	//工厂模式是针对于复杂对象的
	//
	//如果是简单对象，不需要使用工厂模式
	//
	unique_ptr<Factory> rectangleFactory(new RectangleFactory());
	unique_ptr<Figure> rectangle(rectangleFactory->create());

	unique_ptr<Factory> circleFactory(new CircleFactory());
	unique_ptr<Figure> circle(circleFactory->create());

	unique_ptr<Factory> triangleFactory(new TriangleFactory());
	unique_ptr<Figure> triangle(triangleFactory->create());

	printFigure(rectangle.get());
	printFigure(circle.get());
	printFigure(triangle.get());

	return 0;
}

 ///
 /// @file    Line.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-18 11:10:10
 ///
 
#ifndef __WD_LINE_H__
#define __WD_LINE_H__

class Line
{
public:
	Line(int x1, int y1, int x2, int y2);
	~Line();

	void display() const;

private:
	//设计模式之pimpl
	//
	//1. 实现信息隐藏
	//2. 当库需要升级的时候，可以以最小代价完成库的升级
	//3. 减小编译依赖
	class LineImpl;//类的前向声明	
private:
	LineImpl * _pImpl;
};

#endif

#pragma once
#include <iostream>
#include <vector>
using namespace System;
using namespace System::Drawing;
using namespace std;
class Entidad
{
protected:
	int x, y;
	int dx, dy;
	int width, height;
	int IDx;
	int IDy;
	bool visible;
public:
	Entidad(int width, int height)
	{
		this->width = width;
		this->height = height;
		IDx = IDy = 0;
		visible = true;
	}
	virtual void draw(){}
	virtual void move(){}
	int getX() { return x; }
	int getY() { return y; }
	int getIDy() { return IDy; }
	int getAncho() { return width; }
	int getAlto() { return height; }
	bool getVisible() { return visible; }
	void setVisible(bool v) { visible = v; }
	void setDX(int v) { dx + v; }
	void setDY(int v) { dy + v; }
	void setX(int v) { v = x; }
	void setY(int v) { v = y; }
};
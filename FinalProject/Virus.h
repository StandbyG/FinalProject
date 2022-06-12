#pragma once
#include "Entidad.h"
using namespace System::Drawing;
using namespace std; 
class Virus : public Entidad
{
private:
	int change;
public:
	Virus(int width, int height,Graphics^g) : Entidad(width,height)
	{
		x = g->VisibleClipBounds.Width-2; 
		y = rand() % 550;
		IDx = 0;
		{
			switch (change = (rand()%3))
			{
			case 0: IDy = 0, dx = rand()% 15; break;
			case 1:IDy = 1,  dx = rand() % 15; break;
			case 2:IDy = 2,  dx = rand() % 15; break;
			}
		}	
	}
	~Virus() {}
	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.5, height * 0.5);
		g->DrawImage(bmp, zoom, sectionShown, GraphicsUnit::Pixel);
	}
	void move(Graphics^ g) 
	{
		if (x > 0)
		{
			x -= dx;
			IDy = change;
		}
		IDx++;
		if (IDx > 2)IDx = 0;
	}
	Rectangle getRectangle()
	{
		return Rectangle(x, y, width * 0.5, height * 0.5);
	}
	int getXWidth() { return x + width * 0.5; }
	int getYHeight() { return y + height * 0.5; }
};
class VirusVertical : public Entidad
{
private:
	int change;
public:
	VirusVertical(int width, int height, Graphics^ g) : Entidad(width, height)
	{
		x = rand()%1500;
		y = 5;
		IDx = 0;
		{
			switch (change = (rand() % 3))
			{
			case 0: IDy = 0, dy = 4; break;
			case 1:IDy = 1, dy = 5; break;
			case 2:IDy = 2, dy = 3; break;
			}
		}
	}
	~VirusVertical() {}
	void draw(Graphics^ g, Bitmap^ bmp) 
	{
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.5, height * 0.5);
		g->DrawImage(bmp, zoom, sectionShown, GraphicsUnit::Pixel);
	}
	void move(Graphics^ g)
	{
		if (y + height * 0.5 < g->VisibleClipBounds.Height)
		{
			y += dy;
		}
		IDx++;
		if (IDx > 2)IDx = 0;
	}
	Rectangle getRectangle()
	{
		return Rectangle(x, y, width * 0.5, height * 0.5);
	}
	int getXWidth() { return x + width * 0.5; }
	int getYHeight() { return y + height * 0.5; }
};
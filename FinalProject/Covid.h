#pragma once
#include"Entidad.h"
class Covid : Entidad
{
private:
	int vidas;
public:
	Covid(int width, int height, Graphics^ g) : Entidad(width, height)
	{
		x = g->VisibleClipBounds.Width - 2;
		y = rand()%550;
		this->width = width;
		this->height = height;
		IDx = 0;
		IDy = 0; 
		dx = 2;
		vidas = 2;
	}
	void draw(Graphics^ g, Bitmap^ bmpCovid) 
	{
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.7, height * 0.7);
		g->DrawImage(bmpCovid, zoom, sectionShown, GraphicsUnit::Pixel);
	}
	void move(Graphics^ g)
	{
		if (x > 0)
		{
			x -= dx;
		}
		IDx++;
		if (IDx > 2)IDx = 0;
	}
	Rectangle getRectangle() 
	{
		return Rectangle(x, y, width * 0.7, height * 0.7);
	}
	int getVidas() { return vidas; }
	void setVidas(int v) { vidas += v;}
};
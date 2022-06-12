#pragma once
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;
class Bonificacion : public Entidad
{
private:
	int tipo;
public:
	Bonificacion(int width, int height) : Entidad(width, height)
	{
		x = rand()%1500;
		y = rand() % 600;
		this->width = width;
		this->height = height;
		IDx = 0;
		switch (tipo =(rand()%2))
		{
		case 0: IDy = 0; break;
		case 1: IDy = 1; break;
		}
	}
	void draw(Graphics^ g, Bitmap^ bmp, int cont) {
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.6, height * 0.6);
		g->DrawImage(bmp, zoom, sectionShown, GraphicsUnit::Pixel);
		if (cont > 0)
			IDx++;
		if (IDx > 7) IDx = 0;
	}
	Rectangle getRectangle()
	{
		return Rectangle(x, y, width * 0.6, height * 0.6);
	}
};
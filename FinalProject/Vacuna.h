#pragma once
#include"Entidad.h"
class Vacuna : public Entidad
{
	int direction;
public:
	Vacuna(int x, int y, int width,int height, int direction) : Entidad(width, height)
	{
		this->x = x;
		this->y = y;

		dx = 20;
		dy = 20;
		if (dx != 0)
		{
			this->width = width;
		}
		if (dy != 0)
		{
			this->height = height;
		}
		this->direction = direction;
	}
	int getY() { return y; }
	int getX() { return x; }
	void move(Graphics^ g)
	{
		if (direction == 0 && y + height * 0.3 <= g->VisibleClipBounds.Height) {
			y += dy;
			IDx = 1;
			IDy = 1;
		}
		if (direction == 3 && y >= 0) {
			y -= dy;
			IDx = 0;
			IDy = 1;
		}
		if (direction == 2 && x + width * 0.3<= g->VisibleClipBounds.Width) {
			x += dx;
			IDx = 0;
			IDy = 0;
		}
		if (direction == 1 && x >= 0) {
			x -= dx;
			IDx = 1;
			IDy = 0;
		}
	}
	void draw(Graphics^ g, Bitmap^ img)
	{
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.3, height * 0.3);
		g->DrawImage(img, zoom, sectionShown, GraphicsUnit::Pixel);
	}
	Rectangle getRectangle()
	{
		return Rectangle(x, y, width * 0.3, height * 0.3);
	}
	int getXWidth() { return x + width * 0.3; }
	int getYHeigth() { return y + height * 0.3;}
};

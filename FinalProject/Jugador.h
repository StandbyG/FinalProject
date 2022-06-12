#pragma once
#include "Entidad.h"
class Jugador : public Entidad
{
private:
	int vidas;
	int puntos;
public:
	Jugador(Bitmap^ img, int v) : Entidad(width, height)
	{
		x = 60; y = 60;
		dx = dy = 10;
		IDx = IDy = 0;
		width = img->Width / 12;
		height = img->Height / 4;
		puntos = 0;
		vidas = v;
	}
	void Move(Graphics^ g, char i)
	{
		switch (i)
		{
		case 'A':
			if (x > 0) {
				x -= dx;
				IDy = 1;
			}
			break;

		case 'D':
			if (x + width * 1.0 < g->VisibleClipBounds.Width) {
				x += dx;
				IDy = 2;
			}
			break;

		case 'W':
			if (y > 0) {
				y -= dy;
				IDy = 3;
			}
			break;

		case 'S':
			if (y + height * 1.0 < g->VisibleClipBounds.Height) {
				y += dy;
				IDy = 0;
			}
			break;
		}

		IDx++;
		if (IDx > 11)IDx = 0;
	}
	void draw(Graphics^ g, Bitmap^ bmp) 
	{
		Rectangle sectionShown = Rectangle(IDx * width, IDy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width *0.7, height * 0.7);
		g->DrawImage(bmp, zoom, sectionShown, GraphicsUnit::Pixel);
	}
	void SetVidas(int value)
	{
		vidas += value;
	}
	int GetVidas()
	{
		return vidas;
	}
	int GetPuntos()
	{
		return puntos;
	}
	void SetPuntos(int value)
	{
		puntos += value;
	}
	void SetPunto0()
	{
		puntos = 0;
	}
	Rectangle getRectangle()
	{
		return Rectangle(x, y, width *0.7, height * 0.7);
	}
};
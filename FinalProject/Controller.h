#pragma once
#include "Colecciones.h"
using namespace std;
class Controller
{
	Colecciones* cadena;	
public:
	Controller(Bitmap^ bmpj, int v, int width, int height, Graphics^ g)
	{
		cadena = new Colecciones(bmpj, v, width, height, g);
	}
	~Controller() {}

	void Draw(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpj, Bitmap^ bmpv, Bitmap^ bmpb, int cont)
	{
		cadena->drawEverything(g, bmp, bmpj, bmpv, bmpb, cont);
	}
	void Move(Graphics^ g)
	{
		cadena->moveEverything(g);
	}
	void Coli(Graphics^ g)
	{
		cadena->collision(g);
	}
	Colecciones* getColec()
	{
		return cadena;
	}
};
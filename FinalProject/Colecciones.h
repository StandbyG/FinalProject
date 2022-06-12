#pragma once
#include <vector>
#include"Bonificacion.h"
#include "Jugador.h"
#include"Vacuna.h"
#include"Virus.h"
#include "Covid.h"
using namespace std;
class Colecciones
{
	vector<Virus*> virus;
	vector<Vacuna*> vacunas;
	vector<VirusVertical*> virusv;
	vector<Bonificacion*>bonifi;
	Jugador* jugador;
	Covid* covid;
	int nivel;
public:
	Colecciones(Bitmap^ bmpj, int v, int width, int height, Graphics^ g)
	{
		jugador = new Jugador(bmpj, v);
		covid = new Covid(width, height, g);
		nivel = 1;
	}
	~Colecciones() {}
	void addVacunas(Vacuna v)
	{
		vacunas.push_back(new Vacuna(v));
	}
	void addVirus(int w, int h, Graphics^ gra, int cant)
	{
		for (int i = 0; i <= cant; ++i)
		{
			virus.push_back(new Virus(w, h, gra));
		}
	}
	void addBonificacion(int w, int h, Graphics^ gra, int cant)
	{
		for (int i = 0; i <= cant; ++i)
		{
			bonifi.push_back(new Bonificacion(w, h));
		}
	}
	void addVirusVertical(int w, int h, Graphics^ gra, int cant)
	{
		for (int i = 0; i <= cant; ++i)
		{
			virusv.push_back(new VirusVertical(w, h, gra));
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	void drawVirus(Graphics^ g, Bitmap^ bmp)
	{
		for each (Virus * v in virus)
		{

			v->draw(g, bmp);
		}
	}
	void drawnVacunas(Graphics^ g, Bitmap^ bmpv)
	{
		for (int i = 0; i < vacunas.size(); i++)
		{
			vacunas[i]->draw(g, bmpv);
		}
	}
	void drawBonificacion(Graphics^ g, Bitmap^ bmpb,int cont)
	{
		for each (Bonificacion * V in bonifi)
		{
			V->draw(g, bmpb, cont);
		}
	}
	void drawEstadisticas(Graphics^ g)
	{
		g->DrawString("Vidas: " + jugador->GetVidas(), gcnew Font("Arial", 24), Brushes::Red, 180, 0);
		g->DrawString("Puntos: " + jugador->GetPuntos(), gcnew Font("Arial", 24), Brushes::Red, 360, 0);
		g->DrawString("Nivel: " + nivel, gcnew Font("Arial", 24), Brushes::Red, 0, 0);
	}
	void drawVirusVertical(Graphics^ g, Bitmap^ bmp)
	{
		for each (VirusVertical * v in virusv)
		{

			v->draw(g, bmp);
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	void drawEverything(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpj, Bitmap^ bmpv, Bitmap^ bmpb, int cont)
	{
		drawEstadisticas(g);
		jugador->draw(g, bmpj);
		if (nivel == 1 || nivel == 3)
		{
			drawVirus(g, bmp);
		}
		drawnVacunas(g, bmpv);
		drawBonificacion(g, bmpb, cont);	
		if (nivel == 2)
		{
			drawVirusVertical(g, bmp);
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	void moveVirus(Graphics^ g)
	{
		for (int i = 0; i < virus.size(); ++i)
		{
			virus[i]->move(g);
		}
	}
	void moveVacunas(Graphics^ g)
	{
		for (int i = 0; i < vacunas.size(); i++)
		{
			vacunas[i]->move(g);
		}
	}
	void moveVirusVertical(Graphics^ g)
	{
		for (int i = 0; i < virusv.size(); ++i)
		{
			virusv[i]->move(g);
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	void moveEverything(Graphics^ g)
	{
		if (nivel == 1 || nivel == 3)
		{
			moveVirus(g);
		}
		moveVacunas(g);	
		if (nivel == 2)
		{
			moveVirusVertical(g);
		}
	}
	bool colisionR(Rectangle o1, Rectangle o2) {
		return o1.IntersectsWith(o2);
	}
	void colisionVirusJugador()
	{
		if (virus.size() > 1) {
			for (size_t i = 0; i < virus.size() - 1; ++i) {
				for (size_t j = i + 1; j < virus.size(); ++j) {
					if (colisionR(virus[i]->getRectangle(), jugador->getRectangle()))
					{
						jugador->SetVidas(-1);
						virus.erase(virus.begin() + i);
						virus.erase(virus.begin() + j - 1);
					}

				}
			}
		}
	}
	void colisionVirusvJugador()
	{
		if (virusv.size() > 1) {
			for (size_t i = 0; i < virusv.size() - 1; ++i) {
				for (size_t j = i + 1; j < virusv.size(); ++j) {
					if (colisionR(virusv[i]->getRectangle(), jugador->getRectangle()))
					{
						jugador->SetVidas(-1);
						virusv.erase(virusv.begin() + i);
						virusv.erase(virusv.begin() + j - 1);
					}
				}
			}
		}
	}
	void colisionCovidVacuna()
	{
		for (int i = 0; i < vacunas.size(); i++)
		{
			if (vacunas[i]->getRectangle().IntersectsWith(covid->getRectangle()))
			{
				vacunas[i]->setVisible(false);
				covid->setVidas(-1);
			}
		}
	}
	void colisionCovidJugador()
	{
		if (jugador->getRectangle().IntersectsWith(covid->getRectangle()))
		{
			jugador->SetVidas(-jugador->GetVidas());
		}
	}
	void colisionVirusVacuna()
	{
		for (int i = 0; i < virus.size(); i++)
		{
			for (int j = 0; j < vacunas.size(); j++)
			{
				if (virus[i]->getRectangle().IntersectsWith(vacunas[j]->getRectangle()))
				{
					virus[i]->setVisible(false);
					vacunas[j]->setVisible(false);
					jugador->SetPuntos(1);
				}
			}
		}
		for (int i = 0; i < virus.size(); i++)
		{
			if (!virus[i]->getVisible())
			{
				virus.erase(virus.begin() + i);
			}
		}
		for (int i = 0; i < vacunas.size(); i++)
		{
			if (!vacunas[i]->getVisible())
			{
				vacunas.erase(vacunas.begin() + i);
			}
		}			
	}
	void colisionVirusvVacuna()
	{
		for (int i = 0; i < virusv.size(); i++)
		{
			for (int j = 0; j < vacunas.size(); j++)
			{
				if (virusv[i]->getRectangle().IntersectsWith(vacunas[j]->getRectangle()))
				{
					virusv[i]->setVisible(false);
					vacunas[j]->setVisible(false);
					jugador->SetPuntos(1);
				}
			}
		}
		for (int i = 0; i < virusv.size(); i++)
		{
			if (!virusv[i]->getVisible())
			{
				virusv.erase(virusv.begin() + i);
			}
		}
		for (int i = 0; i < vacunas.size(); i++)
		{
			if (!vacunas[i]->getVisible())
			{
				vacunas.erase(vacunas.begin() + i);
			}
		}
	}
	
	void collision(Graphics^ g)
	{
		for (int j = 0; j < vacunas.size(); j++)
		{
			if (vacunas[j]->getXWidth() >= g->VisibleClipBounds.Width || vacunas[j]->getX()<= 0 || vacunas[j]->getY() <= 0 || vacunas[j]->getYHeigth() >=g->VisibleClipBounds.Height)
			{
				vacunas[j]->setVisible(false);
			}
		}
		for (int i = 0; i < virus.size(); i++)
		{
			if (virus[i]->getX() <= 0 || virus[i]->getY() <= 0 || virus[i]->getYHeight() >= g->VisibleClipBounds.Height)
			{
				virus[i]->setVisible(false);
			}
		}
		for (int i = 0; i < virusv.size(); i++)
		{
			if (virusv[i]->getYHeight() >= g->VisibleClipBounds.Height)
			{
				virusv[i]->setVisible(false);
			}
		}
		for (int i = 0; i < bonifi.size(); i++)
		{
			if (jugador->getRectangle().IntersectsWith(bonifi[i]->getRectangle()))
			{
				if (bonifi[i]->getIDy() == 1)
				{
					jugador->SetVidas(1);
				}
				else if (bonifi[i]->getIDy() == 0)
				{
					jugador->setDX(5);
					jugador->setDY(5);
				}
				bonifi[i]->setVisible(false);
			}
		}
		for (int i = 0; i < bonifi.size(); i++)
		{
			if (!bonifi[i]->getVisible())
			{
				bonifi.erase(bonifi.begin() + i);
			}
		}
		colisionVirusvJugador();
		if (nivel == 3)
		{
			colisionCovidVacuna();
		}
		colisionVirusJugador();
		colisionVirusVacuna();
		colisionVirusvVacuna();
		colisionCovidJugador();
		
	}
	void pasanivel() {
		for (int i = 0; i < virus.size(); i++)
			delete virus.at(i);
	}
	Jugador* getJugador() { return jugador; }
	Covid* getCovid() { return covid; }
	int GetNivel()
	{
		return nivel;
	}
	void SetNivel(int value)
	{
		nivel = value;
	}
	void moveCovid(Graphics^ g) {
		covid->move(g);
	}
	void drawCovid(Graphics^ g, Bitmap^ bmpc) {
		covid->draw(g, bmpc);
	}
};
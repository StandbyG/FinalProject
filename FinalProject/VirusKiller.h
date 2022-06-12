#pragma once
#include "Virus.h"
#include"Controller.h"
#include"Jugador.h"
namespace FinalProject {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	/// <summary>
	/// Summary for VirusKiller
	/// </summary>
	public ref class VirusKiller : public System::Windows::Forms::Form
	{
	private:
		Controller* juego;
		Bitmap^ bmpVirus;
		Bitmap^ mapa1;
		Bitmap^ mapa2;
		Bitmap^ mapa3;
		Bitmap^ bmpboni;
		Bitmap^ bmpdoctor;
		Bitmap^ bmpvacuna;
		Bitmap^ bmpCovid;
		Bitmap^ gameOver;
		Bitmap^ winner;
		Graphics^ g;
		BufferedGraphicsContext^ space;
		BufferedGraphics^ buffer;
		SoundPlayer^ music;
		int accountant;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::Timer^ timer1;
	public:
		VirusKiller(void)
		{
			InitializeComponent();
			g = panel1->CreateGraphics();
			space = BufferedGraphicsManager::Current;
			buffer = space->Allocate(g, panel1->ClientRectangle);
			bmpVirus = gcnew Bitmap("virus.png");
			bmpboni = gcnew Bitmap("monedas.png");
			bmpdoctor = gcnew Bitmap("doctor2.png");
			mapa1 = gcnew Bitmap("nivel1.png");
			mapa2 = gcnew Bitmap("nivel2.png");
			mapa3 = gcnew Bitmap("nivel3.png");
			bmpvacuna = gcnew Bitmap("vacunas2.png");
			bmpCovid = gcnew Bitmap("covid.gif");
			gameOver = gcnew Bitmap("gameover.jpg");
			winner = gcnew Bitmap("winner.png");
			music = gcnew SoundPlayer("Conan.wav");
			juego = new Controller(bmpdoctor, 4, bmpCovid->Width / 3, bmpCovid->Height / 1, buffer->Graphics);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~VirusKiller()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(2, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1586, 632);
			this->panel1->TabIndex = 0;
			this->panel1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &VirusKiller::panel1_MouseClick);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 33;
			this->timer1->Tick += gcnew System::EventHandler(this, &VirusKiller::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &VirusKiller::timer2_Tick);
			// 
			// VirusKiller
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1591, 636);
			this->Controls->Add(this->panel1);
			this->Name = L"VirusKiller";
			this->Text = L"VirusKiller";
			this->Load += gcnew System::EventHandler(this, &VirusKiller::VirusKiller_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &VirusKiller::VirusKiller_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
		void Nivel1()
		{
			buffer->Graphics->Clear(Color::White);
			buffer->Graphics->DrawImage(mapa1, 0, 0, panel1->Width, panel1->Height);
			juego->Coli(buffer->Graphics);
			juego->Draw(buffer->Graphics, bmpVirus, bmpdoctor, bmpvacuna, bmpboni, accountant);
			juego->Move(buffer->Graphics);

			if (juego->getColec()->getJugador()->GetPuntos() >= 5)
			{
				accountant = 0;
				juego->getColec()->SetNivel(2);
				juego->getColec()->pasanivel();
				juego->getColec()->getJugador()->SetPunto0();
			}
		}
		void Nivel2()
		{
			buffer->Graphics->Clear(Color::White);
			buffer->Graphics->DrawImage(mapa2, 0, 0, panel1->Width, panel1->Height);
			juego->Coli(buffer->Graphics);
			juego->Draw(buffer->Graphics, bmpVirus, bmpdoctor, bmpvacuna, bmpboni, accountant);
			juego->Move(buffer->Graphics);
			if (juego->getColec()->getJugador()->GetPuntos() >= 5)
			{
				accountant = 0;
				juego->getColec()->SetNivel(3);
				juego->getColec()->pasanivel();
				juego->getColec()->getJugador()->SetPunto0();
			}
		} 
		void Nivel3()
		{
			buffer->Graphics->Clear(Color::White);
			buffer->Graphics->DrawImage(mapa3, 0, 0, panel1->Width, panel1->Height);
			juego->Coli(buffer->Graphics);
			juego->Draw(buffer->Graphics, bmpVirus, bmpdoctor, bmpvacuna, bmpboni, accountant);
			juego->getColec()->drawCovid(buffer->Graphics, bmpCovid);
			juego->Move(buffer->Graphics);
			juego->getColec()->moveCovid(buffer->Graphics);
			if (juego->getColec()->getCovid()->getVidas() == 0)
			{
				timer1->Enabled = false;
				timer2->Enabled = false;
				buffer->Graphics->DrawImage(winner, 0, 0, panel1->Width, panel1->Height);
			}
		}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		if (juego->getColec()->GetNivel() == 1)
		{
			Nivel1();
		}
		else if (juego->getColec()->GetNivel() == 2)
		{
			Nivel2();
		}
		else if (juego->getColec()->GetNivel() == 3)
		{
			Nivel3();
		}
		if (juego->getColec()->getJugador()->GetVidas() == 0)
		{
			timer1->Enabled = false;
			timer2->Enabled = false;
			buffer->Graphics->DrawImage(gameOver, 0, 0, panel1->Width, panel1->Height);
		}
		buffer->Render(g);
	}
	private: System::Void VirusKiller_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{

		case Keys::A: case Keys::Left:
			juego->getColec()->getJugador()->Move(buffer->Graphics, 'A'); break;
		case Keys::D: case Keys::Right:
			juego->getColec()->getJugador()->Move(buffer->Graphics, 'D'); break;
		case Keys::W: case Keys::Up:
			juego->getColec()->getJugador()->Move(buffer->Graphics, 'W'); break;
		case Keys::S: case Keys::Down:
			juego->getColec()->getJugador()->Move(buffer->Graphics, 'S'); break;
		case Keys::Space: if (juego->getColec()->getJugador()->GetVidas() == 0 || juego->getColec()->getCovid()->getVidas() == 0)this->Close(); break;
		}

	}
	private: System::Void panel1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Vacuna v = Vacuna(juego->getColec()->getJugador()->getX() + juego->getColec()->getJugador()->getAncho() / 2-20, juego->getColec()->getJugador()->getY() + juego->getColec()->getJugador()->getAlto() / 2 - 50, bmpvacuna->Width / 2, bmpvacuna->Height / 2,juego->getColec()->getJugador()->getIDy());
		juego->getColec()->addVacunas(v);
	}

	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		if (juego->getColec()->GetNivel() == 2 || juego->getColec()->GetNivel() == 3  )
		{
			if (accountant == 10)
			{
				juego->getColec()->addBonificacion(bmpboni->Width / 8, bmpboni->Height / 2, g, 1);
			}
		}
		if (accountant % 5 == 0)
		{
			juego->getColec()->addVirus(bmpVirus->Width / 3, bmpVirus->Height / 3, g, 10);
		}
		if (juego->getColec()->GetNivel() == 2)
		{
			if (accountant % 7 == 0)
			{
				juego->getColec()->addVirusVertical(bmpVirus->Width / 3, bmpVirus->Height / 3, g, 10);
			}
		}
		accountant++;
	}
	private: System::Void VirusKiller_Load(System::Object^ sender, System::EventArgs^ e) {
		music->PlayLooping();
	}
	};
}
#pragma once
#include "Plansza.h"
#include "Gracz.h"

class Gra
{
public:
	Gra();
	~Gra();
	void drukuj();
	void play();
	void player1notify();
	void player2notify();
	void updatePlansza(int planszaCopy[8][8]);
private:
	//typedef std::unique_ptr<Gracz> pPlayer;
	Plansza plansza;
	Gracz* player1;
	Gracz* player2;
	const int kolumny = 8;
};


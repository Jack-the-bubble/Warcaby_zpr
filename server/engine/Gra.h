#pragma once
#include "Plansza.h"
#include "Gracz.h"
#include "Klient.h"
#include "Komputer.h"
#include "Move.h"
#include <iostream>

class Gra
{
public:
	Gra();
	~Gra();
	void drukuj();
	void play();
	void player1notify();
	void player2notify();

private:
	Plansza plansza;
	Gracz* player1;
	Gracz* player2;
	const int kolumny = 8;
};


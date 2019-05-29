#pragma once
#include "Move.h"
class Plansza
{
public:
	Plansza();
	~Plansza();
	const int getPlansza(int, int);
	void makeMove(int, int, int, int, int);
	void makeMove(Move);
	int bicie(int, int,int,int,int); //usuwa zbity pionek
	bool isWin();

	bool damka(int, int, int);
public:
	int plansza[8][8];
private:

	
	int pionkiBiale;   //pionki gracza o ID = 1 
	int pionkiCzarne;  //pionki gracza o ID = -1
	const int kolumny = 8;
	bool damkaDone = false;
};


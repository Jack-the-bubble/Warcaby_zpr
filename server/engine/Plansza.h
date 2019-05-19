#pragma once
class Plansza
{
public:
	Plansza();
	~Plansza();
	const int getPlansza(int, int);
	void makeMove(int, int, int, int, int);
	int bicie(int, int,int,int,int); //usuwa zbity pionek
	int getPionkiCzarne();
	int getPionkiBiale();
	bool damka(int, int, int);
public:
	int plansza[8][8];
private:

	int pionkiBiale;   //pionki gracza o ID = 1
	int pionkiCzarne;  //pionki gracza o ID = -1
	const int kolumny = 8;
	bool damkaDone = false;
};


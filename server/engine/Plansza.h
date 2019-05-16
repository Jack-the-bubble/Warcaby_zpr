#pragma once
class Plansza
{
public:
	Plansza();
	~Plansza();
	const int getPlansza(int, int);
	void makeMove(int, int, int, int, int);
	void bicie(int, int); //usuwa zbity pionek

public:
	int plansza[8][8];
private:

	int pionkiBiale;
	int pionkiCzarne;
	const int kolumny = 8;
};


#include "Plansza.h"
#include <iostream>
using namespace std;

Plansza::Plansza()
{
	int i, j;
	for (i = 0; i < KOLUMNY; ++i)
	{
		for (j = 0; j < KOLUMNY; ++j)
		{
			plansza[i][j] = 0;
		}
	}
	for (i = 0; i < 3; ++i)  //poczatkowe ustawienie pionkow
	{
		if (i % 2 == 1) plansza[i][1] = plansza[i][3] = plansza[i][5] = plansza[i][7] = 1;
		if (i % 2 == 0) plansza[i][0] = plansza[i][2] = plansza[i][4] = plansza[i][6] = 1;
	}
	for (i = 5; i < KOLUMNY; ++i)  //poczatkowe ustawienie pionkow
	{
		if (i % 2 == 1) plansza[i][1] = plansza[i][3] = plansza[i][5] = plansza[i][7] = -1;
		if (i % 2 == 0) plansza[i][0] = plansza[i][2] = plansza[i][4] = plansza[i][6] = -1;
	}

}



Plansza::~Plansza()
{
}


const int Plansza::getPlansza(int i, int j)
{
	return this->plansza[i][j];
}


/**

	@return czy stan planszy koncowy
*/


bool Plansza::isWin()
{
	int i, j, cnt1 = 0, cnt2 = 0;
	for (i = 0; i < KOLUMNY; ++i)
	{
		for (j = 0; j < KOLUMNY; ++j)
		{
			if(plansza[i][j] == 1 || plansza[i][j] == 2) ++cnt1;
			else if (plansza[i][j] == -1 || plansza[i][j] == -2) ++cnt2;
		}
	}
	return ((cnt1 == 0) || (cnt2 == 0));
}

/**
	Funkcja wykonuje na planszy ruch.

	@param move ruch do wykonania
*/
void Plansza::makeMove(Move move)
{

	plansza[move.from[0]][move.from[1]] = 0;
	plansza[move.to[0]][move.to[1]] = move.ID;

	vector<int>::iterator it;
	vector<int>::iterator it2;
	for (it = move.capturedRow.begin(), it2 = move.capturedCol.begin(); it != move.capturedRow.end(); it++, it2++)
	{
		plansza[*it][*it2] = 0;  
	}
}
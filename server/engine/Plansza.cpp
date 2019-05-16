#include "Plansza.h"



Plansza::Plansza()
{ 
	int i,j;
	for (i = 0; i < kolumny; ++i)
	{
		for (j = 0; j < kolumny; ++j)
		{
			plansza[i][j] = 0;
		}
	}
	for (i = 0; i < kolumny; ++i)  //poczatkowe ustawienie pionkow
	{
		plansza[0][i] = plansza[1][i] = 1;
		plansza[6][i] = plansza[7][i] = -1;
	}
	pionkiBiale = pionkiCzarne = 16;
}



Plansza::~Plansza()
{
}


const int Plansza::getPlansza(int i, int j)
{
	return this->plansza[i][j];
}

void Plansza::makeMove(int graczID, int w_prev, int k_prev, int w_next, int k_next)
{
	this->plansza[w_prev][k_prev] = 0;
	this->plansza[w_next][k_next] = graczID;
	if (graczID * (w_next - w_prev) == 1) return;

}

void Plansza::bicie(int zbity_w, int zbita_k)
{
	int ID = plansza[zbity_w][zbita_k];
	plansza[zbity_w][zbita_k] = 0;
	if (ID == 1) pionkiBiale--;
	if (ID == -1) pionkiCzarne--;
}

/*void Plansza wykonajBicie()
{

}*/

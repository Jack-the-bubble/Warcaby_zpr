#include "Plansza.h"
#include <iostream>
using namespace std;

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
	for (i = 0; i < 3; ++i)  //poczatkowe ustawienie pionkow
	{
		if (i % 2 == 1) plansza[i][1] = plansza[i][3] = plansza[i][5] = plansza[i][7] = 1;
		if (i % 2 == 0) plansza[i][0] = plansza[i][2] = plansza[i][4] = plansza[i][6] = 1;
	}
	for (i = 5; i < kolumny; ++i)  //poczatkowe ustawienie pionkow
	{
		if (i % 2 == 1) plansza[i][1] = plansza[i][3] = plansza[i][5] = plansza[i][7] = -1;
		if (i % 2 == 0) plansza[i][0] = plansza[i][2] = plansza[i][4] = plansza[i][6] = -1;
	}
	pionkiBia쿮 = pionkiCzarne = 12;
}



Plansza::~Plansza()
{
}


const int Plansza::getPlansza(int i, int j)
{
	return this->plansza[i][j];
}

bool Plansza::damka(int graczID, int w, int k)
{
	if ((graczID == 1 && w == kolumny-1) || (graczID == -1 && w == 0))
	{
		plansza[w][k] = graczID * 2;
		std::cout << "damka" << std::endl;
		return true;
	}
	return false;
}

void Plansza::makeMove(int graczID, int w_prev, int k_prev, int w_next, int k_next)
{
	if(plansza[w_prev][k_prev] == graczID) bicie(graczID, w_prev, k_prev, w_next, k_next);   //gdy nie damka
	this->plansza[w_prev][k_prev] = 0;
	this->plansza[w_next][k_next] = graczID;
	damkaDone = false;
	return;

}

int Plansza::bicie(int graczID, int w_prev, int k_prev, int w_next, int k_next)
{
	if (!damkaDone) damkaDone = damka(graczID, w_next, k_next);
	if ((w_prev == w_next) && (k_next == k_prev)) return 0;
	if (graczID * (w_next - w_prev) == 1) return 1;  //tu nic nie zbija
	if (graczID * (w_next - w_prev) == 2)  //tu zbija przy pojedynczym biciu do przodu
	{
		if (k_next > k_prev)
		{
			if (plansza[w_prev + graczID * 1][k_prev + 1] == -graczID)
			{
				plansza[w_prev + graczID * 1][k_prev + 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				return 1;
			}
		}
		else
		{
			if (plansza[w_prev + graczID * 1][k_prev - 1] == -graczID)
			{
				plansza[w_prev + graczID * 1][k_prev - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				return 1;
			}
				
		}

	}
	if (graczID * (w_prev - w_next) == 2)  //tu zbija przy pojedynczym biciu do ty퀅
	{
		if (k_next > k_prev)
		{
			if (plansza[w_prev - graczID * 1][k_prev + 1] == -graczID)
			{
				plansza[w_prev - graczID * 1][k_prev + 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				return 1;
			}
		}
		else
		{
			if (plansza[w_prev - graczID * 1][k_prev - 1] == -graczID)
			{
				plansza[w_prev - graczID * 1][k_prev - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				return 1;
			}
		}
	}
	int pom = 0; 

		if (w_next - graczID * 2 >= 0)
		{
			if (k_next + 2 < kolumny && plansza[w_next - graczID * 1][k_next + 1] == -graczID)
			{
				plansza[w_next - graczID * 1][k_next + 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				if( bicie(graczID, w_prev, k_prev, w_next - graczID * 2, k_next + 2) == 2) plansza[w_next - graczID * 1][k_next + 1] = -graczID ;
				pom++;
			}

			if (k_next - 2 >= 0 && plansza[w_next - graczID * 1][k_next - 1] == -graczID)
			{
				plansza[w_next - graczID * 1][k_next - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				if(bicie(graczID, w_prev, k_prev, w_next - graczID * 2, k_next - 2) == 2) plansza[w_next - graczID * 1][k_next - 1] = -graczID;
				pom++;
			}

		}
		if (w_next + graczID * 2 < kolumny)
		{
			if (k_next + 2 < kolumny && plansza[w_next + graczID * 1][k_next + 1] == -graczID)
			{
				plansza[w_next + graczID * 1][k_next + 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				if(bicie(graczID, w_prev, k_prev, w_next + graczID * 2, k_next + 2) == 2) plansza[w_next + graczID * 1][k_next + 1] = -graczID;
				pom++;
			}
			if (k_next - 2 >= 0 && plansza[w_next + graczID * 1][k_next - 1] == -graczID)
			{
				plansza[w_next + graczID * 1][k_next - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBia쿮--;
				if( bicie(graczID, w_prev, k_prev, w_next + graczID * 2, k_next - 2) == 2) plansza[w_next + graczID * 1][k_next - 1] = -graczID;
				pom++;
			}

		}
		if (pom == 0) return 2;

	return 1;
}



int Plansza::getPionkiBiale()
{
	return this->pionkiBia쿮;
}
int Plansza::getPionkiCzarne()
{
	return this->pionkiCzarne;
}
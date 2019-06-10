#include "Plansza.h"
#include <iostream>
using namespace std;

Plansza::Plansza()
{
	int i,j;
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
	pionkiBiale = pionkiCzarne = 12;
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
 * funkcja sprawdza czy dany pion jest damka
 * @param graczID - identyfikator gracza, ktorego pion chcemy zidentyfikowac
 * @param w - wiersz piona
 * @param k - kolumna piona
 * */
bool Plansza::damka(int graczID, int w, int k)
{
	if ((graczID == 1 && w == KOLUMNY-1) || (graczID == -1 && w == 0))
	{
		plansza[w][k] = graczID * 2;
		std::cout << "damka" << std::endl;
		return true;
	}
	return false;
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
				else if (graczID == -1) pionkiBiale--;
				return 1;
			}
		}
		else
		{
			if (plansza[w_prev + graczID * 1][k_prev - 1] == -graczID)
			{
				plansza[w_prev + graczID * 1][k_prev - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBiale--;
				return 1;
			}

		}

	}
	if (graczID * (w_prev - w_next) == 2)  //tu zbija przy pojedynczym biciu do tylu
	{
		if (k_next > k_prev)
		{
			if (plansza[w_prev - graczID * 1][k_prev + 1] == -graczID)
			{
				plansza[w_prev - graczID * 1][k_prev + 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBiale--;
				return 1;
			}
		}
		else
		{
			if (plansza[w_prev - graczID * 1][k_prev - 1] == -graczID)
			{
				plansza[w_prev - graczID * 1][k_prev - 1] = 0;
				if (graczID == 1) pionkiCzarne--;
				else if (graczID == -1) pionkiBiale--;
				return 1;
			}
		}
	}
	int pom = 0;

	if (w_next - graczID * 2 >= 0)
	{
		if (k_next + 2 < KOLUMNY && plansza[w_next - graczID * 1][k_next + 1] == -graczID)
		{
			plansza[w_next - graczID * 1][k_next + 1] = 0;
			if (graczID == 1) pionkiCzarne--;
			else if (graczID == -1) pionkiBiale--;
			if( bicie(graczID, w_prev, k_prev, w_next - graczID * 2, k_next + 2) == 2) plansza[w_next - graczID * 1][k_next + 1] = -graczID ;
			pom++;
		}

		if (k_next - 2 >= 0 && plansza[w_next - graczID * 1][k_next - 1] == -graczID)
		{
			plansza[w_next - graczID * 1][k_next - 1] = 0;
			if (graczID == 1) pionkiCzarne--;
			else if (graczID == -1) pionkiBiale--;
			if(bicie(graczID, w_prev, k_prev, w_next - graczID * 2, k_next - 2) == 2) plansza[w_next - graczID * 1][k_next - 1] = -graczID;
			pom++;
		}

	}
	if (w_next + graczID * 2 < KOLUMNY)
	{
		if (k_next + 2 < KOLUMNY && plansza[w_next + graczID * 1][k_next + 1] == -graczID)
		{
			plansza[w_next + graczID * 1][k_next + 1] = 0;
			if (graczID == 1) pionkiCzarne--;
			else if (graczID == -1) pionkiBiale--;
			if(bicie(graczID, w_prev, k_prev, w_next + graczID * 2, k_next + 2) == 2) plansza[w_next + graczID * 1][k_next + 1] = -graczID;
			pom++;
		}
		if (k_next - 2 >= 0 && plansza[w_next + graczID * 1][k_next - 1] == -graczID)
		{
			plansza[w_next + graczID * 1][k_next - 1] = 0;
			if (graczID == 1) pionkiCzarne--;
			else if (graczID == -1) pionkiBiale--;
			if( bicie(graczID, w_prev, k_prev, w_next + graczID * 2, k_next - 2) == 2) plansza[w_next + graczID * 1][k_next - 1] = -graczID;
			pom++;
		}

	}
	if (pom == 0) return 2;

	return 1;
}

int Plansza::getPionkiBiale()
{
	return this->pionkiBiale;
}
int Plansza::getPionkiCzarne()
{
	return this->pionkiCzarne;
}
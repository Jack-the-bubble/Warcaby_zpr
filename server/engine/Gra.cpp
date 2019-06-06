#include "Gra.h"

using namespace std;

/**
	Konstruktor klasy Gra. Tworzy graczy z odpowiednimi identyfikatorami

	@param i identyfikator klienta aplikacji frontendowej
*/

Gra::Gra(int i)
{
	Komputer pl1(1);
	player1 = &pl1;

	Komputer pl2(-1);
	player2 = &pl2;
}


Gra::~Gra()
{
}

/**
	Funkcja pomagajaca w testowaniu aplikacji. Wypisuje aktualna plansze na konsole
*/

void Gra::drukuj()
{
	std:cout << "W|";
	for (int j = 0; j < KOLUMNY; ++j) std::cout << j << "|";
	std::cout << std::endl;
	for (int i = KOLUMNY - 1; i >= 0; --i)
	{
	
		std::cout <<i<< "|";
		for (int j = 0; j < KOLUMNY; ++j)
		{
			if (plansza.getPlansza(i, j) == 1)
				std::cout << "O|";
			else if (plansza.getPlansza(i, j) == -1)
				std::cout << "X|";
			else if (plansza.getPlansza(i, j) == 2)
				cout << "Q|";
			else if (plansza.getPlansza(i, j) == -2)
				cout << "W|";
			else std::cout << " |";
		}
		std::cout << std::endl;
	}
}

/**
	Glowna petla gry. Kontroluje przeplyw ruchow miedzy graczami, stan planszy i decyduje o koncu gry.
*/
void Gra::play()
{
	this->drukuj();

	while (!(plansza.isWin())) 
	{
 		this->player1notify();
		plansza.makeMove(player1->getBestMove());
		this->drukuj();
		this->player2notify();
		//player1->oponentMove(player2->getBestMove()); 
		plansza.makeMove(player2->getBestMove());
		this->drukuj();
	}

	return;
}

/**
	Funkcja wywolywana gdy gracz 1 ma wykonac ruch
*/
void Gra::player1notify()
{

	player1->update(plansza.plansza);

}

/**
	Funkcja wywolywana gdy gracz 1 ma wykonac ruch
*/
void Gra::player2notify()
{
	player2->update(plansza.plansza);

}

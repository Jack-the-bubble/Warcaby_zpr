#include "Gra.h"
#include "Uzytkownik.h"
#include <iostream>
using namespace std;



Gra::Gra()
{
}


Gra::~Gra()
{
	delete player1, player2;
}

void Gra::drukuj()
{
	std:cout << "W|";
	for (int j = 0; j < kolumny; ++j) std::cout << j << "|";
	std::cout << std::endl;
	for (int i = kolumny - 1; i >= 0; --i)
	{
	
		std::cout <<i<< "|";
		for (int j = 0; j < kolumny; ++j)
		{
			if (plansza.getPlansza(i,j) == 1)
				std::cout << "O|";
			else if (plansza.getPlansza(i,j) == -1)
				std::cout << "X|";
			else std::cout << " |";
		}
		std::cout << std::endl;
	}
}

void Gra::play()
{
	this->drukuj();

	player1 = new Uzytkownik(1);
	player2 = new Uzytkownik(-1);


	while (true) 
	{
		this->player1notify();

		// makeMove(int graczID, int w_prev, int k_prev, int w_next, int k_next)

		plansza.makeMove(player1->getID(), player1->getPrevW(), player1->getPrevK(), player1->getW(), player1->getK());

		this->drukuj();

		this->player2notify();
		plansza.makeMove(player2->getID(), player2->getPrevW(), player2->getPrevK(), player2->getW(), player2->getK());

		this->drukuj();
	}

	return;
}

void Gra::player1notify()
{
	player1->update(plansza.plansza);

}

void Gra::player2notify()
{
	player2->update(plansza.plansza);

}
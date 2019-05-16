#include "Gra.h"
#include "Uzytkownik.h"
#include "Klient.h"
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

	Uzytkownik pl1(1);
	player1 = &pl1;

	Uzytkownik pl2(-1);
	player2 = &pl2;


	while (plansza.getPionkiBiale() != 0 && plansza.getPionkiCzarne() != 0) 
	{
		this->player1notify();

		 //makeMove(int graczID, int w_prev, int k_prev, int w_next, int k_next)

		plansza.makeMove(player1->getID(), player1->getPrevW(), player1->getPrevK(), player1->getW(), player1->getK());  //to usuniemy jak bedzie komputer


		//TODO
		//updatePlansza(player1->boardCopy); // przekazanie zaktualizowanej planszy


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

void Gra::updatePlansza(int planszaCopy[8][8])
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; i < 8; ++j)
		{
			plansza.plansza[i][j] = planszaCopy[i][j];
		}
	}
}
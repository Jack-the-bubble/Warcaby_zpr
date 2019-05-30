#include "Gra.h"

using namespace std;



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

void Gra::play()
{
	this->drukuj();

	//Uzytkownik pl1(1);
//	Komputer pl1(1);
//	player1 = &pl1;
//
//	Komputer pl2(-1);
//	player2 = &pl2;


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

void Gra::player1notify()
{

	player1->update(plansza.plansza);

}

void Gra::player2notify()
{
	player2->update(plansza.plansza);

}

int main(){
	return 0;
}

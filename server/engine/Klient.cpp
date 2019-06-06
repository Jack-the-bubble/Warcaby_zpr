#include "Klient.h"
#include <iostream>



Klient::Klient(int graczID_)
{
	graczID = graczID_;
}


Klient::~Klient()
{
}

/**
	Funkcja w ktorej gracz ma wskazac swoj ruch, po wyjsciu z niej w skladowej bestMove ma znalezc sie wskazany ruch

	@param plansza[8][8] aktualny stan glownej planszy gry
*/
void Klient::update(const int plansza[8][8])
{
	//TODO
	std::cout<<"hey"<<std::endl;
	//Przeslanie aktualnej planszy do klienta
	//przeslanie gotowej planszy przez klienta
}

int Klient::getID()
{
	return graczID;
}

void Klient::convert_and_update(boost::python::list board){
	int C_board[8][8];
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			C_board[i][j]=extract<int>(board[i*8+j]);
		}
	}
	Klient::update(C_board);
}

/**
	Funkcja uzyskujaca ostatni ruch oponenta

	@param oponentMove poprzedni ruch przeciwnika
*/
void Klient::oponentMove(Move oponentMove)
{
	//co chcesz
}

Move Klient::getBestMove()
{
	//wyslanie wykonanego ruchu do klasy Gra
	Move any;
	return any;
}

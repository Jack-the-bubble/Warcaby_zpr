#include "Gracz.h"



Gracz::Gracz()
{
}


Gracz::~Gracz()
{
}

/**
 * wypisz lokalna kopie planszy uzytkownika
 * @param board - plansza do wydrukowania o rozmiarach 8x8
 * */
void Gracz::drukuj(const int board[8][8]) {
	for(int i = KOLUMNY - 1; i >= 0; i--) {
		for (int j = 0; j < KOLUMNY; ++j) {
			std::cout<<"| " << board[i][j]<<" |";

		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}
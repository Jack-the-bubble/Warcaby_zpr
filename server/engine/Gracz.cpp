#include "Gracz.h"



Gracz::Gracz()
{
}


Gracz::~Gracz()
{
}

void Gracz::drukuj(const int board[8][8]) {
	for(int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; ++j) {
			std::cout<<"| " << board[i][j]<<" |";

		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}
#include "Klient.h"
#include <iostream>



Klient::Klient()
{
	graczID = 1;
	latestMove = Move();
}


Klient::~Klient()
{
}

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

void Klient::oponentMove(Move oponentMove)
{
	//co chcesz
}

void Klient::moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap) {
	std::cout<<"creating move "<<std::endl;
	Move move= Move(begMov_y, begMov_x, destMov_y, destMov_x, 1, boost::python::extract<int>(cap[0]), boost::python::extract<int>(cap[1]));
	for (int i = 0; i < boost::python::len(cap)-2; i+=2) {
		move.addCaptured(boost::python::extract<int>(cap[i+2]), boost::python::extract<int>(cap[i+3]));
	}
	Klient::latestMove = move;//Move(begMov[0], begMov[1], destMov[0], destMov[1], 1, rowC, colC);
}

Move Klient::getBestMove()
{
	return latestMove;
}

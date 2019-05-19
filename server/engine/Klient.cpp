#include "Klient.h"
#include <iostream>



Klient::Klient(int graczID_)
{
	graczID = graczID_;
}


Klient::~Klient()
{
}

void Klient::update(/*const int plansza[8][8]*/)
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
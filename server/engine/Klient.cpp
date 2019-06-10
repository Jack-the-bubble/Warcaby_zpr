#include "Klient.h"
#include <iostream>



Klient::Klient()
{
	graczID = 1;
	bestMove = Move();
//	latestMove = Move();
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

}

int Klient::getID()
{
	return graczID;

}

/**
 * funkcja uaktualnia pole bestMove po ruchu klienta
 * - wspolrzedne podane sa w notacji, ktorej uzywa logika komputera
 * @param begMov_x - wspolrzedna x poczatkowej pozycji pionka ktory nalezy ruszyc
 * @param begMov_y - wspolrzedna y poczatkowej pozycji pionka ktory nalezy ruszyc
 * @param destMov_x - wspolrzedna x koncowej pozycji pionka ktory nalezy ruszyc
 * @param destMov_y - wspolrzedne y koncowej pozycji pionka ktory nalezy ruszyc
 * @param cap - lista pionkow przeciwnika do usuniecia
 * */
void Klient::moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap) {
//	std::cout<<"creating move, captured: "<<boost::python::extract<int>(cap[0])<<" "<< boost::python::extract<int>(cap[1])<<std::endl;
	Move move= Move(begMov_y, begMov_x, destMov_y, destMov_x, 1, boost::python::extract<int>(cap[0]), boost::python::extract<int>(cap[1]));
//	std::cout<<"translated move from client: "<<std::endl;
//	move.printMove();
	for (int i = 0; i < boost::python::len(cap)-2; i+=2) {
		move.addCaptured(boost::python::extract<int>(cap[i+2]), boost::python::extract<int>(cap[i+3]));
	}
	bestMove = move;
}

/**
 * @return ruch zapisany w bestMove
 * */
Move Klient::getBestMove()
{
	return bestMove;
}

/**
 * funkcja ustawia wartosc test
 * */
void Klient::set(int i){
	test = i;
}

/**
 * funkcja wypisuje  w konsoli wartosc test
 * */
int Klient::get(){
	std::cout<<"oto test from klient "<<test<<std::endl;
}
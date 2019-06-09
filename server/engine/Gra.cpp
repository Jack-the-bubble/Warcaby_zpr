#include "Gra.h"

using namespace std;

/**
	Konstruktor klasy Gra. Tworzy graczy z odpowiednimi identyfikatorami

	@param i identyfikator klienta aplikacji frontendowej
*/

Gra::Gra()
{
	player1 = Kl(new Klient);
	player2 = Kom(new Komputer);
}


Gra::~Gra()
{
//	delete player1, player2;
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

	//Uzytkownik pl1(1);
//	Komputer pl1(1);
//	player1 = &pl1;
//
//	Komputer pl2(-1);
//	player2 = &pl2;
	Move moveToDo;

//	player1 = Kl(new Klient);
//	player2 = Kom(new Komputer);

//	while (plansza.getPionkiBiale() != 0 || plansza.getPionkiCzarne() != 0)
//	{
//		this->player1notify();
//		moveToDo = player1->getBestMove();
//		if (moveToDo.ID == 0)
//		{
//			return;
//		}
//		plansza.makeMove(moveToDo);
//
//		this->drukuj();
//		this->player2notify();
//		//player1->oponentMove(player2->getBestMove());
//		moveToDo = player2->getBestMove();
//		if (moveToDo.ID == 0)
//		{
//			return;
//		}
//		plansza.makeMove(moveToDo);
//		this->drukuj();
//	}

	return;
}

/**
	Funkcja wywolywana gdy gracz 1 ma wykonac ruch
*/
void Gra::player1notify()
{

	this->drukuj();

//	cout<<player1->getID()<<endl;
	player1->update(plansza.plansza);


}

/**
	Funkcja wywolywana gdy gracz 1 ma wykonac ruch
*/
void Gra::player2notify()
{
	player2->update(plansza.plansza);

}

void Gra::klientMoveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap){//(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, int rowC, int colC) {
	cout<<"calling client to create move"<<endl;
	int roC = boost::python::extract<int>(cap[0]);
	int coC = boost::python::extract<int>(cap[1]);
	player1->moveUpdate(begMov_x, begMov_y, destMov_x, destMov_y,cap);
}

void Gra::computerUpdate() {
	plansza.makeMove(player2->getBestMove());
}

void Gra::changePlansza() {
	cout<<"changing plansza after client move"<<endl;
	Move pom = player1->getBestMove();
	cout<<"moving from "<<pom.from[0] <<" "<<pom.from[1]<< " point to "<<pom.to[0] <<" "<<pom.to[1]<<endl;
	plansza.makeMove(pom);
}

pyList Gra::convertAndSend(){
    Move move = player2->getBestMove();
    cout<<"move to make from cpp: "<<move.from[0]<<" "<<move.from[1]<< " point to "<<move.to[0] <<" "<<move.to[1]<<endl;
    plansza.makeMove(player2->getBestMove());
    pyList list;
    list.append(move.from[0]);
	list.append(move.from[1]);
	list.append(move.to[0]);
	list.append(move.to[1]);
	int i = move.capturedRow.size()-1;
	while (i >= 0){
		list.append(move.capturedRow[i]);
		list.append(move.capturedCol[i]);
		i--;
	}

    return list;
}


void Gra::assignID(int i){
	ID_ = i;
}

int Gra::getID(){
	return ID_;
}

int Gra::klientGet(){
	player1->get();
}

void Gra::klientSet(int i){
	player1->set(i);
}
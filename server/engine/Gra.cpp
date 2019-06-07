#include "Gra.h"

using namespace std;



Gra::Gra()
{


Klient* pla = new Klient();
	//Uzytkownik pl1(1);
//	Klient pl1();
	player1 = pla;

    Komputer* pl2 = new Komputer(-1);
//	Komputer pl2(-1);
//	player2 = &pl2;
    player2 = pl2;
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

//
//	Klient* pla = new Klient();
//	//Uzytkownik pl1(1);
////	Klient pl1();
//	player1 = pla;
//
//	Komputer pl2(-1);
//	player2 = &pl2;


//	cout<<pla->getID()<<endl;

	while (!(plansza.isWin())) 
	{
 		this->player1notify();
		plansza.makeMove(player1->getBestMove());
		this->drukuj();
		int i;
		scanf("jo: %d", &i);
		this->player2notify();
		//player1->oponentMove(player2->getBestMove()); 
		plansza.makeMove(player2->getBestMove());
		this->drukuj();
	}

	return;
}

void Gra::player1notify()
{

	this->drukuj();
//	cout<<player3->getID()<<endl;
//	cout<<player1->ready<<endl;
//	cout<<player1->getID()<<endl;
	cout<<player1->getID()<<endl;
	player1->update(plansza.plansza);


}

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
	cout<<"changing plansza"<<endl;
	Move pom = player1->getBestMove();
	cout<<"moving from "<<pom.from[0]<< "point"<<endl;
	plansza.makeMove(pom);
}

pyList Gra::convertAndSend(){
    Move move = player2->getBestMove();
    plansza.makeMove(move);
    pyList list;
    list.append(move.from[0]);
	list.append(move.from[1]);
	list.append(move.to[0]);
	list.append(move.to[1]);
	int i = 0;
	while (i != move.capturedRow.size()){
		list.append(move.capturedRow[i]);
		list.append(move.capturedCol[i]);
		i++;
	}
    return list;
}

//int main(){
//	return 0;
//}

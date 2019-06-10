#include "Gra.h"

using namespace std;

/**
	Konstruktor klasy Gra. Tworzy graczy z odpowiednimi identyfikatorami
*/

Gra::Gra()
{
	player1 = Kl(new Klient);
	player2 = Kom(new Komputer);
}


Gra::~Gra()
{
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
 	sluzy do testowania rozgrywki bez polaczenia z serwerem
*/
void Gra::play()
{
	this->drukuj();
	Move moveToDo;

	while (plansza.getPionkiBiale() != 0 || plansza.getPionkiCzarne() != 0)
	{
		this->player1notify();
		moveToDo = player1->getBestMove();
		if (moveToDo.ID == 0)
		{
			return;
		}
		plansza.makeMove(moveToDo);

		this->drukuj();
		this->player2notify();
		//player1->oponentMove(player2->getBestMove());
		moveToDo = player2->getBestMove();
		if (moveToDo.ID == 0)
		{
			return;
		}
		plansza.makeMove(moveToDo);
		this->drukuj();
	}

	return;
}

/**
	Funkcja wywolywana gdy gracz 1 ma wykonac ruch
*/
void Gra::player1notify()
{
	this->drukuj();
	player1->update(plansza.plansza);
}

/**
	Funkcja wywolywana gdy komputer ma wykonac ruch
*/
void Gra::player2notify()
{
	player2->update(plansza.plansza);

}

/**
 * Funkcja uaktualniajaca pole bestMove po ruchu klienta
 * - wspolrzedne podane sa w notacji, ktorej uzywa logika komputera
 * @param begMov_x - wspolrzedna x poczatkowej pozycji pionka ktory nalezy ruszyc
 * @param begMov_y - wspolrzedna y poczatkowej pozycji pionka ktory nalezy ruszyc
 * @param destMov_x - wspolrzedna x koncowej pozycji pionka ktory nalezy ruszyc
 * @param destMov_y - wspolrzedne y koncowej pozycji pionka ktory nalezy ruszyc
 * @param cap - lista pionkow przeciwnika do usuniecia
 * */
void Gra::klientMoveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap){//(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, int rowC, int colC) {
//	cout<<"calling client to create move"<<endl;
	player1->moveUpdate(begMov_x, begMov_y, destMov_x, destMov_y,cap);
}

/**
 * funkcja uaktualniajaca plansze gry po ruchu komputera korzystajac ruchu
 * zapisanego w bestMove
 * */
void Gra::computerUpdate() {
	plansza.makeMove(player2->getBestMove());
}

/**
 * funkcja uaktualniajaca plansze gry po ruchu klienta korzystajac z ruchu
 * zapisanego w latestMove
 * */
void Gra::changePlansza() {
	plansza.makeMove(player1->getBestMove());
}

/**
 * funkcja tlumaczy na notacje klienta i wysyla ruch komputera do serwera
 * w pytohnie
 * */
pyList Gra::convertAndSend(){
    Move move = player2->getBestMove();
//    cout<<"move to make from cpp: "<<move.from[0]<<" "<<move.from[1]<< " point to "<<move.to[0] <<" "<<move.to[1]<<endl;
    plansza.makeMove(move);
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

/**
 * funkcja testuje komunikacje z serwerem
 * @param i - nowe ID gry
 * */
void Gra::assignID(int i){
	ID_ = i;
}


/**
 * funkcja zwraca zapisane ID gry
 * */
int Gra::getID(){
	return ID_;
}


/**
 * funkcja zwraca zapisane ID klienta
 * */
int Gra::klientGet(){
	player1->get();
}

/**
 * funkcja ustawia pole test klienta
 * @param i - ustawia wartosc
 * */
void Gra::klientSet(int i){
	player1->set(i);
}
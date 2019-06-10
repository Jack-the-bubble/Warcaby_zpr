

#ifndef _KOMPUTER_H_
#define _KOMPUTER_H_

#include <vector>
#include<list>
#include "Gracz.h"
#include "Move.h"


/**
 *  \brief     Klasa sztucznej inteligencji, odpowiadza za wykonywanie ruchów komputera
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
class Komputer :
	public Gracz
{
public:
	Komputer();
	~Komputer();
	virtual void update(const int plansza[8][8]); /**wykonuje algorytm mini-max*/
	virtual int getID();
	virtual Move getBestMove(); /**zwraca ruch zapisany w polu bestMove*/
private:
	int graczID; /**wartosc -1 dla komputera*/
	int depthMax = 15; /**glebokosc przeszukiwania algorytmu*/
	bool biciePossible = false; /**zmienna okreslajaca przymus bicia w danej turze*/
	int k_, w_; /**aktualnie rozpatrywany pionek*/
	int alfabetaFirst(int, int, int);/**metoda inicjujaca algorytm mini-max*/
	int myCnt, oponentCnt;
	bool possibleMoves(int);
	int wygrana();
	bool bicie(int, int, int);
	int next_w[12], next_k[12];
	bool czyBicie(int ID);
	int alfabeta(int, int, int, int);
	int markBrd(); /**funkcja zwracajaca ocene planszy dla mini-max*/

	const int WAGA_PIONKA = 50; /**wagi pionka do algorytmu mini-max*/
	const int WAGA_DAMKI = 150; /**wagi damki do algorytmu mini-max*/
	bool czyRuchBezBicia(int ID, int dir, int k, int w);
	std::list<Move> nextPositions(int ID, int dir, int k, int w); /**lista ruchów rozpatrywanych przez algorytm mini-max*/
	void makeMove(Move); /**funkcja modyfikujaca plansze*/
	void rollBackMove(Move); /**funkcja cofajaca ruch*/
}; 

#endif
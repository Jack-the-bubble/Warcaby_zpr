//#pragma once
#ifndef _KOMPUTER_H_
#define _KOMPUTER_H_

#include <vector>
#include<list>
#include "Gracz.h"
//#include "Move.h"

/**
 *  \brief     Klasa komputera(bota) w grze. Bot o swoim ruchu decyduje na podstawie algorytmu minimax z odcinaniem alfa-beta
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
class Komputer :
	public Gracz
{
public:
	Komputer(int graczID_);
	Komputer();
	~Komputer();
	virtual void update(const int plansza[8][8]);
	virtual int getID();
	virtual Move getBestMove() ;
	
private:
	int graczID; /**< identyfikator gracza */
	int depthMax = 6; /**< glebokosc przeszukiwania algorytmu */
	bool biciePossible = false;   /**< flaga przymusu bicia */
	int k_;  /**< aktualnie rozpatrywany pionek - wspolrzedna kolumna */
	int w_;  /**< aktualnie rozpatrywany pionek - wspolrzedna wiersz */
	const int WAGA_PIONKA = 50; /**< waga pionka uzywana w heurystyce oceniajacej */
	const int WAGA_DAMKI = 150; /**< waga damki uzywana w heurystyce oceniajacej */
	int myCnt;  /**< wejsciowa liczba pionkow gracza */
	int oponentCnt;  /**< wejsciowa liczba pionkow przeciwnika */
	Move bestMove;  /**< ruch wykonany w nastepnym posunieciu wskazany przez algorytm minimax */
	int next_w[12];   /**< tablica pionkow o mozliwosci ruchu - wspolrzedna wiersz */
	int next_k[12];   /**< tablica pionkow o mozliwosci ruchu - wspolrzedna kolumna */

	int alfabetaFirst(int, int, int);
	bool possibleMoves(int);
	int wygrana();
	bool bicie(int, int, int);
	bool bicieDamka(int, int, int);
	bool czyBicie(int ID);
	int alfabeta(int, int, int, int);	
	int markBrd();
	bool czyRuchBezBicia(int ID, int dir, int k, int w);
	std::list<Move> nextPositions(int ID, int dir, int k, int w);
	std::list<Move> nextKingPositions(int ID, int dir, int k, int w);
	bool isKingMoveBack(int ID, int dir, int k, int w);
	void makeMove(Move);
	void rollBackMove(Move);
}; 

#endif
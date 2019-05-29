//#pragma once


#include <vector>
#include<list>
#include "Gracz.h"
//#include "Move.h"
class Komputer :
	public Gracz
{
public:
	Komputer(int graczID_);
	~Komputer();
	virtual void update(const int plansza[8][8]);
	virtual int getID();
	virtual Move getBestMove() ;
	
private:
	int graczID;
	int depthMax = 6; //glebokosc przeszukiwania algorytmu
	bool biciePossible = false;
	int k_, w_; //aktualnie rozpatrywany pionek

	int alfabetaFirst(int, int, int);
	bool possibleMoves(int);
	int wygrana();
	bool bicie(int, int, int);
	bool bicieDamka(int, int, int);

	int next_w[12], next_k[12];
	bool czyBicie(int ID);
	int alfabeta(int, int, int, int);
	
	int markBrd();

	const int waga_pionka = 50;
	const int waga_damki = 150;
	int myCnt, oponentCnt;

	
	Move bestMove;
	bool czyRuchBezBicia(int ID, int dir, int k, int w);
	std::list<Move> nextPositions(int ID, int dir, int k, int w);
	std::list<Move> nextKingPositions(int ID, int dir, int k, int w);
	bool isKingMoveBack(int ID, int dir, int k, int w);
//	int boardCopy[8][8];
	void makeMove(Move);
	void rollBackMove(Move);
}; 


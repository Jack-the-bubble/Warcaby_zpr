#pragma once
#include "Gracz.h"
class Uzytkownik :
	public Gracz
{
public:
	Uzytkownik(int id);
	~Uzytkownik();

	virtual bool wybierzPionek();  //tymczasowo pobiera z cin
	bool makeMove(); //tymczasowo pobiera z cin
	int getID();
	virtual int getPrevK();
	virtual int getPrevW();
	virtual int getK();
	virtual int getW();
	virtual void update( const int plansza [8][8]);
	int possibleMoves();
	int bicie( int,int,int);


private:
	int k_,w_;
	int prev_k, prev_w;
	bool wybrano = false;
	int gracz_id;
	int next_k[10], next_w[10];
	int moves_;
	int boardCopy[8][8];
	int doZbicia_k[8], doZbicia_w[8];
	int zbicie;
};


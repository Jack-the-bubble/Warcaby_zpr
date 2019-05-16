#pragma once
#include "Gracz.h"
class Klient :
	public Gracz
{
public:
	Klient(int);
	~Klient();
	virtual void update(const int plansza[8][8]);
	virtual int getID();
	int planszaCopy[8][8];
	bool ready = false;
	int graczID;
};


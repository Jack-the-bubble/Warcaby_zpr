#pragma once
class Gracz
{
public:
	Gracz();
	virtual ~Gracz();
	virtual int getID() = 0;
	virtual int getPrevK() = 0;
	virtual int getPrevW() = 0;
	virtual int getK() = 0;
	virtual int getW() = 0;
	virtual void update (const int plansza[8][8]) = 0;
};


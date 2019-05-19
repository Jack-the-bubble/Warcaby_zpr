//#pragma once
class Gracz
{
public:
	Gracz(){};
	virtual ~Gracz(){};
	virtual int getID() = 0;
	virtual int getPrevK() { return 0; };    //to usuniemy jak bedzie komputer
	virtual int getPrevW() { return 0; };	//to usuniemy jak bedzie komputer
	virtual int getK() { return 0; };	//to usuniemy jak bedzie komputer
	virtual int getW() { return 0; };	//to usuniemy jak bedzie komputer
	virtual void update (/*const int plansza[8][8]*/) = 0;
	int boardCopy[8][8];
};


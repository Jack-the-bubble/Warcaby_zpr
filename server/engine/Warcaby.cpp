// Warcaby.cpp : Ten plik zawiera funkcj� �main�. W nim rozpoczyna si� i ko�czy wykonywanie programu.
/**
	ZPR projekt
	Warcaby.cpp
	@author Katarzyna Seweryn, Marcin Skrzypkowski
*/


#include <iostream>
#include <memory>
#include <string>

#include "Gra.h"


using namespace std;

int main()
{
	Gra* gra1;
	gra1 = new Gra();
	gra1->play();
	return 0;
}
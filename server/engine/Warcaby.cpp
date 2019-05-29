// Warcaby.cpp : Ten plik zawiera funkcje „main”. W nim rozpoczyna sie i koñczy wykonywanie programu.
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
	Gra gra1;
	gra1.play();
	cout << "end of game" << endl;
	while (true) {}
	return 0;
}
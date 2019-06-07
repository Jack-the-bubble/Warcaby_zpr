//#pragma once

#ifndef __MOVE_H__
#define __MOVE_H__

#include<vector>


/**
 *  \brief     Klasa ruchu. Zawiera wspolrzedne poczatkowe i koncowe pionka oraz wspolrzedne zbitych pionkow przeciwnika w danym ruchu.
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
class Move
{
public:
	Move(int from_r, int from_c, int to_r, int to_c, int ID_, int rowC = -1, int colC = -1);
	Move();
	~Move();
	int from[2]; /**< wspolrzedne punktu startowego [wiersz kolumna] */
	int to[2]; /**< wspolrzedne punktu docelowego [wiersz kolumna] */
	std::vector<int> capturedRow; /**< wektor numerow kolumn zbitych pionkow */
	std::vector<int> capturedCol; /**< wektor numerow wierszy zbitych pionkow */
	int ID; /**< identyfikator gracza wykonujacego ruch */
	void addCaptured(int row, int col);
	void operator= (Move);
	void createKing();
	bool kingCreate = false;
};

#endif
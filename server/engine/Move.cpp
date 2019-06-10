#include "Move.h"

Move::Move()
{
	from[0] = 0;
	from[1] = 0;
	to[0] = 0;
	to[1] = 0;
	ID = 0;
}

/**
 * konstruktor obiektu ruchu pionkiem z parametrami
 * @param from_r - wiersz poczatkowej pozycji pionka
 * @param from_c - kolumna poczatkowej pozycji pionka
 * @param to_r - wiersz koncowej pozycji pionka
 * @param to_r - kolumna koncowej pozycji pionka
 * @param ID_ - identyfikator ruchu
 * @param rowC - rzad pionka do usuniecia - jesli brak bicia, ma wartosc -1
 * @param colC - kolumna pionka do usuniecia - jesli brak bicia, ma wartosc -1
 * */
Move::Move(int from_r, int from_c, int to_r, int to_c, int ID_, int rowC, int colC)
{
	from[0] = from_r;
	from[1] = from_c;
	to[0] = to_r;
	to[1] = to_c;
	if (rowC > -1)
	{
		capturedRow.push_back(rowC);
		capturedCol.push_back(colC);
	}
	
	ID = ID_;
}


Move::~Move()
{
}

/**
	Dodanie pionka zbitego w ruchu.

	@param row wiersz zbitego pionka
	@param col kolumna zbitego pionka
*/
void Move::addCaptured(int row, int col)
{
	capturedRow.push_back(row);
	capturedCol.push_back(col);
}

void Move::operator=(Move toCopy)
{
	from[0] = toCopy.from[0];
	from[1] = toCopy.from[1];
	to[0] = toCopy.to[0];
	to[1] = toCopy.to[1];
	ID = toCopy.ID;
	capturedCol = toCopy.capturedCol;
	capturedRow = toCopy.capturedRow;

}

void Move::createKing()
{
	ID = 2 * ID;
}

void Move::printMove() {
	std::cout<<"moving from "<<from[0] <<" "<<from[1]<< " point to "<<to[0] <<" "<<to[1]<<std::endl;
}
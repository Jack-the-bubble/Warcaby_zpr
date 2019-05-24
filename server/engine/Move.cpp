#include "Move.h"

Move::Move()
{
	from[0] = 0;
	from[1] = 0;
	to[0] = 0;
	to[1] = 0;
	ID = 0;
}

Move::Move(int from_r, int from_c, int to_r, int to_c, int ID_, int rowC, int colC )
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

void Move::addCaptured(int row, int col)
{
	capturedRow.push_back(row);
	capturedCol.push_back(col);
}
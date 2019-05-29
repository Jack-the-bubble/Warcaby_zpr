#include "PomBoard.h"

PomBoard::PomBoard()
{
}

PomBoard::PomBoard(int brd_[8][8])
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			brd[i][j] = brd_[i][j];
	}

}


PomBoard::~PomBoard()
{
}

void PomBoard::operator=(PomBoard p2)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			brd[i][j] = p2.brd[i][j];
	}
}
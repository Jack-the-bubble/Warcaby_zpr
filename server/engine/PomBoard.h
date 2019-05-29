#pragma once
class PomBoard
{
public:
	PomBoard();
	PomBoard(int brd_[8][8]);
	~PomBoard();
	int brd[8][8];
	void operator= (PomBoard);
};


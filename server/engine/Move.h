#pragma once
#include<vector>
class Move
{
public:
	Move(int from_r, int from_c, int to_r, int to_c, int ID_, int rowC = -1, int colC = -1);
	Move();
	~Move();
	int from[2]; //[row column]
	int to[2]; //[row column]
	std::vector<int> capturedRow;
	std::vector<int> capturedCol;
	int ID;
	void addCaptured(int row, int col);
};


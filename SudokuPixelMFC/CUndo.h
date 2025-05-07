#pragma once
#include "CSudoku.h"

class CUndo
{
private:
	struct Turn
	{
		int number;
		int row;
		int column;
	};

	Turn stack[100];
	int top;

public:
	CUndo();

	bool StoreInStack(int number, int row, int column);

	void ResetStack();

	bool Undo(CSudoku& sudoku);
};


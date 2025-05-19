#pragma once
#include "CSudoku.h"

class CSolve
{
private:

public:
	CSolve();

	bool Check(CSudoku& sudoku);

	bool Automatically(CSudoku& sudoku);

	bool CheckNumber(CSudoku& sudoku, int number, int row, int column);
};


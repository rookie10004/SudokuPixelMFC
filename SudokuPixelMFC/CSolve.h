#pragma once
#include "CSudoku.h"

class CSolve
{
private:

public:
	CSolve();

	bool Check(CSudoku& sudoku); //überprüft Sudoku auf Richtigkeit

	bool Automatically(CSudoku& sudoku); //löst Sudoku automatisch mit backtracking

	bool CheckNumber(CSudoku& sudoku, int number, int row, int column); //überprüft ob Zahl in der Reihe/Spalte/Quadrat existíert (Hilsfunktion von Automatically)
};


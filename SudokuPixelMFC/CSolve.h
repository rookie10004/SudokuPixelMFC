#pragma once
#include "CSudoku.h"

class CSolve
{
private:

public:
	CSolve();

	bool Check(CSudoku& sudoku); //�berpr�ft Sudoku auf Richtigkeit

	bool Automatically(CSudoku& sudoku); //l�st Sudoku automatisch mit backtracking

	bool CheckNumber(CSudoku& sudoku, int number, int row, int column); //�berpr�ft ob Zahl in der Reihe/Spalte/Quadrat exist�ert (Hilsfunktion von Automatically)
};


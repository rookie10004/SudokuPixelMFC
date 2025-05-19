#include "pch.h"
#include "CSolve.h"

CSolve::CSolve()
{
}

bool CSolve::Check(CSudoku& sudoku)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku.GetCurrentNumber(i, j) == '0')
			{
				return false;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = j + 1; k < 9; k++)
			{
				if (sudoku.GetCurrentNumber(i, j) == sudoku.GetCurrentNumber(i, k))
				{
					return false;
				}
			}
		}
	}

	for (int i = 0; i < 9; i++)	
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = j + 1; k < 9; k++)
			{
				if (sudoku.GetCurrentNumber(j, i) == sudoku.GetCurrentNumber(k, i))
				{
					return false;
				}
			}
		}
	}

	for (int QuadratZeile = 0; QuadratZeile < 3; QuadratZeile++)	
	{
		for (int QuadratSpalte = 0; QuadratSpalte < 3; QuadratSpalte++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = i; k < 3; k++)
					{
						for (int l = (k == i ? j + 1 : 0); l < 3; l++)
						{
							if (sudoku.GetCurrentNumber(QuadratZeile * 3 + i, QuadratSpalte * 3 + j) == sudoku.GetCurrentNumber(QuadratZeile * 3 + k, QuadratSpalte * 3 + l))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}

	return true;
}

bool CSolve::Automatically(CSudoku& sudoku)
{
	int row, column;
	bool isFieldEmpty = false;
	for (int i = 0; i < 9 && !isFieldEmpty; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku.GetCurrentNumber(i, j) == 0)
			{
				column = j;
				row = i;
				isFieldEmpty = true;
				break;
			}
		}
	}

	if (!isFieldEmpty)
	{
		return true;
	}

	for (int number = 1; number <= 9; number++)
	{
		if (CheckNumber(sudoku, number, row, column) == true)
		{
			sudoku.SetCurrentNumber(number, row, column);
			if (Automatically(sudoku) == true)
			{
				return true;
			}
			sudoku.SetCurrentNumber(0, row, column);
		}
	}

	return false;
}

bool CSolve::CheckNumber(CSudoku& sudoku, int number, int row, int column)
{
	for (int i = 0; i < 9; i++)
	{
		if (sudoku.GetCurrentNumber(i, column) == number)
		{
			return false;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (sudoku.GetCurrentNumber(row, i) == number)
		{
			return false;
		}
	}

	int startColumn = column - column % 3;
	int startRow = row - row % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (sudoku.GetCurrentNumber(startRow + i, startColumn + j) == number)
			{
				return false;
			}
		}
	}

	return true;
}

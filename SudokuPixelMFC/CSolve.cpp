#include "pch.h"
#include "CSolve.h"

CSolve::CSolve()
{
}

bool CSolve::Check(CSudoku& sudoku)
{
	int value;

	for (int i= 0; i< 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			value = sudoku.GetCurrentNumber(i, j);
			if (value != 0)
			{
				sudoku.SetCurrentNumber(0, i, j);

				if (!CheckNumber(sudoku, value, i, j))
				{
					sudoku.SetCurrentNumber(value, i, j);
					return false;
				}

				sudoku.SetCurrentNumber(value, i, j);
			}
			else
			{
				return false;
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
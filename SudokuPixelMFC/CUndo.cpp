#include "pch.h"
#include "CUndo.h"

CUndo::CUndo()
{
	top = -1;
}

bool CUndo::StoreInStack(int number, int row, int column)
{
	if (top < 99)
	{
		++top;
		stack[top].number = number;
		stack[top].row = row;
		stack[top].column = column;
		return true;
	}
	else
	{
		return false;
	}
}

void CUndo::ResetStack()
{
	top = -1;
}

bool CUndo::Undo(CSudoku& sudoku)
{
	if (top >= 0)
	{
		sudoku.SetCurrentNumber(stack[top].number, stack[top].row, stack[top].column);
		top--;
		return true;
	}
	return false;
}


#include "pch.h"
#include "CUndo.h"


CUndo::~CUndo()
{
	stack.clear();
}

void CUndo::StoreInStack(int number, int row, int column)
{
	Turn temp = { number, row, column };
	stack.push_back(temp);
}

bool CUndo::Undo(CSudoku& sudoku)
{
	if (stack.empty())
	{
		return false;
	}

	Turn temp = stack.back();
	sudoku.SetCurrentNumber(temp.number, temp.row, temp.column);
	stack.pop_back();

	return true;
}

bool CUndo::isEmpty()
{
	return stack.empty();
}

void CUndo::ClearStack()
{
	stack.clear();
}

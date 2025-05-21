#pragma once
#include "CSudoku.h"
#include <vector>

class CUndo
{
private:
	struct Turn
	{
		int number;
		int row;
		int column;
	};

	std::vector<Turn> stack;

public:
	~CUndo();

	void StoreInStack(int number, int row, int column); //speichert Daten in Vector

	bool Undo(CSudoku& sudoku); //l�scht das letzte Element

	bool isEmpty(); //�berpr�ft ob vector leer ist

	Turn& GetStack() { return stack.back(); };

	void ClearStack(); //l�scht den Vector
};


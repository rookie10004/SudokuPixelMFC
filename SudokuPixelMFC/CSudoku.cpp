#include "pch.h"
#include "CSudoku.h"

CSudoku::CSudoku()
{
}

void CSudoku::SetFilePath(std::string fPath)
{
	filePath = fPath;
}

int CSudoku::GetCurrentNumber(int row, int column)
{
	return current[row][column];
}

int CSudoku::GetOriginalNumber(int row, int column)
{
	return original[row][column];
}

int CSudoku::GetOriginalNumber(CVec2& index)
{
	return original[index.y][index.x];
}

void CSudoku::SetCurrentNumber(int number, int row, int column)
{
	current[row][column] = number;
}

void CSudoku::LoadNewGame()
{
	std::ifstream file(filePath);

	if (!file)
	{
		AfxMessageBox(L"File open error");
		OnCancel();
	}

	int column = 0, row = 0;
	char ch;
	int count = 0;
	while (file.get(ch) && count < 81)
	{
		if (ch >= '0' && ch <= '9')
		{
			current[row][column] = ch - '0';
			original[row][column] = ch - '0';
			column++;
		}
		if (column == 9)
		{
			row++;
			column = 0;
		}
		count++;
	}

	file.close();
}

void CSudoku::LoadOldGame()
{
	std::ifstream file(filePath);

	if (!file)
	{
		AfxMessageBox(L"File open error");
		OnCancel();
	}

	int column = 0, row = 0;
	char ch;
	while (file.get(ch) && ch != '\n')
	{
		original[row][column] = ch - '0';
		column++;
		if (column == 9)
		{
			row++;
			column = 0;
		}
	}

	row = 0, column = 0;
	while (file.get(ch))
	{
		current[row][column] = ch - '0';
		column++;
		if (column == 9)
		{
			row++;
			column = 0;
		}
	}

	file.close();
}

void CSudoku::StoreSavegame()
{
	std::ofstream file(filePath);

	if (!file)
	{
		AfxMessageBox(L"File open error");
		OnCancel();
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			file << original[i][j];
		}
	}

	file << '\n';

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			file << current[i][j];
		}
	}

	file.close();
}

void CSudoku::ResetArrays()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			current[i][j] = 0;
			original[i][j] = 0;
		}
	}
}

bool CSudoku::CheckSavegame()
{
	std::ifstream file(filePath);

	if (!file)
	{
		AfxMessageBox(L"File open error");
		OnCancel();
	}

	int count = 0;
	while (file.get() != EOF)
	{
		count++;
	}

	if (count > 81)
	{
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

void CSudoku::CopyArray()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			current[i][j] = original[i][j];
		}
	}
}

bool CSudoku::GenerateRandomSudoku()
{
	//solver.SolveSudoku(); generiert vollständiges Sudoku aber füge noch ein paar random Zahlen ein für den Seed
	return false;
}

void CSudoku::RemoveNumbers()
{
	int removed = 0;
	int countToRemoved = 40 + (static_cast<int>(difficulty) - 1) * 4;
	while (removed < countToRemoved)
	{
		int row = rand() % 9;
		int column = rand() % 9;
		if (current[row][column] != 0)
		{
			current[row][column] = 0;
		}
	}
}

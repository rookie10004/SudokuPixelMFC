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
		throw FileException("Error opening file:" + filePath);
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
		throw FileException("Error opening file:" + filePath);
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
		throw FileException("Error opening file:" + filePath);
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

bool CSudoku::CheckSavegame()
{
	std::ifstream file(filePath);

	if (!file)
	{
		throw FileException("Error opening file:" + filePath);
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
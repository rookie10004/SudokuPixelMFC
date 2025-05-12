#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <afxwin.h>

class CSudoku : CDialog
{
public:
	enum class Difficulty : int
	{
		Easy,
		Medium,
		Hard,
		Expert,
		God
	};

private:
	std::string filePath;

	int current[9][9] = {};
	int original[9][9] = {};

	Difficulty difficulty;

public:
	CSudoku();

	CSudoku(std::string filePath, Difficulty difficulty = Difficulty::Easy);

	int GetCurrentNumber(int row, int column);

	int GetOriginalNumber(int row, int column);

	void SetCurrentNumber(int number, int  row, int column);

	void LoadNewGame();

	void LoadOldGame();

	void StoreSavegame();

	void ResetArrays();

	bool CheckSavegame();

	void CopyArray();

	bool GenerateRandomSudoku();

	void RemoveNumbers();
};


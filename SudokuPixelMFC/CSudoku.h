#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <afxwin.h>
#include "CVec2.h"

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

	void SetFilePath(std::string fPath);

	int GetCurrentNumber(int row, int column);

	int GetOriginalNumber(int row, int column);

	int GetOriginalNumber(CVec2& index);

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


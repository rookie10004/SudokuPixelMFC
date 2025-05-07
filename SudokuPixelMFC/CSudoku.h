#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <afxwin.h>

class CSudoku : CDialog
{
public:
	enum class Mode : int
	{
		NewGame,
		OldGame
	};

	enum class Difficulty : int
	{
		VeryEasy,
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

	Mode mode;
	Difficulty difficulty;

public:
	CSudoku();

	CSudoku(std::string filePath, Mode mode, Difficulty difficulty);

	int GetCurrentNumber(int row, int column);

	int GetOriginalNumber(int row, int column);

	void SetCurrentNumber(int number, int  row, int column);

	void LoadNewGame();

	void LoadOldGame();

	void StoreSavegame();

	void ResetArrays();

	bool CheckSavegame(std::string filePath);

	void CopyArray();

	bool GenerateRandomSudoku();

	void RemoveNumbers();
};


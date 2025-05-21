#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <afxwin.h>
#include "CVec2.h"
#include "Exceptions.h"

class CSudoku : CDialog
{
private:
	std::string filePath;

	int current[9][9] = {};
	int original[9][9] = {};

public:
	CSudoku();

	void SetFilePath(std::string fPath);

	int GetCurrentNumber(int row, int column);

	int GetOriginalNumber(int row, int column);

	int GetOriginalNumber(CVec2& index);

	void SetCurrentNumber(int number, int  row, int column);

	void LoadNewGame(); //l�dt aus der ersten Zeile die Werte ins array

	void LoadOldGame(); //l�dt aus der ersten und zweiten Zeile die Werte ins array

	void StoreSavegame(); //speichert die Werte in der zweiten Zeile

	bool CheckSavegame(); //�berpr�ft auf bereits vorhandenen Spielstand
};


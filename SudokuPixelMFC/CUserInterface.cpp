#include "pch.h"
#include "CUserInterface.h"
#include "SudokuPixelMFCDlg.h"


bool CUserInterface::OnInitSpritesSudoku(CSudoku& sudoku)
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuBackground.bmp load error");
		return false;
	}
	spriteListSudoku.SetWorkspace(&buffer);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku.GetCurrentNumber(i, j) != 0)
			{
				int x = j * tileSize.x + offset.x + (j / 3) * blockSpacing.x + tileSize.x - numberSize.x - 2;
				int y = i * tileSize.y + offset.y + (i / 3) * blockSpacing.y + tileSize.y - numberSize.y - 2;
				CVec2 position{ x, y };
				SetCell(position, sudoku.GetCurrentNumber(i, j));
			}
		}
	}

	if (!selectFrame.Load("./SudokuFieldSelect.bmp"))
	{
		AfxMessageBox(L"SudokuFieldSelect.bmp load error");
		return false;
	}
	selectFrame.SetZ(0);
	selectFrame.SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectFrame);

	if (!selectDimension[0].Load("./SudokuGridColumnSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridColumnSelect.bmp load error");
		return false;
	}
	selectDimension[0].SetZ(0);
	selectDimension[0].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[0]);

	if (!selectDimension[1].Load("./SudokuGridRowSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridRowSelect.bmp load error");
		return false;
	}
	selectDimension[1].SetZ(0);
	selectDimension[1].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[1]);

	if (!frame.Load("./SudokuGrid423x423.bmp"))
	{
		AfxMessageBox(L"SudokuGrid423x423.bmp load error");
		return false;
	}
	frame.SetZ(0);
	frame.SetPosition(offset.x, offset.y);
	spriteListSudoku.Insert(&frame);

	if (!LoadSpriteButton("ButtonBack", buttonBack, backButtonSize, spriteListSudoku, offset.x + undoButtonSize.x + checkButtonSize.x + blockSpacing.x * 2, buttonRowFirst.y, 0) ||
		!LoadSpriteButton("ButtonUndo", buttonUndo, undoButtonSize, spriteListSudoku, offset.x, buttonRowFirst.y, 0) ||
		!LoadSpriteButton("ButtonReset", buttonReset, resetButtonSize, spriteListSudoku, offset.x, buttonRowSecond.y, 0) ||
		!LoadSpriteButton("ButtonCheck", buttonCheck, checkButtonSize, spriteListSudoku, offset.x + undoButtonSize.x + blockSpacing.x, buttonRowFirst.y, 0) ||
		!LoadSpriteButton("ButtonSolve", buttonSolve, solveButtonSize, spriteListSudoku, offset.x + resetButtonSize.x + blockSpacing.x, buttonRowSecond.y, 0) ||
		!LoadSpriteButton("ButtonSave", buttonSave, saveButtonSize, spriteListSudoku, offset.x, buttonRowThird.y, 0) ||
		!LoadSpriteButton("ButtonExit", buttonExit, exitButtonSize, spriteListSudoku, offset.x + resetButtonSize.x + solveButtonSize.x + blockSpacing.x * 2, buttonRowSecond.y, 0))
	{
		return false;
	}

	return true;
}

bool CUserInterface::OnInitSpritesSelection()
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuBackground.bmp load error");
		return false;
	}
	spriteListSelection.SetWorkspace(&buffer);
	
	if (!LoadSpriteButton("ButtonEasy", buttonEasy, easyButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y, 0) ||
		!LoadSpriteButton("ButtonMedium", buttonMedium, mediumButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 1, 0) ||
		!LoadSpriteButton("ButtonHard", buttonHard, hardButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 2, 0) ||
		!LoadSpriteButton("ButtonExpert", buttonExpert, expertButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 3, 0) ||
		!LoadSpriteButton("ButtonGod", buttonGod, godButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 4, 0) ||
		!LoadSpriteButton("ButtonExit", buttonExit, exitButtonSize, spriteListSelection, buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 5.5, 0))
	{
		return false;
	}

	return true;
}

bool CUserInterface::LoadSpriteButton(std::string name, CSprite sprite[], CVec2 vec2, CSpriteList& spriteList, int x, int y, int z)
{
	std::string p = "./" + name + ".bmp";
	std::vector<char> path(p.begin(), p.end()); //Load() hat kein overload für const char* --> konvertiert zu char*
	path.push_back('\0');

	if (!sprite[Status::Default].Load(path.data()))
	{
		AfxMessageBox(L"load error!");
		return false;
	}
	sprite[Status::Default].SetZ(z);
	sprite[Status::Default].SetPosition(x, y);
	spriteList.Insert(&sprite[Status::Default]);

	p = "./" + name + "Pressed.bmp";
	std::vector<char>vPath(p.begin(), p.end());
	vPath.push_back('\0');

	if (!sprite[Status::Pressed].Load(vPath.data(), CSize(vec2.x, vec2.y), false))
	{
		AfxMessageBox(L"load error");
		return false;
	}

	return true;
}

bool CUserInterface::OnLButtonUpSelection(CPoint point, CSudoku& sudoku)
{
	RemoveSprites();

	if (point.x >= buttonExit[Status::Default].GetXPos() &&
		point.x <= exitButtonSize.x + buttonExit[Status::Default].GetXPos() &&
		point.y >= buttonExit[Status::Default].GetYPos() &&
		point.y <= exitButtonSize.y + buttonExit[Status::Default].GetYPos())
	{
		exit(0);
	}

	if (point.x >= buttonEasy[Status::Default].GetXPos() &&
		point.x <= easyButtonSize.x + buttonEasy[Status::Default].GetXPos() &&
		point.y >= buttonEasy[Status::Default].GetYPos() &&
		point.y <= easyButtonSize.y + buttonEasy[Status::Default].GetYPos())
	{
		sudoku.SetFilePath("./sudoku1.txt");
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
		return true;
	}

	if (point.x >= buttonMedium[Status::Default].GetXPos() &&
		point.x <= mediumButtonSize.x + buttonMedium[Status::Default].GetXPos() &&
		point.y >= buttonMedium[Status::Default].GetYPos() &&
		point.y <= mediumButtonSize.y + buttonMedium[Status::Default].GetYPos())
	{
		sudoku.SetFilePath("./sudoku2.txt");
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
		return true;
	}

	if (point.x >= buttonHard[Status::Default].GetXPos() &&
		point.x <= hardButtonSize.x + buttonHard[Status::Default].GetXPos() &&
		point.y >= buttonHard[Status::Default].GetYPos() &&
		point.y <= hardButtonSize.y + buttonHard[Status::Default].GetYPos())
	{
		sudoku.SetFilePath("./sudoku3.txt");
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
		return true;
	}

	if (point.x >= buttonExpert[Status::Default].GetXPos() &&
		point.x <= expertButtonSize.x + buttonExpert[Status::Default].GetXPos() &&
		point.y >= buttonExpert[Status::Default].GetYPos() &&
		point.y <= expertButtonSize.y + buttonExpert[Status::Default].GetYPos())
	{
		sudoku.SetFilePath("./sudoku4.txt");
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
		return true;
	}

	if (point.x >= buttonGod[Status::Default].GetXPos() &&
		point.x <= godButtonSize.x + buttonGod[Status::Default].GetXPos() &&
		point.y >= buttonGod[Status::Default].GetYPos() &&
		point.y <= godButtonSize.y + buttonGod[Status::Default].GetYPos())
	{
		sudoku.SetFilePath("./sudoku5.txt");
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
		return true;
	}

	return false;
}

void CUserInterface::OnLButtonDownSelection(CPoint point)
{
	if (point.x >= buttonEasy[Status::Default].GetXPos() &&
		point.x <= easyButtonSize.x + buttonEasy[Status::Default].GetXPos() &&
		point.y >= buttonEasy[Status::Default].GetYPos() &&
		point.y <= easyButtonSize.y + buttonEasy[Status::Default].GetYPos())
	{
		buttonEasy[Status::Pressed].SetZ(3);
		buttonEasy[Status::Pressed].SetPosition(buttonEasy[Status::Default].GetXPos(), buttonEasy[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonEasy[Status::Pressed]);
	}

	if (point.x >= buttonMedium[Status::Default].GetXPos() &&
		point.x <= mediumButtonSize.x + buttonMedium[Status::Default].GetXPos() &&
		point.y >= buttonMedium[Status::Default].GetYPos() &&
		point.y <= mediumButtonSize.y + buttonMedium[Status::Default].GetYPos())
	{
		buttonMedium[Status::Pressed].SetZ(3);
		buttonMedium[Status::Pressed].SetPosition(buttonMedium[Status::Default].GetXPos(), buttonMedium[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonMedium[Status::Pressed]);
	}

	if (point.x >= buttonHard[Status::Default].GetXPos() &&
		point.x <= hardButtonSize.x + buttonHard[Status::Default].GetXPos() &&
		point.y >= buttonHard[Status::Default].GetYPos() &&
		point.y <= hardButtonSize.y + buttonHard[Status::Default].GetYPos())
	{
		buttonHard[Status::Pressed].SetZ(3);
		buttonHard[Status::Pressed].SetPosition(buttonHard[Status::Default].GetXPos(), buttonHard[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonHard[Status::Pressed]);
	}

	if (point.x >= buttonExpert[Status::Default].GetXPos() &&
		point.x <= expertButtonSize.x + buttonExpert[Status::Default].GetXPos() &&
		point.y >= buttonExpert[Status::Default].GetYPos() &&
		point.y <= expertButtonSize.y + buttonExpert[Status::Default].GetYPos())
	{
		buttonExpert[Status::Pressed].SetZ(3);
		buttonExpert[Status::Pressed].SetPosition(buttonExpert[Status::Default].GetXPos(), buttonExpert[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonExpert[Status::Pressed]);
	}

	if (point.x >= buttonGod[Status::Default].GetXPos() &&
		point.x <= godButtonSize.x + buttonGod[Status::Default].GetXPos() &&
		point.y >= buttonGod[Status::Default].GetYPos() &&
		point.y <= godButtonSize.y + buttonGod[Status::Default].GetYPos())
	{
		buttonGod[Status::Pressed].SetZ(3);
		buttonGod[Status::Pressed].SetPosition(buttonGod[Status::Default].GetXPos(), buttonGod[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonGod[Status::Pressed]);
	}

	if (point.x >= buttonExit[Status::Default].GetXPos() &&
		point.x <= exitButtonSize.x + buttonExit[Status::Default].GetXPos() &&
		point.y >= buttonExit[Status::Default].GetYPos() &&
		point.y <= exitButtonSize.y + buttonExit[Status::Default].GetYPos())
	{
		buttonExit[Status::Pressed].SetZ(3);
		buttonExit[Status::Pressed].SetPosition(buttonExit[Status::Default].GetXPos(), buttonExit[Status::Default].GetYPos());
		spriteListSelection.Insert(&buttonExit[Status::Pressed]);
	}
}

bool CUserInterface::OnLButtonUpSudoku(CPoint point, CSudoku& sudoku)
{
	RemoveSprites();

	int column = GetCellIndex(point.x, offset.x, tileSize.x, blockSpacing.x);
	int row = GetCellIndex(point.y, offset.y, tileSize.y, blockSpacing.y);

	if (column >= 0 && row >= 0)
	{
		int x = offset.x + column * tileSize.x + (column / 3) * blockSpacing.x + blockSpacing.x;
		int y = offset.y;
		selectDimension[0].SetPosition(x, y);

		x = offset.x;
		y = offset.y + row * tileSize.y + (row / 3) * blockSpacing.y + blockSpacing.y;
		selectDimension[1].SetPosition(x, y);

		x = column * tileSize.x + offset.x + (column / 3) * blockSpacing.x + blockSpacing.x;
		y = row * tileSize.y + offset.y + (row / 3) * blockSpacing.y + blockSpacing.y;
		selectFrame.SetPosition(x, y);
	}

	if (point.x >= buttonExit[Status::Default].GetXPos() &&
		point.x <= exitButtonSize.x + buttonExit[Status::Default].GetXPos() &&
		point.y >= buttonExit[Status::Default].GetYPos() &&
		point.y <= exitButtonSize.y + buttonExit[Status::Default].GetYPos())
	{
		exit(1);
		return false;
	}

	if (point.x >= buttonBack[Status::Default].GetXPos() &&
		point.x <= backButtonSize.x + buttonBack[Status::Default].GetXPos() &&
		point.y >= buttonBack[Status::Default].GetYPos() &&
		point.y <= backButtonSize.y + buttonBack[Status::Default].GetYPos())
	{
		return false;
	}

	return true;
}

void CUserInterface::OnLButtonDownSudoku(CPoint point)
{
	if (point.x >= buttonExit[Status::Default].GetXPos() &&
		point.x <= exitButtonSize.x + buttonExit[Status::Default].GetXPos() &&
		point.y >= buttonExit[Status::Default].GetYPos() &&
		point.y <= exitButtonSize.y + buttonExit[Status::Default].GetYPos())
	{
		buttonExit[Status::Pressed].SetZ(3);
		buttonExit[Status::Pressed].SetPosition(buttonExit[Status::Default].GetXPos(), buttonExit[Status::Default].GetYPos());
		spriteListSudoku.Insert(&buttonExit[Status::Pressed]);
	}

	if (point.x >= buttonBack[Status::Default].GetXPos() &&
		point.x <= backButtonSize.x + buttonBack[Status::Default].GetXPos() &&
		point.y >= buttonBack[Status::Default].GetYPos() &&
		point.y <= backButtonSize.y + buttonBack[Status::Default].GetYPos())
	{
		buttonBack[Status::Pressed].SetZ(3);
		buttonBack[Status::Pressed].SetPosition(buttonBack[Status::Default].GetXPos(), buttonBack[Status::Default].GetYPos());
		spriteListSudoku.Insert(&buttonBack[Status::Pressed]);
	}
}

CDIB& CUserInterface::GetBuffer()
{
	return buffer;
}

CSpriteList& CUserInterface::GetSpriteListSudoku()
{
	return spriteListSudoku;
}

CSpriteList& CUserInterface::GetSpriteListSelection()
{
	return spriteListSelection;
}

CSprite& CUserInterface::GetSelectFrame()
{
	return selectFrame;
}

CSprite* CUserInterface::GetSelectDimension()
{
	return selectDimension;
}

CSprite* CUserInterface::GetButtonExit()
{
	return buttonExit;
}

int CUserInterface::GetCellIndex(int position, int offset, int tileSize, int blockSpacing)
{
	int adjusted = position - offset;
	for (int i = 0; i < 9; i++)
	{
		int blockOffset = (i / 3) * blockSpacing;
		int start = i * tileSize + blockOffset;
		int end = start + tileSize;
		if (adjusted >= start && adjusted < end)
		{
			return i;
		}
	}
	return -1;
}

void CUserInterface::RemoveSprites()
{
	spriteListSelection.Remove(&buttonEasy[Status::Pressed]);
	spriteListSelection.Remove(&buttonMedium[Status::Pressed]);
	spriteListSelection.Remove(&buttonHard[Status::Pressed]);
	spriteListSelection.Remove(&buttonExpert[Status::Pressed]);
	spriteListSelection.Remove(&buttonGod[Status::Pressed]);
	spriteListSelection.Remove(&buttonExit[Status::Pressed]);

	spriteListSudoku.Remove(&buttonExit[Status::Pressed]);
	spriteListSudoku.Remove(&buttonReset[Status::Pressed]);
	spriteListSudoku.Remove(&buttonBack[Status::Pressed]);
	spriteListSudoku.Remove(&buttonUndo[Status::Pressed]);
	spriteListSudoku.Remove(&buttonSolve[Status::Pressed]);
	spriteListSudoku.Remove(&buttonCheck[Status::Pressed]);
}

void CUserInterface::SetCell(CVec2& position, int number)
{
	CSprite* numberSprite = LoadSpriteNumber(number);
	CSprite* currentSprite = GetSprite(position);
	if (currentSprite != nullptr)
	{
		spriteListSudoku.Remove(currentSprite);
	}
	numberSprite->SetPosition(position.x, position.y);
}

CSprite* CUserInterface::LoadSpriteNumber(int number)
{
	std::string path("./SudokuNumberPixel" + std::to_string(number) + ".bmp");
	std::vector<char> vPath(path.begin(), path.end());
	vPath.push_back('\0');

	CSprite* numberSprite = new CSprite();
	if (!numberSprite->Load(vPath.data(), CSize(32, 32)))
	{
		delete numberSprite;
	}
	numberSprite->SetZ(20);
	numberSprite->SetPosition(-1000, -1000);
	spriteListSudoku.Insert(numberSprite);
	return numberSprite;
}

CSprite* CUserInterface::GetSprite(CVec2& position)
{
	// ....
	return nullptr;
}

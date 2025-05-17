#include "pch.h"
#include "CUserInterface.h"
#include "SudokuPixelMFCDlg.h"


bool CUserInterface::OnInitSpritesSudoku(CSudoku& sudoku)
{
	if (!buffer.Load("./Sprites/SudokuGridPixelWhite.bmp"))
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
				int x = j * tileSize.x + offset.x + (j / 3) * blockSpace.x + tileSize.x - numberSize.x - 2;
				int y = i * tileSize.y + offset.y + (i / 3) * blockSpace.y + tileSize.y - numberSize.y - 2;
				CVec2 position{ x, y };
				SetCell(position, sudoku.GetCurrentNumber(i, j));
			}
		}
	}

	if (!selectFrame.Load("./Sprites/SudokuFieldSelect.bmp"))
	{
		AfxMessageBox(L"SudokuFieldSelect.bmp load error");
		return false;
	}
	selectFrame.SetZ(0);
	selectFrame.SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectFrame);

	if (!selectDimension[0].Load("./Sprites/SudokuGridColumnSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridColumnSelect.bmp load error");
		return false;
	}
	selectDimension[0].SetZ(0);
	selectDimension[0].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[0]);

	if (!selectDimension[1].Load("./Sprites/SudokuGridRowSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridRowSelect.bmp load error");
		return false;
	}
	selectDimension[1].SetZ(0);
	selectDimension[1].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[1]);

	if (!frame.Load("./Sprites/SudokuGrid423x423.bmp"))
	{
		AfxMessageBox(L"SudokuGrid423x423.bmp load error");
		return false;
	}
	frame.SetZ(0);
	frame.SetPosition(offset.x, offset.y);
	spriteListSudoku.Insert(&frame);

	if (!LoadSpriteButton("ButtonBackIcon", buttonBack, iconButtonSize, spriteListSudoku, buttonRowSecond.x + resetButtonSize.x + solveButtonSize.x + blockSpace.x * 2, buttonRowSecond.y) ||
		!LoadSpriteButton("ButtonUndo", buttonUndo, undoButtonSize, spriteListSudoku, buttonRowFirst.x, buttonRowFirst.y) ||
		!LoadSpriteButton("ButtonReset", buttonReset, resetButtonSize, spriteListSudoku, buttonRowSecond.x, buttonRowSecond.y) ||
		!LoadSpriteButton("ButtonCheck", buttonCheck, checkButtonSize, spriteListSudoku, buttonRowFirst.x + undoButtonSize.x + blockSpace.x, buttonRowFirst.y) ||
		!LoadSpriteButton("ButtonSolve", buttonSolve, solveButtonSize, spriteListSudoku, buttonRowSecond.x + resetButtonSize.x + blockSpace.x, buttonRowSecond.y) ||
		!LoadSpriteButton("ButtonSave", buttonSave, saveButtonSize, spriteListSudoku, buttonRowFirst.x + undoButtonSize.x + checkButtonSize.x + blockSpace.x * 2, buttonRowFirst.y)  ||
		!LoadSpriteButton("ButtonExitIcon", buttonExit, iconButtonSize, spriteListSudoku, buttonRowSecond.x + resetButtonSize.x + solveButtonSize.x + iconButtonSize.x + blockSpace.x * 3, buttonRowSecond.y))
	{
		return false;
	}

	return true;
}

bool CUserInterface::OnInitSpritesSelection()
{
	if (!buffer.Load("./Sprites/SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuBackground.bmp load error");
		return false;
	}
	spriteListSelection.SetWorkspace(&buffer);
	
	if (!LoadSpriteButton("ButtonEasy", buttonEasy, easyButtonSize, spriteListSelection, selectionSize.x / 2 - easyButtonSize.x / 2, buttonSelectRow.y) ||
		!LoadSpriteButton("ButtonMedium", buttonMedium, mediumButtonSize, spriteListSelection, selectionSize.x / 2 - mediumButtonSize.x / 2, buttonSelectRow.y + buttonSpace.y * 1) ||
		!LoadSpriteButton("ButtonHard", buttonHard, hardButtonSize, spriteListSelection, selectionSize.x / 2 - hardButtonSize.x / 2, buttonSelectRow.y + buttonSpace.y * 2) ||
		!LoadSpriteButton("ButtonExpert", buttonExpert, expertButtonSize, spriteListSelection, selectionSize.x / 2 - expertButtonSize.x / 2, buttonSelectRow.y + buttonSpace.y * 3) ||
		!LoadSpriteButton("ButtonGod", buttonGod, godButtonSize, spriteListSelection, selectionSize.x / 2 - godButtonSize.x / 2, buttonSelectRow.y + buttonSpace.y * 4) ||
		!LoadSpriteButton("ButtonExit", buttonExit, exitButtonSize, spriteListSelection, selectionSize.x / 2 - exitButtonSize.x / 2, buttonSelectRow.y + buttonSpace.y * 5.5))
	{
		return false;
	}

	if (!buttonGithub.Load("./Sprites/githubIcon.bmp"))
	{
		AfxMessageBox(L"githubIcon.bmp load error");
		return false;
	}
	buttonGithub.SetZ(0);
	buttonGithub.SetPosition(280, 380);
	spriteListSelection.Insert(&buttonGithub);

	return true;
}

bool CUserInterface::LoadSpriteButton(std::string name, CSprite sprite[], CVec2 spriteSize, CSpriteList& spriteList, int x, int y)
{
	std::string p = "./Sprites/" + name + ".bmp";
	std::vector<char> path(p.begin(), p.end()); //Load() hat kein overload für const char* --> konvertiert zu char*
	path.push_back('\0');

	if (!sprite[Status::Default].Load(path.data()))
	{
		AfxMessageBox(L"load error!");
		return false;
	}
	sprite[Status::Default].SetZ(0);
	sprite[Status::Default].SetPosition(x, y);
	spriteList.Insert(&sprite[Status::Default]);

	p = "./Sprites/" + name + "Pressed.bmp";
	std::vector<char>vPath(p.begin(), p.end());
	vPath.push_back('\0');

	if (!sprite[Status::Pressed].Load(vPath.data(), CSize(spriteSize.x, spriteSize.y), false))
	{
		AfxMessageBox(L"load error");
		return false;
	}

	return true;
}

bool CUserInterface::OnLButtonUpSelection(CPoint point, CSudoku& sudoku)
{
	RemoveSprites();

	if (CheckButtonUp(point, buttonEasy, easyButtonSize))
	{
		sudoku.SetFilePath("./Sudoku Loadouts/sudoku1.txt");
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

	if (CheckButtonUp(point, buttonMedium, mediumButtonSize))
	{
		sudoku.SetFilePath("./Sudoku Loadouts/sudoku2.txt");
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

	if (CheckButtonUp(point, buttonHard, hardButtonSize))
	{
		sudoku.SetFilePath("./Sudoku Loadouts/sudoku3.txt");
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

	if (CheckButtonUp(point, buttonExpert, expertButtonSize))
	{
		sudoku.SetFilePath("./Sudoku Loadouts/sudoku4.txt");
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

	if (CheckButtonUp(point, buttonGod, godButtonSize))
	{
		sudoku.SetFilePath("./Sudoku Loadouts/sudoku5.txt");
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

	if (CheckButtonUp(point, buttonExit, exitButtonSize))
	{
		exit(0);
	}

	if (point.x >= buttonGithub.GetXPos() &&
		point.x <= githubIconSize.x + buttonGithub.GetXPos() &&
		point.y >= buttonGithub.GetYPos() &&
		point.y <= githubIconSize.y + buttonGithub.GetYPos())
	{
		ShellExecute(0, 0, L"https://github.com/rookie10004", 0, 0, SW_SHOW);
	}

	return false;
}

void CUserInterface::OnLButtonDownSelection(CPoint point)
{
	ButtonDownAnimation(point, buttonEasy, spriteListSelection, easyButtonSize);
	ButtonDownAnimation(point, buttonMedium, spriteListSelection, mediumButtonSize);
	ButtonDownAnimation(point, buttonHard, spriteListSelection, hardButtonSize);
	ButtonDownAnimation(point, buttonExpert, spriteListSelection, expertButtonSize);
	ButtonDownAnimation(point, buttonGod, spriteListSelection, godButtonSize);
	ButtonDownAnimation(point, buttonExit, spriteListSelection, exitButtonSize);
}

bool CUserInterface::OnLButtonUpSudoku(CPoint point, CSudoku& sudoku)
{
	RemoveSprites();

	int column = GetCellIndex(point.x, offset.x, tileSize.x, blockSpace.x);
	int row = GetCellIndex(point.y, offset.y, tileSize.y, blockSpace.y);

	if (column >= 0 && row >= 0)
	{
		int x = offset.x + column * tileSize.x + (column / 3) * blockSpace.x + blockSpace.x;
		int y = offset.y;
		selectDimension[0].SetPosition(x, y);

		x = offset.x;
		y = offset.y + row * tileSize.y + (row / 3) * blockSpace.y + blockSpace.y;
		selectDimension[1].SetPosition(x, y);

		x = column * tileSize.x + offset.x + (column / 3) * blockSpace.x + blockSpace.x;
		y = row * tileSize.y + offset.y + (row / 3) * blockSpace.y + blockSpace.y;
		selectFrame.SetPosition(x, y);
	}

	if (CheckButtonUp(point, buttonReset, resetButtonSize))
	{
		sudoku.LoadNewGame();
		// ???
	}

	// logik der anderen Button

	if (CheckButtonUp(point, buttonExit, iconButtonSize))
	{
		exit(1);
	}

	if (CheckButtonUp(point, buttonBack, iconButtonSize))
	{
		return false;
	}

	return true;
}

void CUserInterface::OnLButtonDownSudoku(CPoint point)
{
	ButtonDownAnimation(point, buttonSolve, spriteListSudoku, solveButtonSize);
	ButtonDownAnimation(point, buttonCheck, spriteListSudoku, checkButtonSize);
	ButtonDownAnimation(point, buttonUndo, spriteListSudoku, undoButtonSize);
	ButtonDownAnimation(point, buttonReset, spriteListSudoku, resetButtonSize);
	ButtonDownAnimation(point, buttonSave, spriteListSudoku, saveButtonSize);
	ButtonDownAnimation(point, buttonExit, spriteListSudoku, iconButtonSize);
	ButtonDownAnimation(point, buttonBack, spriteListSudoku, iconButtonSize);
}

void CUserInterface::ButtonDownAnimation(CPoint point, CSprite sprite[], CSpriteList& spriteList, CVec2 spriteSize)
{
	if (point.x >= sprite[Status::Default].GetXPos() &&
		point.x <= spriteSize.x + sprite[Status::Default].GetXPos() &&
		point.y >= sprite[Status::Default].GetYPos() &&
		point.y <= spriteSize.y + sprite[Status::Default].GetYPos())
	{
		sprite[Status::Pressed].SetZ(5);
		sprite[Status::Pressed].SetPosition(sprite[Status::Default].GetXPos(), sprite[Status::Default].GetYPos());
		spriteList.Insert(&sprite[Status::Pressed]);
	}
}

bool CUserInterface::CheckButtonUp(CPoint point, CSprite sprite[], CVec2 spriteSize)
{
	if (point.x >= sprite[Status::Default].GetXPos() &&
		point.x <= spriteSize.x + sprite[Status::Default].GetXPos() &&
		point.y >= sprite	[Status::Default].GetYPos() &&
		point.y <= spriteSize.y + sprite[Status::Default].GetYPos())
	{
		return true;
	}

	return false;
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

int CUserInterface::GetCellIndex(int position, int offset, int tileSize, int blockSpace)
{
	int adjusted = position - offset;
	for (int i = 0; i < 9; i++)
	{
		int blockOffset = (i / 3) * blockSpace;
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
	spriteListSudoku.Remove(&buttonSave[Status::Pressed]);
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
	std::string path("./Sprites/SudokuNumberPixel" + std::to_string(number) + ".bmp");
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

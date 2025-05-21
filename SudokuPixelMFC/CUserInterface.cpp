#include "pch.h"
#include "CUserInterface.h"
#include "SudokuPixelMFCDlg.h"


CUserInterface::CUserInterface()
{
}

bool CUserInterface::OnInitSpritesSudoku(CSudoku& sudoku)
{
	if (!buffer.Load("./Sprites/SudokuGridPixelWhite.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuGridPixelWhite.bmp");
		return false;
	}
	spriteListSudoku.SetWorkspace(&buffer);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int x = j * tileSize.x + offset.x + (j / 3) * blockSpace.x + tileSize.x - numberSize.x - 2;
			int y = i * tileSize.y + offset.y + (i / 3) * blockSpace.y + tileSize.y - numberSize.y - 2;
			CVec2 position{ x, y };
			SetCell(position, sudoku.GetCurrentNumber(i, j), sudoku);
		}
	}

	if (!selectFrame.Load("./Sprites/SudokuFieldSelect.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuFieldSelect.bmp");
		return false;
	}
	selectFrame.SetZ(0);
	selectFrame.SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectFrame);

	if (!selectDimension[0].Load("./Sprites/SudokuGridColumnSelect.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuGridColumnSelect.bmp");
		return false;
	}
	selectDimension[0].SetZ(0);
	selectDimension[0].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[0]);

	if (!selectDimension[1].Load("./Sprites/SudokuGridRowSelect.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuGridRowSelect.bmp");
		return false;
	}
	selectDimension[1].SetZ(0);
	selectDimension[1].SetPosition(-1000, -1000);
	spriteListSudoku.Insert(&selectDimension[1]);

	if (!frame.Load("./Sprites/SudokuGrid423x423.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuGrid423x423.bmp");
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

	if (!buttonCheck[2].Load("./Sprites/ButtonCheckTrue.bmp") || !buttonCheck[3].Load("./Sprites/ButtonCheckFalse.bmp"))
	{
		throw SpriteException("Error loading sprite:ButtonCheckTrue.bmp or ButtonCheckFalse.bmp");
	}

	return true;
}

bool CUserInterface::OnInitSpritesSelection()
{
	if (!buffer.Load("./Sprites/SudokuGridPixelWhite.bmp"))
	{
		throw SpriteException("Error loading sprite:SudokuGridPixelWhite.bmp");
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
		throw SpriteException("Error loading sprite:githubIcon.bmp");
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
		throw SpriteException("Error loading sprite:" + p);
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
		throw SpriteException("Error loading sprite:" + p);
		return false;
	}

	return true;
}

bool CUserInterface::OnLButtonUpSelection(CPoint point, CSudoku& sudoku)
{
	RemoveSprites();

	if (CheckButtonUp(point, buttonEasy, easyButtonSize))
	{
		LoadFile("./Sudoku Loadouts/sudoku1.txt", sudoku);
		return true;
	}

	if (CheckButtonUp(point, buttonMedium, mediumButtonSize))
	{
		LoadFile("./Sudoku Loadouts/sudoku2.txt", sudoku);
		return true;
	}

	if (CheckButtonUp(point, buttonHard, hardButtonSize))
	{
		LoadFile("./Sudoku Loadouts/sudoku3.txt", sudoku);
		return true;
	}

	if (CheckButtonUp(point, buttonExpert, expertButtonSize))
	{
		LoadFile("./Sudoku Loadouts/sudoku4.txt", sudoku);
		return true;
	}

	if (CheckButtonUp(point, buttonGod, godButtonSize))
	{
		LoadFile("./Sudoku Loadouts/sudoku5.txt", sudoku);
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
		try
		{
			openURL("https://github.com/rookie10004/SudokuPixelMFC");
		}
		catch (const std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONHAND);
		}
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

bool CUserInterface::OnLButtonUpSudoku(CPoint point, CSudoku& sudoku, CUndo& undo, CSolve& solve)
{
	RemoveSprites();

	if (point.x >= offset.x && point.x <= offset.x + gridSize.x && point.y >= offset.y && point.y <= offset.y + gridSize.y)
	{
		currentCell = GetCellIndex(CVec2(point.x, point.y));
	}

	if (currentCell != CVec2(-1, -1))
	{
		CVec2 position(offset.x + currentCell.x * tileSize.x + (currentCell.x / 3) * blockSpace.x + blockSpace.x, offset.y);
		selectDimension[0].SetPosition(position);

		position.x = offset.x;
		position.y = offset.y + currentCell.y * tileSize.y + (currentCell.y / 3) * blockSpace.y + blockSpace.y;
		selectDimension[1].SetPosition(position);

		position = currentCell * tileSize + offset + (currentCell / 3) * blockSpace + blockSpace;
		selectFrame.SetPosition(position);
	}

	if (CheckButtonUp(point, buttonReset, resetButtonSize))
	{
		sudoku.LoadNewGame();
		RemoveNumbers();

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (sudoku.GetCurrentNumber(i, j) != 0)
				{
					int x = j * tileSize.x + offset.x + (j / 3) * blockSpace.x + tileSize.x - numberSize.x - 2;
					int y = i * tileSize.y + offset.y + (i / 3) * blockSpace.y + tileSize.y - numberSize.y - 2;
					CVec2 position{ x, y };
					SetCell(position, sudoku.GetCurrentNumber(i, j), sudoku);
				}
			}
		}
	}

	if (CheckButtonUp(point, buttonSave, saveButtonSize))
	{
		sudoku.StoreSavegame();
	}

	if (CheckButtonUp(point, buttonUndo, undoButtonSize))
	{
		if (!undo.isEmpty())
		{
			spriteListSudoku.Remove(spriteArray[undo.GetStack().column][undo.GetStack().row].sprite);
			SetCell(spriteArray[undo.GetStack().column][undo.GetStack().row].position, undo.GetStack().number, sudoku);
			undo.Undo(sudoku);
		}
	}

	if (CheckButtonUp(point, buttonCheck, checkButtonSize) && buttonEnabled)
	{
		if (solve.Check(sudoku))
		{
			buttonCheck[2].SetZ(5);
			buttonCheck[2].SetPosition(buttonCheck[Status::Default].GetXPos(), buttonCheck[Status::Default].GetYPos());
			spriteListSudoku.Insert(&buttonCheck[2]);
		}
		else
		{
			buttonCheck[3].SetZ(5);
			buttonCheck[3].SetPosition(buttonCheck[Status::Default].GetXPos(), buttonCheck[Status::Default].GetYPos());
			spriteListSudoku.Insert(&buttonCheck[3]);
		}
		buttonEnabled = false;
	}

	if (CheckButtonUp(point, buttonSolve, solveButtonSize))
	{
		sudoku.LoadNewGame();
		RemoveNumbers();
		solve.Automatically(sudoku);
		undo.ClearStack();

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (sudoku.GetCurrentNumber(i, j) != 0)
				{
					int x = j * tileSize.x + offset.x + (j / 3) * blockSpace.x + tileSize.x - numberSize.x - 2;
					int y = i * tileSize.y + offset.y + (i / 3) * blockSpace.y + tileSize.y - numberSize.y - 2;
					CVec2 position{ x, y };
					SetCell(position, sudoku.GetCurrentNumber(i, j), sudoku);
				}
			}
		}
	}

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

void CUserInterface::OnChar(UINT nChar, CSudoku& sudoku, CUndo& undo)
{
	if (sudoku.GetOriginalNumber(currentCell) == 0 && selectFrame.GetPos() != CPoint(-1000, -1000))
	{
		if (nChar >= '1' && nChar <= '9')
		{
			SetCell(CVec2(selectFrame.GetXPos() + 8, selectFrame.GetYPos() + 8), nChar - '0', sudoku);
			undo.StoreInStack(sudoku.GetCurrentNumber(currentCell.y, currentCell.x), currentCell.y, currentCell.x);
			sudoku.SetCurrentNumber(nChar - '0', currentCell.y, currentCell.x);
		}
	}

	if (selectFrame.GetPos() != CPoint(-1000, -1000))
	{
		switch (nChar)
		{
		case 'w':
		case 'W':
			if (currentCell.y > 0)
			{
				currentCell.y--;
				selectFrame.SetPosition(currentCell * tileSize + offset + (currentCell / 3) * blockSpace + blockSpace);
				selectDimension[1].SetPosition(offset.x, offset.y + currentCell.y * tileSize.y + (currentCell.y / 3) * blockSpace.y + blockSpace.y);
			}
			break;

		case 'a':
		case 'A':
			if (currentCell.x > 0)
			{
				currentCell.x--;
				selectFrame.SetPosition(currentCell * tileSize + offset + (currentCell / 3) * blockSpace + blockSpace);
				selectDimension[0].SetPosition(offset.x + currentCell.x * tileSize.x + (currentCell.x / 3) * blockSpace.x + blockSpace.x, offset.y);
			}
			break;

		case 's':
		case 'S':
			if (currentCell.y < 8)
			{
				currentCell.y++;
				selectFrame.SetPosition(currentCell * tileSize + offset + (currentCell / 3) * blockSpace + blockSpace);
				selectDimension[1].SetPosition(offset.x, offset.y + currentCell.y * tileSize.y + (currentCell.y / 3) * blockSpace.y + blockSpace.y);
			}
			break;

		case 'd':
		case 'D':
			if (currentCell.x < 8)
			{
				currentCell.x++;
				selectFrame.SetPosition(currentCell * tileSize + offset + (currentCell / 3) * blockSpace + blockSpace);
				selectDimension[0].SetPosition(offset.x + currentCell.x * tileSize.x + (currentCell.x / 3) * blockSpace.x + blockSpace.x, offset.y);
			}
			break;

		default:
			break;
		}
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

CVec2 CUserInterface::GetCellIndex(CVec2& position)
{
	CVec2 adjusted = position - offset;

	for (int i = 0; i < 9; i++)
	{
		int blockOffset = (i / 3) * blockSpace.x;
		int start = i * tileSize.x + blockOffset;
		int end = start + tileSize.x;

		if (adjusted.x >= start && adjusted.x < end)
		{
			for (int j = 0; j < 9; j++)
			{
				int blockOffsetY = (j / 3) * blockSpace.y;
				int startY = j * tileSize.y + blockOffsetY;
				int endY = startY + tileSize.y;

				if (adjusted.y >= startY && adjusted.y < endY)
				{
					return CVec2(i, j);
				}
			}
		}
	}

	return CVec2(-1, -1);
}

void CUserInterface::LoadFile(std::string filePath, CSudoku& sudoku)
{
	try
	{
		sudoku.SetFilePath(filePath);
		if (sudoku.CheckSavegame())
		{
			sudoku.LoadOldGame();
		}
		else
		{
			sudoku.LoadNewGame();
		}
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
}

void CUserInterface::openURL(const std::string& url)
{
#if defined(_WIN32) || defined(_WIN64)

	std::wstring wURL(url.begin(), url.end());
	ShellExecute(0, 0, wURL.c_str(), 0, 0, SW_SHOW);

#elif defined(__APPLE__)

	std::string command = "open " + url;
	system(command.c_str());

#elif defined(__linux__)

	std::string command = "xdg-open " + url;
	system(command.c_str());

#else
	throw OSException("Operating system is not fully supported");
#endif
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

void CUserInterface::RemoveNumbers()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			spriteListSudoku.Remove(spriteArray[i][j].sprite);
			spriteArray[i][j] = SpriteArray();
		}
	}
}

void CUserInterface::ButtonCheckRemove()
{
	spriteListSudoku.Remove(&buttonCheck[2]);
	spriteListSudoku.Remove(&buttonCheck[3]);
	buttonEnabled = true;
}

void CUserInterface::SetCell(CVec2& position, int number, CSudoku& sudoku)
{
	if (number == 0)
	{
		return;
	}

	CSprite* numberSprite;

	if (sudoku.GetOriginalNumber(GetCellIndex(position).y, GetCellIndex(position).x) != 0)
	{
		numberSprite = LoadSpriteNumber(position, number);
	}
	else
	{
		numberSprite = LoadSpriteNumber(position, number, 0.65f);
	}

	CSprite* currentSprite = GetSprite(position);
	if (currentSprite != nullptr)
	{
		spriteListSudoku.Remove(currentSprite);
	}
	spriteArray[GetCellIndex(position).x][GetCellIndex(position).y] = SpriteArray(numberSprite, number, position);
}

CSprite* CUserInterface::LoadSpriteNumber(CVec2& position, int number, float alpha)
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
	numberSprite->SetPosition(position.x, position.y);
	numberSprite->SetAlpha(alpha);
	spriteListSudoku.Insert(numberSprite);

	return numberSprite;
}

CSprite* CUserInterface::GetSprite(CVec2& position)
{
	return spriteArray[GetCellIndex(position).x][GetCellIndex(position).y].sprite;
}

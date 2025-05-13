#include "pch.h"
#include "CUserInterface.h"
#include "SudokuPixelMFCDlg.h"


bool CUserInterface::OnInitSpritesSudoku()
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuGridPixelWhite.bmp load error");
		return false;
	}
	spriteListSudoku.SetWorkspace(&buffer);

	for (int i = 0; i < 10; i++)
	{
		std::string path("./SudokuNumberPixel" + std::to_string(i) + ".bmp");
		std::vector<char> vPath(path.begin(), path.end());
		vPath.push_back('\0');
		if (!number[i].Load(vPath.data(), CSize(32, 32), TRUE))
		{
			std::wstring pathEr(L"SudokuNumberPixel" + std::to_wstring(i) + L".bmp load error");
			AfxMessageBox(pathEr.data());
			return false;
		}
		number[i].SetZ(20);
		number[i].SetPosition((i - 1) * tileSize.x + offset.x + blockSpacing.x + 10, offset.y + blockSpacing.y + 10);
	}
	for (int i = 0; i < 10; i++)
	{
		spriteListSudoku.Insert(&number[i]);
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

	if (!buttonExit[Status::Default].Load("./ButtonExit.bmp"))
	{
		AfxMessageBox(L"ButtonExit.bmp load error");
		return false;
	}
	buttonExit[Status::Default].SetZ(0);
	buttonExit[Status::Default].SetPosition(offset.x + gridSize.x - exitButtonSize.x, buttonRowSecond.y);
	spriteListSudoku.Insert(&buttonExit[Status::Default]);

	if (!buttonExit[Status::Pressed].Load("./ButtonExitPressed.bmp", CSize(128, 52), false))
	{
		AfxMessageBox(L"ButtonExitPressed.bmp load error");
		return false;
	}

	if (!buttonBack[Status::Default].Load("./ButtonBack.bmp"))
	{
		AfxMessageBox(L"ButtonBack.bmp load error");
		return false;
	}
	buttonBack[Status::Default].SetZ(0);
	buttonBack[Status::Default].SetPosition(offset.x + gridSize.x - backButtonSize.x, buttonRowFirst.y);
	spriteListSudoku.Insert(&buttonBack[Status::Default]);

	if (!buttonBack[Status::Pressed].Load("./ButtonBackPressed.bmp", CSize(128, 52), false))
	{
		AfxMessageBox(L"ButtonBackPressed.bmp load error");
		return false;
	}

	return true;
}

bool CUserInterface::OnInitSpritesSelection()
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuGridPixelWhite.bmp load error");
		return false;
	}
	spriteListSelection.SetWorkspace(&buffer);

	if (!buttonExit[Status::Default].Load("./ButtonExit.bmp"))
	{
		AfxMessageBox(L"ButtonExit.bmp load error");
		return false;
	}
	buttonExit[Status::Default].SetZ(0);
	buttonExit[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 5.5);
	spriteListSelection.Insert(&buttonExit[Status::Default]);

	if (!buttonExit[Status::Pressed].Load("./ButtonExitPressed.bmp", CSize(128, 52), false))
	{
		AfxMessageBox(L"ButtonExitPressed.bmp load error");
		return false;
	}

	if (!buttonEasy[Status::Default].Load("./ButtonEasy.bmp"))
	{
		AfxMessageBox(L"ButtonEasy.bmp load error");
		return false;
	}
	buttonEasy[Status::Default].SetZ(0);
	buttonEasy[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y);
	spriteListSelection.Insert(&buttonEasy[Status::Default]);

	if (!buttonEasy[Status::Pressed].Load("./ButtonEasyPressed.bmp", CSize(136, 52), false))
	{
		AfxMessageBox(L"ButtonEasyPressed.bmp load error");
		return false;
	}

	if (!buttonMedium[Status::Default].Load("./ButtonMedium.bmp"))
	{
		AfxMessageBox(L"ButtonMedium.bmp load error");
		return false;
	}
	buttonMedium[Status::Default].SetZ(0);
	buttonMedium[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 1);
	spriteListSelection.Insert(&buttonMedium[Status::Default]);

	if (!buttonMedium[Status::Pressed].Load("./ButtonMediumPressed.bmp", CSize(204, 52), false))
	{
		AfxMessageBox(L"ButtonMediumPressed.bmp load error");
		return false;
	}

	if (!buttonHard[Status::Default].Load("./ButtonHard.bmp"))
	{
		AfxMessageBox(L"ButtonHard.bmp load error");
		return false;
	}
	buttonHard[Status::Default].SetZ(0);
	buttonHard[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 2);
	spriteListSelection.Insert(&buttonHard[Status::Default]);

	if (!buttonHard[Status::Pressed].Load("./ButtonHardPressed.bmp", CSize(140, 52), false))
	{
		AfxMessageBox(L"ButtonHardPressed.bmp load error");
		return false;
	}

	if (!buttonExpert[Status::Default].Load("./ButtonExpert.bmp"))
	{
		AfxMessageBox(L"ButtonExpert.bmp load error");
		return false;
	}
	buttonExpert[Status::Default].SetZ(0);
	buttonExpert[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 3);
	spriteListSelection.Insert(&buttonExpert[Status::Default]);

	if (!buttonExpert[Status::Pressed].Load("./ButtonExpertPressed.bmp", CSize(192, 52), false))
	{
		AfxMessageBox(L"ButtonExpertPressed.bmp load error");
		return false;
	}

	if (!buttonGod[Status::Default].Load("./ButtonGod.bmp"))
	{
		AfxMessageBox(L"ButtonGod.bmp load error");
		return false;
	}
	buttonGod[Status::Default].SetZ(0);
	buttonGod[Status::Default].SetPosition(buttonSelectRow.x, buttonSelectRow.y + buttonSpace.y * 4);
	spriteListSelection.Insert(&buttonGod[Status::Default]);

	if (!buttonGod[Status::Pressed].Load("./ButtonGodPressed.bmp", CSize(116, 52), false))
	{
		AfxMessageBox(L"ButtonGodPressed.bmp load error");
		return false;
	}

	return true;
}

bool CUserInterface::OnLButtonUpSelection(CPoint point)
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
		static CSudoku sudoku("./sudoku1.txt");
		return true;
	}

	if (point.x >= buttonMedium[Status::Default].GetXPos() &&
		point.x <= mediumButtonSize.x + buttonMedium[Status::Default].GetXPos() &&
		point.y >= buttonMedium[Status::Default].GetYPos() &&
		point.y <= mediumButtonSize.y + buttonMedium[Status::Default].GetYPos())
	{
		static CSudoku sudoku("./sudoku2.txt");
		return true;
	}

	if (point.x >= buttonHard[Status::Default].GetXPos() &&
		point.x <= hardButtonSize.x + buttonHard[Status::Default].GetXPos() &&
		point.y >= buttonHard[Status::Default].GetYPos() &&
		point.y <= hardButtonSize.y + buttonHard[Status::Default].GetYPos())
	{
		static CSudoku sudoku("./sudoku3.txt");
		return true;
	}

	if (point.x >= buttonExpert[Status::Default].GetXPos() &&
		point.x <= expertButtonSize.x + buttonExpert[Status::Default].GetXPos() &&
		point.y >= buttonExpert[Status::Default].GetYPos() &&
		point.y <= expertButtonSize.y + buttonExpert[Status::Default].GetYPos())
	{
		static CSudoku sudoku("./sudoku4.txt");
		return true;
	}

	if (point.x >= buttonGod[Status::Default].GetXPos() &&
		point.x <= godButtonSize.x + buttonGod[Status::Default].GetXPos() &&
		point.y >= buttonGod[Status::Default].GetYPos() &&
		point.y <= godButtonSize.y + buttonGod[Status::Default].GetYPos())
	{
		static CSudoku sudoku("./sudoku5.txt");
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

bool CUserInterface::OnLButtonUpSudoku(CPoint point)
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

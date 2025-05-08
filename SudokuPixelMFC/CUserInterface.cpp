#include "pch.h"
#include "CUserInterface.h"


BOOL CUserInterface::OnInitSprites()
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuGridPixelWhite.bmp load error");
		return false;
	}
	spriteList.SetWorkspace(&buffer);

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
		number[i].SetPosition((i + 1.3) * 46, 30);
	}
	for (int i = 0; i < 10; i++)
	{
		spriteList.Insert(&number[i]);
	}

	if (!selectFrame.Load("./SudokuFieldSelect.bmp"))
	{
		AfxMessageBox(L"SudokuFieldSelect.bmp load error");
		return false;
	}
	selectFrame.SetZ(0);
	selectFrame.SetPosition(-1000, -1000);
	spriteList.Insert(&selectFrame);

	if (!selectDimension[0].Load("./SudokuGridColumnSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridColumnSelect.bmp load error");
		return false;
	}
	selectDimension[0].SetZ(0);
	selectDimension[0].SetPosition(-1000, -1000);
	spriteList.Insert(&selectDimension[0]);

	if (!selectDimension[1].Load("./SudokuGridRowSelect.bmp"))
	{
		AfxMessageBox(L"SudokuGridRowSelect.bmp load error");
		return false;
	}
	selectDimension[1].SetZ(0);
	selectDimension[1].SetPosition(-1000, -1000);
	spriteList.Insert(&selectDimension[1]);

	if (!frame.Load("./SudokuGrid423x423.bmp"))
	{
		AfxMessageBox(L"SudokuGrid423x423.bmp load error");
		return false;
	}
	frame.SetZ(0);
	frame.SetPosition(offsetX, offsetY);
	spriteList.Insert(&frame);

	if (!buttonExit[0].Load("./ButtonExit.bmp"))
	{
		AfxMessageBox(L"ButtonExit.bmp load error");
		return false;
	}
	buttonExit[0].SetZ(0);
	buttonExit[0].SetPosition(offsetX + gridSize - buttonExitY, buttonRow);
	spriteList.Insert(&buttonExit[Status::Default]);

	if (!buttonExit[1].Load("./ButtonExitPressed.bmp", CSize(124, 53), false))
	{
		AfxMessageBox(L"ButtonExitPressed.bmp load error");
		return false;
	}

	return true;
}

CDIB& CUserInterface::GetBuffer()
{
	return buffer;
}

CSpriteList& CUserInterface::GetSpriteList()
{
	return spriteList;
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
	spriteList.Remove(&buttonExit[1]);
}

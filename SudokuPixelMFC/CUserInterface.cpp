#include "pch.h"
#include "CUserInterface.h"


BOOL CUserInterface::OnInitSprites()
{
	if (!buffer.Load("./SudokuGridPixelWhite.bmp"))
	{
		AfxMessageBox(L"SudokuGridPixelWhite.bmp load error");
		return FALSE;
	}
	spriteList.SetWorkspace(&buffer);

	if (!frame.Load("./SudokuGridPixel.bmp"))
	{
		AfxMessageBox(L"SudokuGridPixel.bmp load error");
		return FALSE;
	}
	frame.SetZ(10);
	frame.SetPosition(42, 10);
	spriteList.Insert(&frame);

	for (int i = 0; i < 10; i++)
	{
		std::string path("./SudokuNumberPixel" + std::to_string(i) + ".bmp");
		std::vector<char> vPath(path.begin(), path.end());
		vPath.push_back('\0');
		if (!number[i].Load(vPath.data(), CSize(32, 32), TRUE))
		{
			std::wstring pathEr(L"SudokuNumberPixel" + std::to_wstring(i) + L".bmp load error");
			AfxMessageBox(pathEr.data());
			return FALSE;
		}
		number[i].SetZ(20);
		number[i].SetPosition((i + 1.3) * 46, 30);
	}
	for (int i = 0; i < 10; i++)
	{
		spriteList.Insert(&number[i]);
	}

	return TRUE;
}

CDIB& CUserInterface::GetBuffer()
{
	return buffer;
}

CSpriteList& CUserInterface::GetSpriteList()
{
	return spriteList;
}

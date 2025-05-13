#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "CVec2.h"
#include "CSudoku.h"

class CUserInterface
{
public:
	enum Status : int
	{
		Default,
		Pressed
	};

private:
	CDIB buffer;
	CSprite bkg;
	CSprite number[10];
	CSprite frame;
	CSprite selectFrame;
	CSprite selectDimension[2];
	CSpriteList spriteListSudoku;
	CSpriteList spriteListSelection;

	CSprite buttonEasy[2];
	CSprite buttonMedium[2];
	CSprite buttonHard[2];
	CSprite buttonExpert[2];
	CSprite buttonGod[2];

	CSprite buttonUndo[2];
	CSprite buttonReset[2];
	CSprite buttonSolve[2];
	CSprite buttonCheck[2];
	CSprite buttonBack[2];
	CSprite buttonExit[2];

	CVec2 offset{ 58, 10 };
	CVec2 blockSpacing{ 3, 3 };
	CVec2 gridSize{ 423, 423 };
	CVec2 tileSize{ 45, 45 };

	CVec2 buttonSelectRow{ 70, 25 };
	CVec2 buttonSpace{ 0, 60 }; //buttonSize mit eingerechnet

	CVec2 buttonRowFirst{ 0, 450 };
	CVec2 buttonRowSecond{ 0, 450 + buttonSpace.y };

	CVec2 easyButtonSize{ 136, 52 };
	CVec2 mediumButtonSize{ 204, 52 };
	CVec2 hardButtonSize{ 140, 52 };
	CVec2 expertButtonSize{ 192, 52 };
	CVec2 godButtonSize{ 116, 52 };
	CVec2 backButtonSize{ 136, 52 };
	CVec2 exitButtonSize{ 128, 52 };

public:
	bool OnInitSpritesSudoku(CSudoku& sudoku);

	bool OnInitSpritesSelection();

	bool OnLButtonUpSelection(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSelection(CPoint point);

	bool OnLButtonUpSudoku(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSudoku(CPoint point);

	CDIB& GetBuffer();

	CSpriteList& GetSpriteListSudoku();

	CSpriteList& GetSpriteListSelection();

	CSprite& GetSelectFrame();

	CSprite* GetSelectDimension();

	CSprite* GetButtonExit();

	int GetCellIndex(int position, int offset, int tileSize, int blockSpacing);

	void RemoveSprites();
};


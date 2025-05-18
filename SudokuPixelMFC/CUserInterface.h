#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "CSudoku.h"
#include "CVec2.h"
#include <cstdlib>

/*TODO:	
		- Undo/Reset/Check/Solve/Save Funktion
		- Code kommentieren
		- Startbildschirm mit Intro
		- Exceptions
		- Sound??*/ 

class CUserInterface
{
private:
	CVec2 selectionSize{ 344, 470 };
	CVec2 sudokuSize{  }; // fehlt noch

	enum Status : int
	{
		Default,
		Pressed
	};

	struct SpriteArray
	{
		SpriteArray() : sprite(nullptr), number(0), position(0, 0) { }
		SpriteArray(CSprite* sprite, int number, CVec2 position) : sprite(sprite), number(number), position(position) { }

		CSprite* sprite;
		int number;
		CVec2 position;
	};

	SpriteArray spriteArray[9][9];

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
	CSprite buttonSave[2];
	CSprite buttonBack[2];
	CSprite buttonExit[2];
	CSprite buttonGithub;

	CVec2 offset{ 58, 10 };
	CVec2 gridSize{ 423, 423 };
	CVec2 tileSize{ 45, 45 };
	CVec2 numberSize{ 32, 32 };

	CVec2 blockSpace{ 3, 3 };
	CVec2 buttonSpace{ 0, 52 + 8 }; //buttonSize(52) mit eingerechnet

	CVec2 buttonSelectRow{ 70, 25 };
	CVec2 buttonRowFirst{ 52, 445 };
	CVec2 buttonRowSecond{ 48, buttonRowFirst.y + buttonSpace.y };

	CVec2 easyButtonSize{ 136, 52 };
	CVec2 mediumButtonSize{ 204, 52 };
	CVec2 hardButtonSize{ 140, 52 };
	CVec2 expertButtonSize{ 192, 52 };
	CVec2 godButtonSize{ 116, 52 };
	CVec2 exitButtonSize{ 128, 52 };
	CVec2 undoButtonSize{ 140, 52 };
	CVec2 saveButtonSize{ 136, 52 };
	CVec2 solveButtonSize{ 160, 52 };
	CVec2 checkButtonSize{ 164, 52 };
	CVec2 resetButtonSize{ 164, 52 };
	CVec2 iconButtonSize{ 60, 52 };
	CVec2 githubIconSize{ 44, 44 };

public:
	CUserInterface();

	bool OnInitSpritesSudoku(CSudoku& sudoku);

	bool OnInitSpritesSelection();

	bool LoadSpriteButton(std::string path, CSprite sprite[], CVec2 spriteSize, CSpriteList& spriteList, int x, int y);

	bool OnLButtonUpSelection(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSelection(CPoint point);

	bool OnLButtonUpSudoku(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSudoku(CPoint point);

	void ButtonDownAnimation(CPoint point, CSprite sprite[], CSpriteList& spriteList, CVec2 spriteSize);

	bool CheckButtonUp(CPoint point, CSprite sprite[], CVec2 spriteSize);

	void OnChar(UINT nChar, CSudoku& sudoku);

	CDIB& GetBuffer();

	CSpriteList& GetSpriteListSudoku();

	CSpriteList& GetSpriteListSelection();

	CSprite& GetSelectFrame();

	CSprite* GetSelectDimension();

	CSprite* GetButtonExit();

	CVec2 GetCellIndex(CVec2& position);

	void openURL(const std::string& url);

	void RemoveSprites();

	void SetCell(CVec2& position, int number);

	CSprite* LoadSpriteNumber(CVec2& position, int number, float alpha = 1);

	CSprite* GetSprite(CVec2& position);
};


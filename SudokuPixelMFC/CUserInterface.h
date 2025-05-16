#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "CSudoku.h"

/*TODO:	- Ordner mit Sprites sortieren und struktieren
		- Undo/Reset/Check/Solve/Save Funktion
		- Code kommentieren
		- Startbildschirm mit Intro
		- Sound??*/ 

class CUserInterface
{
public:
	enum Status : int
	{
		Default,
		Pressed
	};

private:
	struct CVec2
	{
		int x;
		int y;

		CVec2() : x(0), y(0) {}

		CVec2(int xValue, int yValue) : x(xValue), y(yValue) {}

		bool operator==(const CVec2& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const CVec2& other) const
		{
			return !(*this == other);
		}

		CVec2& operator=(const CVec2& other)
		{
			return CVec2(x = other.x, y = other.y);
		}

		CVec2& operator+(const CVec2& other)
		{
			return CVec2(x + other.x, y + other.y);
		}

		CVec2& operator-(const CVec2& other)
		{
			return CVec2(x - other.x, y - other.y);
		}
	};

	struct SpriteArray
	{
		SpriteArray(CSprite* sprite, int number, CVec2 position) : sprite(sprite), number(number), position(position) { }

		CSprite* sprite;
		int number;
		CVec2 position;
	};

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

	CVec2 offset{ 58, 10 };
	CVec2 blockSpacing{ 3, 3 };
	CVec2 gridSize{ 423, 423 };
	CVec2 tileSize{ 45, 45 };
	CVec2 numberSize{ 32, 32 };

	CVec2 buttonSelectRow{ 70, 25 };
	CVec2 buttonSpace{ 0, 60 }; //buttonSize mit eingerechnet

	CVec2 buttonRowFirst{ 0, 445 };
	CVec2 buttonRowSecond{ 0, 445 + buttonSpace.y };
	CVec2 buttonRowThird{ 0, 445 + buttonSpace.y * 2 };

	CVec2 easyButtonSize{ 136, 52 };
	CVec2 mediumButtonSize{ 204, 52 };
	CVec2 hardButtonSize{ 140, 52 };
	CVec2 expertButtonSize{ 192, 52 };
	CVec2 godButtonSize{ 116, 52 };
	CVec2 backButtonSize{ 136, 52 };
	CVec2 exitButtonSize{ 128, 52 };
	CVec2 undoButtonSize{ 140, 52 };
	CVec2 saveButtonSize{ 136, 52 };
	CVec2 solveButtonSize{ 160, 52 };
	CVec2 checkButtonSize{ 164, 52 };
	CVec2 resetButtonSize{ 164, 52 };

public:
	bool OnInitSpritesSudoku(CSudoku& sudoku);

	bool OnInitSpritesSelection();

	bool LoadSpriteButton(std::string path, CSprite sprite[], CVec2 spriteSize, CSpriteList& spriteList, int x, int y);

	bool OnLButtonUpSelection(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSelection(CPoint point);

	bool OnLButtonUpSudoku(CPoint point, CSudoku& sudoku);

	void OnLButtonDownSudoku(CPoint point);

	void ButtonDownAnimation(CPoint point, CSprite sprite[], CSpriteList& spriteList, CVec2 spriteSize);

	bool CheckButtonUp(CPoint point, CSprite sprite[], CVec2 spriteSize);

	CDIB& GetBuffer();

	CSpriteList& GetSpriteListSudoku();

	CSpriteList& GetSpriteListSelection();

	CSprite& GetSelectFrame();

	CSprite* GetSelectDimension();

	CSprite* GetButtonExit();

	int GetCellIndex(int position, int offset, int tileSize, int blockSpacing);

	void RemoveSprites();

	void SetCell(CVec2& position, int number);

	CSprite* LoadSpriteNumber(int number);

	CSprite* GetSprite(CVec2& position);
};


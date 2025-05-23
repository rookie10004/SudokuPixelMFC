#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "CSudoku.h"
#include "CVec2.h"
#include <cstdlib>
#include "CUndo.h"
#include "CSolve.h"


class CUserInterface : public CDialogEx
{
private:
	CVec2 selectionSize{ 344, 470 };

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

	CVec2 currentCell{ -1, -1 };

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
	CSprite buttonSave[2];
	CSprite buttonBack[2];
	CSprite buttonExit[2];
	CSprite buttonGithub;
	CSprite buttonCheck[4];
	bool buttonEnabled = true;

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

	bool OnInitSpritesSudoku(CSudoku& sudoku); //initialiesiert sprites f�r zweiten Dialogfenster

	bool OnInitSpritesSelection(); //initialiesiert sprites f�r ersten Dialogfenster

	bool LoadSpriteButton(std::string path, CSprite sprite[], CVec2 spriteSize, CSpriteList& spriteList, int x, int y); //Hilfsfunktion zum initaliseren der button sprites

	bool OnLButtonUpSelection(CPoint point, CSudoku& sudoku); //Eventfunktion

	void OnLButtonDownSelection(CPoint point); //Eventfunktion

	bool OnLButtonUpSudoku(CPoint point, CSudoku& sudoku, CUndo& undo, CSolve& solve); //Eventfunktion

	void OnLButtonDownSudoku(CPoint point); //Eventfunktion

	void ButtonDownAnimation(CPoint point, CSprite sprite[], CSpriteList& spriteList, CVec2 spriteSize); //Animation f�r button sprites gedr�ckt

	bool CheckButtonUp(CPoint point, CSprite sprite[], CVec2 spriteSize); //�berpr�ft ob button gedr�ckt werden

	void OnChar(UINT nChar, CSudoku& sudoku, CUndo& undo); //Eventfunktion

	CDIB& GetBuffer();

	CSpriteList& GetSpriteListSudoku();

	CSpriteList& GetSpriteListSelection();

	CSprite& GetSelectFrame();

	CSprite* GetSelectDimension();

	CSprite* GetButtonExit();

	CVec2 GetCellIndex(CVec2& position); //berechnet Array index

	void LoadFile(std::string filePath, CSudoku& sudoku); //Hilfsfunktion zum Laden des alten, wenn vorhanden, oder neuen Spielstands

	void openURL(const std::string& url); //�ffnet im Standardbrowser den Link je nach BS (BS wird im Pr�prozess erkannt)

	void RemoveSprites(); //entfernt alle gedr�ckten button sprites

	void RemoveNumbers(); //entfernt alle Nummern aus dem array und der spriteliste

	void ButtonCheckRemove(); //entfernt button sprite explizit f�r den Check button

	void SetCell(CVec2& position, int number, CSudoku& sudoku); //l�dt Nummer sprite in das entsprechende Feld und l�scht das vorherige

	CSprite* LoadSpriteNumber(CVec2& position, int number, float alpha = 1); //setzt X/Y/Z/Alpha f�r die Nummer sprite (Hilfsfunktion von SetCell)

	CSprite* GetSprite(CVec2& position);
};


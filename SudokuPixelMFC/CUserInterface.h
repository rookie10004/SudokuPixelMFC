#pragma once
#include "spritelib.h"
#include <string>
#include <vector>

class CUserInterface
{
private:
	CDIB buffer;
	CSprite bkg;
	CSprite number[10];
	CSprite frame;
	CSprite buttonExit[2];
	CSprite selectFrame;
	CSprite selectDimension[2];
	CSpriteList spriteList;

	int offsetX = 58;
	int offsetY = 10;
	int gridSize = 423;

	int buttonRow = 450;

	int buttonExitY = 123;

public:
	BOOL OnInitSprites();

	CDIB& GetBuffer();

	CSpriteList& GetSpriteList();

	CSprite& GetSelectFrame();

	CSprite* GetSelectDimension();

	CSprite* GetButtonExit();

	int GetCellIndex(int position, int offset, int tileSize, int blockSpacing);
};


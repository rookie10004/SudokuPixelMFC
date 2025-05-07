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
	CSprite button[5];
	CSpriteList spriteList;


public:
	BOOL OnInitSprites();

	CDIB& GetBuffer();

	CSpriteList& GetSpriteList();
};


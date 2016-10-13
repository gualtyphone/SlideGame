#pragma once
#include "cocos2d.h"
#include <string>
#include "MainMenu.h"
#include "ReadWriteSettings.h"

class WinScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int time, int moves);
	static WinScene* create(int time, int moves);
	virtual bool init(int time, int moves);
	
	virtual void initBackground();
	virtual void initImage();
	virtual void initMenu();

	virtual void playAgain(cocos2d::Ref* sender);
	virtual void mainMenu(cocos2d::Ref* sender);
	virtual void exit(cocos2d::Ref* sender);

private:

	int finalTime;
	int finalMoves;

	std::string imgName;
	float puzzleImgSize;

	int tilesH;
	int tilesW;

};

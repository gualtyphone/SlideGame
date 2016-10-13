#pragma once
#include <string>
#include <random>
#include "time.h"
#include "cocos2d.h"
#include "WinScene.h"
#include "GameTile.h"
#include "MainMenu.h"
#include "ReadWriteSettings.h"
#include "SimpleAudioEngine.h" 

class GameScene : public cocos2d::Layer
{
public:
	//--------------------------------------------------------
	//				SCENE CREATION/DELETION
	//--------------------------------------------------------
	~GameScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
	virtual bool init() override;
	virtual void initBackground();
	virtual void initMenu();
	virtual void initTiles();

	//--------------------------------------------------------
	//				TILES MOVING
	//--------------------------------------------------------
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event * event) override;

	//functions that chech if there is an empty place in a direction
	// and moves the tiles in that direction
	bool checkAndMoveUP(int ID);
	bool checkAndMoveDOWN(int ID);
	bool checkAndMoveLEFT(int ID);
	bool checkAndMoveRIGHT(int ID);

	void checkVictory();

	//--------------------------------------------------------
	//				TILES SHUFFLING FUNCTIONS
	//--------------------------------------------------------
	void shuffleTiles();
	int checkAndMoveSingleTile(int ID);

	//--------------------------------------------------------
	//				DISPLAYS FUNCTIONS
	//--------------------------------------------------------
	virtual void initTimer();
	virtual void updateTimer(float dt);

	virtual void initMovesDisplay();
	virtual void updateMovesDisplay();

private:
	GameTile* tile = nullptr;

	//array of the positions on the window tiles need to be in
	cocos2d::Vec2* position = nullptr; 

	bool shuffling = false;
	bool manualShuffling = false;
	int timesShuffled = 0;

	std::string imgName;
	int tilesH; //number of tiles in height
	int tilesW; //number of tiles in width

	//label that displays the current timer(here because i need to access from multiple functions)
	cocos2d::Label* timerLabel = nullptr;
	int timeStarted;

	cocos2d::Label* movesLabel = nullptr;
	int moves;
};

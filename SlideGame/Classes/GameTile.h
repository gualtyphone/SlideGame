#pragma once
#include "cocos2d.h"
//#include "GameScene.h"
#include <string>

class GameTile
{
public:
	//--------------------------------------------------------
	//				INITIATION
	//--------------------------------------------------------
	void init(std::string imgName, int id, int posId, cocos2d::Vec2 singleTileSize, cocos2d::Vec2 posForRect);
	void setScale(float scaleH, float scaleW);
	void setPos(int newPosId, cocos2d::Vec2 newPos);

	//--------------------------------------------------------
	//				MOVING LOGIC
	//--------------------------------------------------------
	bool moveTile(int newPosId, cocos2d::Vec2 newPos);

	//--------------------------------------------------------
	//				GETTERS & SETTERS
	//--------------------------------------------------------
	int getId();
	int getPosId();
	void setPosId(int newPosId);


	cocos2d::Sprite* sprite = nullptr;

private:
	int _id;
	int positionId;
	cocos2d::Vec2 size;
	cocos2d::Vec2 position;
};


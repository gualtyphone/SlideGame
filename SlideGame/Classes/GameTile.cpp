#include "GameTile.h"
USING_NS_CC;

//--------------------------------------------------------
//				INITIALIZATION
//--------------------------------------------------------
void GameTile::init(std::string imgName, int id, int posId, Vec2 singleTileSize, Vec2 posForRect)
{
	_id = id;
	positionId = posId;
	sprite = Sprite::create(imgName, Rect(posForRect.x, posForRect.y, singleTileSize.x, singleTileSize.y));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setTag(1);
}

void GameTile::setScale(float scaleH, float scaleW)
{
	sprite->setScaleX(scaleW);
	sprite->setScaleY(scaleH);
}

void GameTile::setPos(int newPosId, Vec2 newPos)
{
	positionId = newPosId;
	position = newPos;
	sprite->setPosition(newPos);
}

//--------------------------------------------------------
//				MOVING LOGIC
//--------------------------------------------------------
bool GameTile::moveTile(int newPosId, Vec2 newPos)
{
	if (sprite->getNumberOfRunningActions() == 0)
	{
		positionId = newPosId;
		auto moveTo = MoveTo::create(0.2, newPos);
		sprite->runAction(moveTo);
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------
//				GETTERS & SETTERS
//--------------------------------------------------------
int GameTile::getId()
{
	return _id;
}

int GameTile::getPosId()
{
	return positionId;
}

void GameTile::setPosId(int newPosId)
{
	positionId = newPosId;
}
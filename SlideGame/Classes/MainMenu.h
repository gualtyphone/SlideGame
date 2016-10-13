#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "SettingsScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#include "CocosGUI.h"
#else
	#include "ui/CocosGUI.h"
#endif

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void initMusic();
	virtual void initBackground();
	virtual void initMenu();

	//implement the "static create()" function manually
	CREATE_FUNC(MainMenu);

private:
	std::string imgName;

	int tilesH;
	int tilesW;
};

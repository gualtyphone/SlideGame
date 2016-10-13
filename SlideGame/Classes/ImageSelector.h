#pragma once
#include "cocos2d.h"
#include <string>
#include "SettingsScene.h"
#include "ReadWriteSettings.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#include "CocosGUI.h"
#else
	#include "ui/CocosGUI.h"
#endif

#if (CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
    #include <windows.h>
#endif

class ImageSelector : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	static ImageSelector* create();
	virtual bool init() override;

	virtual void initBackground();
	virtual void initMenu();

	virtual void prevMenu(cocos2d::Ref* sender);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event * event) override;

private:

	int imgNumber;

	std::string* imgPaths = nullptr;

	std::string imgName;
	int tilesH;
	int tilesW;
};


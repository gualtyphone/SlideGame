#pragma once
#include "cocos2d.h"
#include <string>
#include "MainMenu.h"
#include "ImageSelector.h"
#include "ReadWriteSettings.h"
#include <iostream>
#include <fstream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#include "CocosGUI.h"
#else
	#include "ui/CocosGUI.h"
#endif


class SettingsScene : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	static SettingsScene* create();
	virtual bool init();
	virtual void initBackground();


	virtual void imageChange(cocos2d::Ref* sender);
	virtual void mainMenu(cocos2d::Ref* pSender);
	virtual void updateSlider();


	void initMenu();



private:

	cocos2d::ui::Slider* classSliderW = nullptr;
	cocos2d::ui::Slider* classSliderH = nullptr;
	
	cocos2d::Label* classGridSizeLabelW = nullptr;
	cocos2d::Label* classGridSizeLabelH = nullptr;

	std::string gridSizeStringW;
	std::string gridSizeStringH;

	std::string imgName;

	int tilesH;
	int tilesW;

};
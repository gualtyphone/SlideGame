#include "SettingsScene.h"
USING_NS_CC;

cocos2d::Scene* SettingsScene::createScene()
{
	cocos2d::Scene* scene = Scene::create();
	auto layer = SettingsScene::create();

	scene->addChild(layer);

	return scene;
}

SettingsScene* SettingsScene::create()
{
	SettingsScene *ss = new SettingsScene();

	if (ss->init()) {
		ss->autorelease();
		//here write your code to initialize everything
	}
	else
		ss = NULL;

	return ss;

}

bool SettingsScene::init()
{
	ReadWriteSettings::readSettings(tilesW, tilesH, imgName);
	initBackground();
	initMenu();

	return true;
}

void SettingsScene::initBackground()
{
	auto backdrop = Sprite::create("background/SlideGameBackground.png");
	float tempH = backdrop->getBoundingBox().size.height;
	float screenH = Director::getInstance()->getVisibleSize().height;
	float scale = screenH / tempH;
	backdrop->setScale(scale);
	backdrop->setAnchorPoint(Vec2(0, 0));
	auto origin = Director::getInstance()->getVisibleOrigin();
	backdrop->setPosition(origin);
	this->addChild(backdrop, -1);
}

void SettingsScene::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float tempScale;

	//--------------OLD------------------
	float positionH = visibleSize.height / 10; // used to set the height of all things

	//--------------TITLE------------------
	cocos2d::Label* titleLabel = Label::createWithTTF("Settings", "fonts/Onky.ttf", 60);
	titleLabel->setPosition(Vec2(origin.x + (visibleSize.width / 2), origin.y + (positionH * 9)));
	this->addChild(titleLabel, 2);

	//--------------SLIDERS------------------
    std::ostringstream convert;   // stream used for the conversion
    convert << tilesW;      // insert the textual representation of 'Number' in the characters in the stream
    gridSizeStringW = "Width: " + convert.str();
    auto gridSizeLabelW = Label::createWithTTF(gridSizeStringW, "fonts/Onky.ttf", 16);
    classGridSizeLabelW = gridSizeLabelW;
	gridSizeLabelW->setPosition(Vec2(origin.x + (visibleSize.width / 2), origin.y + (positionH * 7.5)));
	this->addChild(gridSizeLabelW, 2);

	auto sliderW = ui::Slider::create();
	classSliderW = sliderW;
	sliderW->loadBarTexture("ui/Slider_Back.png"); // what the slider looks like
	sliderW->loadSlidBallTextures("ui/SliderNode_Normal.png", "ui/SliderNode_Press.png", "ui/SliderNode_Disable.png");
	sliderW->loadProgressBarTexture("ui/Slider_PressBar.png");
	sliderW->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			updateSlider();
			break;
		default:
			break;
		}
	});
	sliderW->setMaxPercent(7);
	sliderW->setPercent(tilesW-3);
	tempScale = (visibleSize.width / 3) / sliderW->getBoundingBox().size.width;
	sliderW->setScale(tempScale);
	sliderW->setPosition(Vec2(origin.x + (visibleSize.width / 10*5), origin.y + (positionH * 7)));
	this->addChild(sliderW, 2);

    std::ostringstream convert2;   // stream used for the conversion
    convert2 << tilesH;      // insert the textual representation of 'Number' in the characters in the stream
    gridSizeStringH = "Height: " + convert2.str();
    auto gridSizeLabelH = Label::createWithTTF(gridSizeStringH, "fonts/Onky.ttf", 16);
    classGridSizeLabelH = gridSizeLabelH;
	gridSizeLabelH->setPosition(Vec2(origin.x + (visibleSize.width / 2), origin.y + (positionH * 5.5)));
	this->addChild(gridSizeLabelH, 2);

	auto sliderH = ui::Slider::create();
	classSliderH = sliderH;
	sliderH->loadBarTexture("ui/Slider_Back.png"); // what the slider looks like
	sliderH->loadSlidBallTextures("ui/SliderNode_Normal.png", "ui/SliderNode_Press.png", "ui/SliderNode_Disable.png");
	sliderH->loadProgressBarTexture("ui/Slider_PressBar.png");
	sliderH->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			updateSlider();
			break;
		default:
			break;
		}
	});
	sliderH->setMaxPercent(7);
	sliderH->setPercent(tilesH - 3);
	tempScale = (visibleSize.width / 3) / sliderH->getBoundingBox().size.width;
	sliderH->setScale(tempScale);
	sliderH->setPosition(Vec2(origin.x + (visibleSize.width / 10 * 5), origin.y + (positionH * 5)));
	this->addChild(sliderH, 2);

	//--------------MAIN MENU BUTTON------------------
	auto mainMenuButton = ui::Button::create("ui/MainMenuButtonNormal.png",
		"ui/MainMenuButtonPressed.png",
		"ui/MainMenuButtonPressed.png");
	tempScale = (visibleSize.width / 3) / mainMenuButton->getBoundingBox().size.width;
	mainMenuButton->setScale(tempScale);
	mainMenuButton->setAnchorPoint(Vec2(0.5, 0));
	mainMenuButton->setPosition(Vec2(origin.x + (visibleSize.width / 2), origin.y + 10));
	mainMenuButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);
			Director::getInstance()->replaceScene(MainMenu::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(mainMenuButton);

	//--------------CHANGE IMAGE BUTTON------------------
	auto changeImageButton = ui::Button::create("ui/ChangeImageButtonNormal.png",
		"ui/ChangeImageButtonPressed.png",
		"ui/ChangeImageButtonPressed.png");
	tempScale = (visibleSize.width / 3) / changeImageButton->getBoundingBox().size.width;
	changeImageButton->setScale(tempScale);
	changeImageButton->setAnchorPoint(Vec2(0.5, 0));
	changeImageButton->setPosition(Vec2(origin.x + (visibleSize.width / 2), 
										(mainMenuButton->getPositionY() + 
										mainMenuButton->getBoundingBox().size.height) + 10));
	changeImageButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);
			Director::getInstance()->replaceScene(ImageSelector::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(changeImageButton);


}

void SettingsScene::imageChange(cocos2d::Ref* sender)
{
	ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);

	Director::getInstance()->replaceScene(ImageSelector::createScene());
}

void SettingsScene::mainMenu(cocos2d::Ref* sender)
{
	ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void SettingsScene::updateSlider()
{
	tilesW = classSliderW->getPercent()+3;
	tilesH = classSliderH->getPercent()+3;

	std::ostringstream convertW;   // stream used for the conversion
	convertW << tilesW;      // insert the textual representation of 'Number' in the characters in the stream
	gridSizeStringW = "Width: " + convertW.str();

	classGridSizeLabelW->setString(gridSizeStringW);

	std::ostringstream convertH;   // stream used for the conversion
	convertH << tilesH;      // insert the textual representation of 'Number' in the characters in the stream
    gridSizeStringH = "Height: " + convertH.str();

	classGridSizeLabelH->setString(gridSizeStringH);
}
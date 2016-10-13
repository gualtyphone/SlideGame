#include "WinScene.h"
USING_NS_CC;

cocos2d::Scene* WinScene::createScene(int time, int moves)
{

	cocos2d::Scene* scene = Scene::create();
	auto layer = WinScene::create(time, moves);

	scene->addChild(layer);

	return scene;
}

WinScene* WinScene::create(int time, int moves)
{
	WinScene *ws = new WinScene();

	if (ws->init(time, moves)) {
		ws->autorelease();
		//here write your code to initialize everything
	}
	else
		ws = NULL;

	return ws;

}

bool WinScene::init(int time, int moves)
{
	finalTime = time;
	finalMoves = moves;
	ReadWriteSettings::readSettings(tilesW, tilesH, imgName);

	Size screenSize = Director::getInstance()->getVisibleSize();
	puzzleImgSize = (screenSize.height)-72;
	initBackground();
	initImage();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// set the background music and continuously play it.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	audio->playEffect("audio/Won.mp3");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	audio->playEffect("audio/Won.wav");
#endif
	initMenu();

	return true;
}

void WinScene::initBackground()
{
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto backdrop = Sprite::create("background/SlideGameBackground.png");
	float tempH = backdrop->getBoundingBox().size.height;
	float screenH = Director::getInstance()->getVisibleSize().height;
	float tempScale = screenH / tempH;
	backdrop->setScale(tempScale);
	backdrop->setAnchorPoint(Vec2(0, 0));
	backdrop->setPosition(origin);
	backdrop->setTag(101);
	this->addChild(backdrop, -1);

	auto gridBackdrop = Sprite::create("background/GridBackground.png");
	tempH = gridBackdrop->getBoundingBox().size.height;
	tempScale = screenH / tempH;
	gridBackdrop->setScale(tempScale);
	gridBackdrop->setAnchorPoint(Vec2(0, 0));
	gridBackdrop->setPosition(origin);
	gridBackdrop->setTag(100);
	this->addChild(gridBackdrop, -1);
}

void WinScene::initImage()
{
	auto img = Sprite::create(imgName);
	int totHeight = img->getBoundingBox().size.height;
	int totWidth = img->getBoundingBox().size.width;
	float bgHeight = this->getChildByTag(100)->getBoundingBox().size.height;
	float bgWidth = this->getChildByTag(100)->getBoundingBox().size.width;

	float puzzleHeight = bgHeight - ((bgHeight * 76) / 720);
	float puzzleWidth = bgWidth - ((bgWidth * 76) / 720);

	float scaleH = puzzleHeight / totHeight;
	float scaleW = puzzleWidth / totWidth;

	img->setScaleX(scaleW);
	img->setScaleY(scaleH);
	img->setAnchorPoint(Vec2(0, 0));
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 pos(((bgWidth * 38) / 720), ((bgHeight * 38) / 720));
    pos.add(origin);
	img->setPosition(pos);
	this->addChild(img, 0);
}

void WinScene::initMenu()
{
	float bgWidth = this->getChildByTag(100)->getBoundingBox().size.width;
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	cocos2d::Label* youWonLabel = Label::createWithTTF("You WON", "fonts/Onky.ttf", 40);
	youWonLabel->setAnchorPoint(Vec2(0.5, 1));
	youWonLabel->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2), 
									(origin.y + visibleSize.height-20)));
	this->addChild(youWonLabel, 2);

	Label* timerLabel = Label::createWithTTF("TIME 0", "fonts/Onky.ttf", 20);
	std::ostringstream convertTime;
	convertTime << finalTime;
	std::string timeString = ("TIME ") + convertTime.str();
	timerLabel->setString(timeString);
	timerLabel->setAnchorPoint(Vec2(0.5, 1));
	timerLabel->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2),
		(youWonLabel->getPositionY()) - (youWonLabel->getBoundingBox().size.height + 30)));
	this->addChild(timerLabel, 2);

	Label* movesLabel = Label::createWithTTF("MOVES 0", "fonts/Onky.ttf", 20);
	std::ostringstream convertMoves;
	convertMoves << finalMoves;
	std::string movesString = ("MOVES ") + convertMoves.str();
	movesLabel->setString(movesString);
	movesLabel->setAnchorPoint(Vec2(0.5, 1));
	movesLabel->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2),
		(timerLabel->getPositionY()) - (timerLabel->getBoundingBox().size.height + 10)));
	this->addChild(movesLabel, 2);

	auto mainMenuButton = ui::Button::create("ui/MainMenuButtonNormal.png",
		"ui/MainMenuButtonPressed.png",
		"ui/MainMenuButtonPressed.png");
	float tempScale = (visibleSize.width - bgWidth) / mainMenuButton->getBoundingBox().size.width;
	mainMenuButton->setScale(tempScale);
	mainMenuButton->setAnchorPoint(Vec2(0.5, 0));
	mainMenuButton->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2),
										(origin.y + visibleSize.height / 2) + 10));
	mainMenuButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(MainMenu::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(mainMenuButton);

	auto shuffleButton = ui::Button::create("ui/PlayAgainButtonNormal.png",
		"ui/PlayAgainButtonPressed.png",
		"ui/PlayAgainButtonPressed.png");
	tempScale = (visibleSize.width - bgWidth) / shuffleButton->getBoundingBox().size.width;
	shuffleButton->setScale(tempScale);
	shuffleButton->setAnchorPoint(Vec2(0.5, 1));
	shuffleButton->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2), 
									(origin.y + visibleSize.height / 2) - 10));
	shuffleButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(shuffleButton);
}


void WinScene::playAgain(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void WinScene::mainMenu(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void WinScene::exit(cocos2d::Ref*pSender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
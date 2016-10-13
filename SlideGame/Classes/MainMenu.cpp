#include "MainMenu.h"
USING_NS_CC;

cocos2d::Scene* MainMenu::createScene()
{
	cocos2d::Scene* scene = Scene::create();
	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	initMusic();
	initBackground();
	initMenu();

	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void MainMenu::initMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	if (!(audio->isBackgroundMusicPlaying()))
	{
		// set the background music and continuously play it.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		audio->playBackgroundMusic("audio/GameSoundtrack.mp3", true);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		audio->playBackgroundMusic("audio/GameSoundtrack.wav", true);
#endif
	}
}

void MainMenu::initBackground() 
{
	auto backdrop = Sprite::create("background/SlideGameBackground.png");
	float tempH = backdrop->getBoundingBox().size.height;
	float screenH = Director::getInstance()->getVisibleSize().height;
	float scale = screenH / tempH;
	backdrop->setScale(scale);
	backdrop->setAnchorPoint(Vec2(0, 0));
	auto origin = Director::getInstance()->getVisibleOrigin();
	backdrop->setPosition(origin);
	backdrop->setTag(0);
	this->addChild(backdrop, -1);
}

void MainMenu::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto title = Sprite::create("ui/SlideGameLogo.png");
	float scale = visibleSize.width / title->getBoundingBox().size.width;
	title->setScale(scale);
	title->setAnchorPoint(Vec2(0.5, 1));
	title->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height)));
	this->addChild(title, 2);

	auto playButton = ui::Button::create("ui/PlayButtonNormal.png",
									"ui/PlayButtonPressed.png",
									"ui/PlayButtonPressed.png");
	scale = (visibleSize.width / 3) / playButton->getBoundingBox().size.width;
	playButton->setScale(scale);
	playButton->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 10 * 5.5)));
	playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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
	this->addChild(playButton);

	auto settingsButton = ui::Button::create("ui/SettingsButtonNormal.png",
		"ui/SettingsButtonPressed.png",
		"ui/SettingsButtonPressed.png");
	scale = (visibleSize.width / 3) / settingsButton->getBoundingBox().size.width;
	settingsButton->setScale(scale);
	settingsButton->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 10 * 3.5)));
	settingsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(SettingsScene::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(settingsButton);

	auto quitButton = ui::Button::create("ui/QuitButtonNormal.png",
		"ui/QuitButtonPressed.png",
		"ui/QuitButtonPressed.png");
	scale = (visibleSize.width / 3) / quitButton->getBoundingBox().size.width;
	quitButton->setScale(scale);
	quitButton->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 10 * 1.5)));
	quitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
			break;
		default:
			break;
		}
	});
	this->addChild(quitButton);
}

//void MainMenu::initSpriteCache() 
//{
//	// load the Sprite Sheet
//	auto spriteCache = SpriteFrameCache::getInstance();
//
//	// the .plist file can be generated with any of the tools mentioned below
//	spriteCache->addSpriteFramesWithFile("standardImages.plist");
//}
#include "ImageSelector.h"
USING_NS_CC;

cocos2d::Scene* ImageSelector::createScene()
{
	cocos2d::Scene* scene = Scene::create();
	auto layer = ImageSelector::create();

	scene->addChild(layer);

	return scene;
}

ImageSelector* ImageSelector::create()
{
	ImageSelector *ss = new ImageSelector();

	if (ss->init()) {
		ss->autorelease();
		//here write your code to initialize everything
	}
	else
		ss = NULL;

	return ss;
}

bool ImageSelector::init()
{
	ReadWriteSettings::readSettings(tilesW, tilesH, imgName);

	imgNumber = 4;
	imgPaths = new std::string[imgNumber];
	imgPaths[0] = "images/MickeyMouse.png";
	imgPaths[1] = "images/MickeyMo.png";
	imgPaths[2] = "images/Sun.png";
	imgPaths[3] = "images/UP.png";

	initBackground();
	initMenu();

	return true;
}

void ImageSelector::initBackground()
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

void ImageSelector::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < imgNumber; i++)
	{
		std::string currentPath = imgPaths[i];
		auto image = Sprite::create();
		image->setTag(i + 1);
		image->setTexture(currentPath);

		float currW = image->getBoundingBox().size.width;
		float currH = image->getBoundingBox().size.height;

		float scaleW = (((visibleSize.width / imgNumber) / currW) * 90) / 100;
		float scaleH = (((visibleSize.width / imgNumber) / currH) * 90) / 100;

		image->setScaleY(scaleH);
		image->setScaleX(scaleW);
        Vec2 pos((visibleSize.width / (imgNumber * 2)) * ((i * 2) + 1),(visibleSize.height / 3) * 2);
        pos.add(origin);
        image->setPosition(pos);
		image->setOpacity(50);
		if (currentPath == imgName)
		{
			image->setOpacity(255);
		}

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(ImageSelector::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, image);

		this->addChild(image);
	}

	


	auto backButton = ui::Button::create("ui/BackButtonNormal.png",
		"ui/BackButtonPressed.png",
		"ui/BackButtonPressed.png");
	float tempScale = (visibleSize.width / 3) / backButton->getBoundingBox().size.width;
	backButton->setScale(tempScale);
	backButton->setAnchorPoint(Vec2(0.5, 0));
	backButton->setPosition(Vec2(origin.x + (visibleSize.width / 2), origin.y + 10));
	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);
			Director::getInstance()->replaceScene(SettingsScene::createScene());
			break;
		default:
			break;
		}
	});
	this->addChild(backButton);
}

void ImageSelector::prevMenu(cocos2d::Ref* sender)
{
	ReadWriteSettings::writeSettings(tilesW, tilesH, imgName);
	Director::getInstance()->replaceScene(SettingsScene::createScene());
}

bool ImageSelector::onTouchBegan(Touch* touch, Event * event)
{
	//tag to identify sprite
	if (event->getCurrentTarget()->getTag() > 0 && event->getCurrentTarget()->getTag() <= imgNumber)
	{
		Point location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		Sprite* currentTile = (Sprite*)event->getCurrentTarget();
		if (currentTile->getBoundingBox().containsPoint(location))
		{
			for (int i = 0; i < imgNumber; i++)
			{
				event->getCurrentTarget()->getParent()->getChildByTag(i + 1)->setOpacity(50);
			}
			currentTile->setOpacity(255);
			imgName = imgPaths[currentTile->getTag()-1];
		}
	}
	return true;
}
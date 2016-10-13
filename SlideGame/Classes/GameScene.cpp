#include "GameScene.h"
#define WH w + (h*tilesW) 
USING_NS_CC;

//--------------------------------------------------------
//				SCENE CREATION/DELETION
//--------------------------------------------------------
GameScene::~GameScene()
{
	delete[] tile;
	delete[] position;
}

cocos2d::Scene* GameScene::createScene()
{
	cocos2d::Scene* scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	ReadWriteSettings::readSettings(tilesW, tilesH, imgName);

	if (tilesH == 6 && tilesW == 7)
	{
		imgName = "42.png";
		tilesH = 3;
		tilesW = 3;
	}

	srand(time(NULL));
	initBackground();
	initTiles();
	initMenu();
	initTimer();
	initMovesDisplay();
	return true;
}

void GameScene::initBackground()
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

void GameScene::initMenu()
{
    float bgWidth = this->getChildByTag(100)->getBoundingBox().size.width;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto mainMenuButton = ui::Button::create("ui/MainMenuButtonNormal.png",
		"ui/MainMenuButtonPressed.png",
		"ui/MainMenuButtonPressed.png");
	float tempScale = (visibleSize.width - bgWidth) / mainMenuButton->getBoundingBox().size.width;
	mainMenuButton->setScale(tempScale);
	mainMenuButton->setAnchorPoint(Vec2(0.5, 0));
	mainMenuButton->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2), (origin.y + visibleSize.height / 2)+10));
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
	
	auto shuffleButton = ui::Button::create("ui/ShuffleButtonNormal.png",
		"ui/ShuffleButtonPressed.png",
		"ui/ShuffleButtonPressed.png");
	tempScale = (visibleSize.width - bgWidth) / shuffleButton->getBoundingBox().size.width;
	shuffleButton->setScale(tempScale);
	shuffleButton->setAnchorPoint(Vec2(0.5, 1));
	shuffleButton->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2), (origin.y + visibleSize.height / 2) - 10));
	shuffleButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			manualShuffling = true;
			if (!shuffling) {
				shuffling = true;
				shuffleTiles();
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			manualShuffling = false;
			moves = 0;
			updateMovesDisplay();
			break;
		default:
			break;
		}
	});
	this->addChild(shuffleButton);
}

void GameScene::initTiles()
{
	tile = new GameTile[tilesW*tilesH];
	position = new Vec2[tilesW*tilesH];

	auto img = Sprite::create(imgName);
	int imgTotHeight = img->getBoundingBox().size.height;
	int imgTotWidth = img->getBoundingBox().size.width;

	Vec2 singleTileDimension(imgTotWidth / tilesW, imgTotHeight / tilesH);
	Vec2 bgDimension(this->getChildByTag(100)->getBoundingBox().size.width,
		this->getChildByTag(100)->getBoundingBox().size.height);

	//scale used to position the tiles in the correct place
	float positionScaleH = (bgDimension.y - ((bgDimension.y * 70) / 720)) / imgTotHeight;
	float positionScaleW = (bgDimension.x - ((bgDimension.x * 70) / 720)) / imgTotWidth;

	//98% of scale used for the image size(leave a small border)
	float dimensionScaleH = (positionScaleH * 98) / 100;
	float dimensionScaleW = (positionScaleW * 98) / 100;




	for (int h = 0; h < tilesH; h++)
	{
		for (int w = 0; w < tilesW; w++)
		{
			//these are used to create the image because rect starts from the top left while the position starts form bottom left
			Vec2 tilePositionOriginalImageFromBottomLeft(imgTotWidth / tilesW * w, imgTotHeight / tilesH * h);
			Vec2 tilePositionOriginalImageFromTopLeft(imgTotWidth / tilesW * w, (imgTotHeight - singleTileDimension.y) - (imgTotHeight / tilesH * h));

			Vec2 borderSpace(bgDimension.x * 38 / 720, bgDimension.y * 38 / 720);
			Vec2 scaledPosition(tilePositionOriginalImageFromBottomLeft.x*positionScaleW, tilePositionOriginalImageFromBottomLeft.y*positionScaleH);

			Vec2 tilePositionOnScren = Director::getInstance()->getVisibleOrigin();
			tilePositionOnScren.add(borderSpace);
			tilePositionOnScren.add(scaledPosition);

			position[WH] = tilePositionOnScren;

			tile[WH].init(imgName, WH, WH, singleTileDimension, tilePositionOriginalImageFromTopLeft);
			tile[WH].setScale(dimensionScaleH, dimensionScaleW);
			tile[WH].setPos(WH, position[WH]);
			if (WH != 0)
			{
				//Listener for when the tile is touched
				auto touchListener = EventListenerTouchOneByOne::create();
				touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, tile[WH].sprite);

				this->addChild(tile[WH].sprite);
			}
		}
	}
	shuffling = true;
	shuffleTiles();
}

//--------------------------------------------------------
//				TILES MOVING
//--------------------------------------------------------
bool GameScene::onTouchBegan(Touch* touch, Event * event)
{
	//tag to identify sprites
	if (event->getCurrentTarget()->getTag() == 1)
	{
		Point location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		for (int h = 0; h < tilesH; h++)
		{
			for (int w = 0; w < tilesW; w++)
			{
				if (WH != 0)
				{
					if (tile[WH].sprite->getBoundingBox().containsPoint(location))
					{
						int ID = tile[WH].getId();
						//if here is so the tile doesn't try to move if already moved in another direction
						bool moved = checkAndMoveUP(ID);
						if (!moved)
						{
							moved = checkAndMoveDOWN(ID);
							if (!moved)
							{
								moved = checkAndMoveLEFT(ID);
								if (!moved)
								{
									moved = checkAndMoveRIGHT(ID);
								}
							}
						}
						if (moved)
						{
							auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
							// set the background music and continuously play it.
							#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
								audio->playEffect("audio/Woosh.mp3");
							#endif
							#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
								audio->playEffect("audio/Woosh.wav");
							#endif

								moves++;
								updateMovesDisplay();
						}
						checkVictory();
					}
				}
			}
		}
	}
	return true;
}


bool GameScene::checkAndMoveUP(int ID)
{
	//this makes sure you don't try to move a tile that is already moving
	if (tile[ID].sprite->getNumberOfRunningActions() == 0)
	{
		int posId = tile[ID].getPosId();
		if (posId + tilesW < (tilesH*tilesW))
		{
			int tileUP = posId + tilesW;
			bool move = false;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileUP)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
						else
						{
							move = checkAndMoveUP(WH);
						}
					}
				}
			}
			if (move == true)
			{
				tile[ID].moveTile(tileUP, position[tileUP]);
				tile[0].setPosId(posId);
				return true;
			}
		}
	}
	return false;
}

bool GameScene::checkAndMoveDOWN(int ID)
{
	//this makes sure you don't try to move a tile that is already moving
	if (tile[ID].sprite->getNumberOfRunningActions() == 0)
	{
		int posId = tile[ID].getPosId();
		if (posId - tilesW >= 0)
		{
			int tileDOWN = posId - tilesW;
			bool move = false;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileDOWN)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
						else
						{
							move = checkAndMoveDOWN(WH);
						}
					}
				}
			}
			if (move == true)
			{
				tile[ID].moveTile(tileDOWN, position[tileDOWN]);
				tile[0].setPosId(posId);
				return true;
			}
		}
	}
	return false;
}

bool GameScene::checkAndMoveRIGHT(int ID)
{
	//this makes sure you don't try to move a tile that is already moving
	if (tile[ID].sprite->getNumberOfRunningActions() == 0)
	{
		int posId = tile[ID].getPosId();
		if ((posId + 1) % tilesW != 0)
		{
			int tileRIGHT = posId + 1;
			bool move = false;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileRIGHT)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
						else
						{
							move = checkAndMoveRIGHT(WH);
						}
					}
				}
			}
			if (move == true)
			{
				tile[ID].moveTile(tileRIGHT, position[tileRIGHT]);
				tile[0].setPosId(posId);
				return true;
			}
		}
	}
	return false;
}

bool GameScene::checkAndMoveLEFT(int ID)
{
	//this makes sure you don't try to move a tile that is already moving
	if (tile[ID].sprite->getNumberOfRunningActions() == 0)
	{
		int posId = tile[ID].getPosId();
		if ((posId - 1) % tilesW != tilesW - 1)
		{
			int tileLEFT = posId - 1;
			bool move = false;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileLEFT)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
						else
						{
							move = checkAndMoveLEFT(WH);
						}
					}
				}
			}
			if (move == true)
			{
				tile[ID].moveTile(tileLEFT, position[tileLEFT]);
				tile[0].setPosId(posId);
				return true;
			}
		}
	}
	return false;
}


void GameScene::checkVictory()
{
	int victoryPoints = 0;
	for (int h = 0; h < tilesH; h++)
	{
		for (int w = 0; w < tilesW; w++)
		{
			if (tile[WH].getPosId() == WH)
			{
				victoryPoints++;
			}
		}
	}
	CCLOG("victoryPoints = %i", victoryPoints);

	if (victoryPoints == tilesH*tilesW)
	{
		CCLOG("Won");

		//WinScene::imgName = imgName;

		std::ofstream settings;
		settings.open("settings.txt", std::ofstream::out | std::ofstream::trunc);
		settings.close();
		settings.open("settings.txt");
		settings << imgName + "\n";
		settings << tilesH;
		settings << "\n";
		settings << tilesW;
		settings.close();

		Scene* winScene = WinScene::createScene(time(NULL) - timeStarted, moves);
		Director::getInstance()->replaceScene(winScene);
	}
}

//--------------------------------------------------------
//				TILES SHUFFLING FUNCTIONS
//--------------------------------------------------------
void GameScene::shuffleTiles()
{
	if (timesShuffled < ((tilesH*tilesW) * 3) || manualShuffling)
	{
		int newPos = -1;
		while (newPos == -1)
		{
			int ID = (rand() % ((tilesW*tilesH) - 1)) + 1;
			//int posId = tile[ID].getPosId();
			newPos = checkAndMoveSingleTile(ID);
			if (newPos != -1)
			{
				auto moveTo = MoveTo::create(0.04f, position[newPos]);
				auto shuffle = CallFuncN::create(CC_CALLBACK_0(GameScene::shuffleTiles, this));
				auto seq = Sequence::create(moveTo, shuffle, nullptr);
				tile[ID].setPosId(newPos);
				tile[ID].sprite->runAction(seq);
				CCLOG("Shuffled: %i", timesShuffled);
				timesShuffled++;
			}
		}
	}
	else
	{
		timeStarted = time(NULL);
		shuffling = false;
		timesShuffled = 0;
		return;
	}
}

int GameScene::checkAndMoveSingleTile(int ID)
{
	//this function is very long, it containd the four functions checkAndMoveUP/DOWN/LEFT/RIGHT with a 
	// differnt line. It would be better to splice it up in 4 different functions but having only one makes the code
	// in shuffleTiles() much more readable.

	//this makes sure you don't try to move a tile that is already moving
	Sprite* sprite = tile[ID].sprite;
	if (sprite->getNumberOfRunningActions() == 0)
	{
		bool move = false;
		int posId = tile[ID].getPosId();
		if (posId + tilesW < (tilesH*tilesW))
		{
			int tileUP = posId + tilesW;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileUP)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
					}
				}
			}
			if (move == true)
			{
				tile[0].setPosId(posId);
				return tileUP;
			}
		}

		if (posId - tilesW >= 0)
		{
			int tileDOWN = posId - tilesW;
			
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileDOWN)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
					}
				}
			}
			if (move == true)
			{
				tile[0].setPosId(posId);
				return tileDOWN;
			}
		}

		if ((posId + 1) % tilesW != 0)
		{
			int tileRIGHT = posId + 1;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileRIGHT)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
					}
				}
			}
			if (move == true)
			{
				tile[0].setPosId(posId);
				return tileRIGHT;
			}
		}

		if ((posId - 1) % tilesW != tilesW - 1)
		{
			int tileLEFT = posId - 1;
			for (int h = 0; h < tilesH; h++)
			{
				for (int w = 0; w < tilesW; w++)
				{
					if (tile[WH].getPosId() == tileLEFT)
					{
						if (tile[WH].getId() == 0)
						{
							move = true;
						}
					}
				}
			}
			if (move == true)
			{
				tile[0].setPosId(posId);
				return tileLEFT;
			}
		}

	}
	return -1;
}

//--------------------------------------------------------
//				DISPLAYS FUNCTIONS
//--------------------------------------------------------
void GameScene::initTimer()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float bgWidth = this->getChildByTag(100)->getBoundingBox().size.width;

	timerLabel = Label::createWithTTF("TIME 0", "fonts/Onky.ttf", 20);
	timerLabel->setAnchorPoint(Vec2(0.5, 1));
	timerLabel->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2),
		origin.y + visibleSize.height - 50));	this->addChild(timerLabel, 2);

	timeStarted = time(NULL);
	this->schedule(schedule_selector(GameScene::updateTimer), 1.0f);
}

void GameScene::updateTimer(float dt)
{
	if (!shuffling) {
		int currentTime = time(NULL);
		int elapsedTime = currentTime - timeStarted;
		std::ostringstream convert;
		convert << elapsedTime;
		std::string timeString = ("TIME ") + convert.str();
		timerLabel->setString(timeString);
	}
}



void GameScene::initMovesDisplay()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float bgWidth = this->getChildByTag(100)->getBoundingBox().size.width;

	movesLabel = Label::createWithTTF("MOVES 0", "fonts/Onky.ttf", 20);
	movesLabel->setAnchorPoint(Vec2(0.5, 1));
	movesLabel->setPosition(Vec2(origin.x + bgWidth + ((visibleSize.width - bgWidth) / 2),
									(timerLabel->getPositionY()) - (timerLabel->getBoundingBox().size.height + 10)));
	this->addChild(movesLabel, 2);

	moves = 0;
}

void GameScene::updateMovesDisplay()
{
	std::ostringstream convert;
	convert << moves;
	std::string moevesString = ("MOVES ") + convert.str();
	movesLabel->setString(moevesString);
}
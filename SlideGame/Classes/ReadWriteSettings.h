#pragma once
#include <string>
#include "cocos2d.h"

struct ReadWriteSettings
{
public:
	static void readSettings(int &tilesW, int &tilesH, std::string &imgName);
	static void writeSettings(int tilesW, int tilesH, std::string imgName);
};
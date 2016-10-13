#include "ReadWriteSettings.h"
USING_NS_CC;

void ReadWriteSettings::readSettings(int &tilesW, int &tilesH, std::string &imgName)
{
	std::string path = FileUtils::getInstance()->getWritablePath() + "\\settings.bin";
	FILE* settings = fopen(path.c_str(), "rb");

	if (settings == NULL)
	{
		imgName = "images/MickeyMouse.png";
		tilesW = 4;
		tilesH = 4;
	}
	else
	{
		int newTilesW;
		int newTilesH;
		char newImageName[500];
		fread(&newTilesW, sizeof(int), 1, settings);
		fread(&newTilesH, sizeof(int), 1, settings);
		fread(&newImageName, sizeof(newImageName), 1, settings);
		fclose(settings);

		tilesW = newTilesW;
		tilesH = newTilesH;
		imgName = newImageName;
	}
	Sprite* sprite = Sprite::create(imgName);
	if (sprite == NULL)
	{
		imgName = "images/MickeyMouse.png";
	}

}
void ReadWriteSettings::writeSettings(int tilesW, int tilesH, std::string imgName)
{
	std::string path = FileUtils::getInstance()->getWritablePath() + "\\settings.bin";
	FILE* settings = fopen(path.c_str(), "wb");

	char imageName[500];
	strcpy(imageName, imgName.c_str());

	fwrite(&tilesW, sizeof(int), 1, settings);
	fwrite(&tilesH, sizeof(int), 1, settings);
	fwrite(&imageName, sizeof(imageName), 1, settings);

	fclose(settings);
}
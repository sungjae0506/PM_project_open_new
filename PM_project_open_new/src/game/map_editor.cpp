#include "map_editor.h"

static ImageManager imageManager("image_data.json");

void MapEditor::clear()
{
	mode = ModeTheme;
	layerState.clear();
	layerState.resize(3);

	maps.clear();
	maps.resize(maxStage);

	for (int i = 0; i < maxStage; ++i)
	{
		maps[i].backgroundStr = "game_background";
		maps[i].tileStr = "wood";
	}

	initialSettings.clear();
	initialSettings.resize(maxStage);

	modeThemeButtonState.clear();
	modeThemeButtonState.resize(6);
	modeThemeButtonState[0] = true;
	modeThemeButtonState[1] = true;


	modeCharacterButtonState.clear();
	modeCharacterButtonState.resize(6);

	modeCurrentButtonState.clear();
	modeCurrentButtonState.resize(5);

}

void MapEditor::setStage(int s)
{
	if (s != currentStage)
	{
		currentStage = s;
		for (int i = 0; i < 6; ++i)
		{
			modeThemeButtonState[i] = 0;
			modeCharacterButtonState[i] = 0;
		}
		for (int i = 0; i < 5; ++i)
		{
			modeCharacterButtonState[i] = 0;
		}
		if (maps[s].backgroundStr == "game_background")
		{
			modeThemeButtonState[0] = true;
		}
		else
		{
			modeThemeButtonState[3] = true;
		}
		if (maps[s].tileStr == "wood")
		{
			modeThemeButtonState[1] = true;
		}
		else
		{
			modeThemeButtonState[4] = true;
		}

	}
}

// //////////////////////////////////////////////////////////////

void MapEditor::drawEntity(void)
{
	
}

void MapEditor::drawMap()
{
	if (maps[currentStage].backgroundStr != "")
		maps[currentStage].setBackground(imageManager.getImages(maps[currentStage].backgroundStr));
	else
		maps[currentStage].background.clear();
	maps[currentStage].setTile(imageManager.getImages(maps[currentStage].tileStr));

	maps[currentStage].draw();
}

void MapEditor::keyboardEvent(KeyboardEvent e, string key, Point p)
{
	
}

void MapEditor::draw(Point mousePos)
{
	drawMap();
	drawEntity();
}

void MapEditor::readMap(string path)
{
	fstream f(path);
	json jsonData = json::parse(f);
	InitialSetting tempInitialSetting;
	Map tempMap;

	vector<vector<bool>> tempTile;
	vector<vector<char>> tempBubbleCurrent;
	string tempString;

	auto themeData = jsonData["theme"];
	auto playerData = jsonData["player"];
	auto enemyData = jsonData["enemy"];
	auto tileData = jsonData["tile"];
	auto bubbleCurrentData = jsonData["bubble_current"];


	for (auto i : playerData)
	{
		tempInitialSetting.addPlayerPos(Point(i["pos"][0].get<double>(), i["pos"][1].get<double>()));
	}
	for (auto i : enemyData)
	{
		tempInitialSetting.addEnemyPos(Point(i["pos"][0].get<double>(), i["pos"][1].get<double>()));
		tempInitialSetting.addEnemyName(i["name"].get<string>());
	}

	tempTile.resize(32);
	for (int i = 0; i < 32; ++i)
		tempTile[i].resize(32);

	for (int i = 0; i < 32; ++i)
	{
		tempString = tileData[i].get<string>();
		for (int j = 0; j < 32; ++j)
			tempTile[i][j] = (tempString[j] == '#');
	}

	tempBubbleCurrent.resize(32);
	for (int i = 0; i < 32; ++i)
		tempBubbleCurrent[i].resize(32);

	for (int i = 0; i < 32; ++i)
	{
		tempString = bubbleCurrentData[i].get<string>();
		for (int j = 0; j < 32; ++j)
			tempBubbleCurrent[i][j] = tempString[j];
	}

	tempMap.tileVector = tempTile;
	tempMap.bubbleCurrentVector = tempBubbleCurrent;
	tempMap.setTile(imageManager.getImages(themeData["tile"].get<string>()));
	tempMap.setBackground(imageManager.getImages(themeData["background"].get<string>()));

	Range r(0, 0, 320, 320);
	tempMap.platform = vectorToLines(tempTile, r);
	tempMap.wall.addLine(Line(Point(r.point0.x + 20, r.point0.y), Point(r.point0.x + 20, r.point1.y), Point(1, 0)));
	tempMap.wall.addLine(Line(Point(r.point1.x - 20, r.point0.y), Point(r.point1.x - 20, r.point1.y), Point(-1, 0)));
	tempMap.wall.addLine(Line(Point(r.point0.x + 20, r.point1.y), Point(r.point1.x - 20, r.point1.y), Point(0, -1)));

	initialSettings.push_back(tempInitialSetting);

	maps.push_back(tempMap);

}
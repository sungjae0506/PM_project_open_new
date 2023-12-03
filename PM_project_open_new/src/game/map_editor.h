#pragma once

#pragma once
#include <vector>
#include <queue>
#include <set>
#include <string>
#include "../UI/event.h"
#include "player.h"
#include "bubble.h"
#include "enemy.h"
#include "map.h"
#include "game_const.h"
#include <json.hpp>
#include <ctime>
#include "initial_setting.h"
#include "../asset/image_manager.h"
#include "enemy_AI.h"

using json = nlohmann::json;

class MapEditor
{
public:
	string mapName;

	int maxStage = 100;

	int currentStage = 0;

	enum {ModeTheme, ModeCharacter, ModeCurrent} mode;

	vector<bool> modeThemeButtonState;
	vector<bool> modeCharacterButtonState;
	vector<bool> modeCurrentButtonState;

	vector<bool> layerState;

	vector<Map> maps;
	vector<InitialSetting> initialSettings;

	void clear();
	void setStage(int s);
	
	void drawEntity(void);
	void drawMap();

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void draw(Point mousePos);

	void readMap(string path);
};
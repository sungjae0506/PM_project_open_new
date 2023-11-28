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
#include "../util/json.hpp"
#include <ctime>
#include "initial_setting.h"
#include "../asset/image_manager.h"

using json = nlohmann::json;

class GameManager
{
public:
	int mainTick;
	int internalTick;
	string state; // MapStarting, MapRunning, MapChanging, Stop(internalTick¿Ã ¡§¡ˆµ )

	int currentStage;
	Map currentMap;
	vector<Map> maps;
	vector<InitialSetting> initialSettings;
	InitialSetting prevSetting;
	
	vector<Player> players;
	vector<Bubble> bubbles;
	vector<Enemy> enemies;

	const int bubbleMax = 240;
	queue<int> bubbleResourceQueue;
	vector<bool> bubblePopVector;
	queue<int> bubblePopQueue;
	vector<vector<bool>> bubbleAdjVector;

	int playerNum;
	int playerCnt = 1; // test
	int enemyCnt = 1;  // test

	vector<Image> heartImage;
	

	void clear();
	
	void setState(string s);
	string getState(void);
	void changeState();
	void incTick(void);

	void begin(int n);

	void move();

	void drawEntity(void);
	void drawMap();
	void drawMap(double stage);
	void drawHeart(void);

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void idleEvent(IdleEvent e);
	void draw(Point mousePos);

	void readMap(string path);
};
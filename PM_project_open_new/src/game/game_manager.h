#pragma once
#include <vector>
#include "player.h"
#include "bubble.h"
#include "enemy.h"
#include "map.h"

class GameManager
{
public:
	int tick;
	string state;

	int currentStage;
	vector<string> mapPath;
	vector<Map> maps;
	Map currentMap;

	vector<Entity*> players;
	vector<Entity*> bubbles;
	vector<Entity*> enemies;

	void clear();
	void addPlayer(Entity* player);

	void stateChange();

	void clearMapPath(void);
	void addMapPath(string path);
	void loadMap(void);

	void move();

	void drawMap();
	void drawMapChange();

	void keyboardEvent();
	void idleEvent();
	void draw();

	
};
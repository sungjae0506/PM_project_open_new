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
#include "character.h"
#include "game_const.h"
#include <ctime>

class GameManager
{
public:
	int mainTick;
	int internalTick;
	string state; // MapStarting, MapRunning, MapChanging, Stop(internalTick¿Ã ¡§¡ˆµ )

	int currentStage;
	vector<Map> maps;
	vector<Character> characters;

	Map currentMap;
	vector<Player> players;
	vector<Bubble> bubbles;
	vector<Enemy> enemies;

	const int bubbleMax = 240;
	queue<int> bubbleResourceQueue;
	vector<bool> bubblePopVector;
	queue<int> bubblePopQueue;
	vector<vector<bool>> bubbleAdjVector;

	int playerNum;

	void clear();
	
	void setState(string s);
	string getState(void);
	void changeState();
	void incTick(void);

	void addMap(string path);
	void addCharacter(string path);

	void load(int n);

	void move();

	void drawEntity(void);
	void drawMap();
	void drawMap(double stage);

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void idleEvent(IdleEvent e);
	void draw(Point mousePos);

};
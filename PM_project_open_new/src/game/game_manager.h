#pragma once
#include <vector>
#include <string>
#include "../UI/event.h"
#include "player.h"
#include "bubble.h"
#include "enemy.h"
#include "map.h"
#include "character.h"
#include "game_const.h"

class GameManager
{
public:
	int mainTick;
	int internalTick;
	string state; // MapRunning, MapChanging, Stop

	int currentStage;
	vector<Map> maps;
	vector<Character> characters;

	Map currentMap;
	vector<Player> players;
	vector<Bubble> bubbles;
	vector<Enemy> enemies;

	int playerNum;

	void clear();
	
	void changeState();

	void addMap(string path);
	void addCharacter(string path);

	void load(int n);

	void move();

	void drawEntity();
	void drawMap();
	void drawMap(double stage);

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void idleEvent(IdleEvent e);
	void draw(Point mousePos);

};
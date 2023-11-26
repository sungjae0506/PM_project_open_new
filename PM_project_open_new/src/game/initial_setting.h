#pragma once
#include "../util/object.h"
#include <vector>
#include <string>

class InitialSetting
{
public:
	vector<Point> playerPos;
	vector<Point> enemyPos;
	vector<string> enemyName;

	InitialSetting();

	void clear();

	void addPlayerPos(const Point& p);
	void addEnemyPos(const Point& p);
	void addEnemyName(string s);
};
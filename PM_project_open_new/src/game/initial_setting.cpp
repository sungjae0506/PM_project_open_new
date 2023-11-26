#include "initial_setting.h"

InitialSetting::InitialSetting()
{
}

void InitialSetting::clear()
{
	playerPos.clear();
	enemyPos.clear();
	enemyName.clear();
}

void InitialSetting::addPlayerPos(const Point& p)
{
	playerPos.push_back(p);
}

void InitialSetting::addEnemyPos(const Point& p)
{
	enemyPos.push_back(p);
}

void InitialSetting::addEnemyName(string s)
{
	enemyName.push_back(s);
}
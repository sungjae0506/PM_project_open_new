#pragma once
#include <vector>
#include <string>
#include "../util/object.h"
#include "../game/player.h"
#include "../game/map.h"
using namespace std;

typedef pair<int, int> pii;

class EnemyAI
{
public:
	string mode;
	Point targetVel;

	EnemyAI();
	EnemyAI(string _mode);
	void setMode(string _mode);

	void enemyInit(Enemy& e);
	void pathfinding(Enemy& e, const vector<Player>& p, const Map& mp);
	
	
};
#pragma once
#include <vector>
#include "entity.h"
#include "player.h"
#include "bubble.h"
#include "enemy.h"
#include "game_const.h"

class Character
{
public:
	vector<Player> players;
	vector<Enemy> enemies;

	Character();
	Character(const Character& c);

	void readCharacter(string path);
};
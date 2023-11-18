#pragma once
#include "entity.h"

class Player : Entity
{
public:
	Lines hitBox;
	Player();
	Player(Point pos);
};

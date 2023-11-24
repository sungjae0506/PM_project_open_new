#pragma once
#include "entity.h"
#include "map.h"
#include "game_const.h"
#include "../util/material.h"

class Bubble : Entity
{
public:
	Circle hitBox; // 수평으로 갈 때 :r = 5.0, 수직으로 갈 때 : r = 10.0;
	bool mapCollisionState;
	double r1 = 5.0;
	double r2 = 10.0;

	Material mtl;

	Bubble();
	Bubble(Point pos, Point dir);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);

	virtual void setName(string s);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void);

	virtual void setState(string s);
	virtual string getState(void);
	virtual void changeState(void);
	virtual void incTick(void);

	void collisionHandling(const Map& mp);
};
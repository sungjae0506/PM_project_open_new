#pragma once
#pragma once
#include "entity.h"
#include "map.h"
#include "game_const.h"

class Projectile : Entity
{
public:
	Circle hitBox; // r = 8.0

	bool mapCollisionState = false;
	bool playerCollisionState = false;
	bool enemyCollisionState = false;
	
	double r = 8.0;

	Projectile();
	Projectile(Point pos, Point dir);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);
	virtual void setName(string s);
	void setImages(vector<Image>& images);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void) const;
	Point getVel(void) const;

	virtual void setState(string s);
	virtual string getState(void) const;
	virtual void changeState(void);
	virtual void incTick(void);

	void collisionHandling(const Map& mp);
};
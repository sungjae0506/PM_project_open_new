#pragma once
#include "entity.h"
#include "map.h"
#include "game_const.h"
#include "enemy.h"

class Bubble : Entity
{
public:
	Circle hitBox1; // �������� �� �� :r = 5.0, �������� �� �� : r = 10.0;
	Circle hitBox2;

	bool mapCollisionState = false;
	bool playerCollisionState = false;
	bool enemyCollisionState = false;
	
	Enemy* enemyPtr;

	double r1 = 5.0;
	double r2 = 10.0;

	Range bubbleCurrentRange;
	Point bubbleCurrentVel;
	Line platform;
	Lines wall;

	Bubble();
	Bubble(Point pos, Point dir);

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
	bool collisionDetection(const Bubble& b);
	void collisionHandling(Bubble& b);
	void collisionHandling(Enemy& e);
	void bubbleCurrentHandling(const Map& mp);

};
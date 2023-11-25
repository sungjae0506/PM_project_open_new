#pragma once
#include <string>
#include "../util/object.h"
#include "map.h"
using namespace std;

class Entity
{
public:
	int mainTick;
	int internalTick;

	Point pos;
	Point vel;
	Point acc;

	string name;
	string state;
	
	virtual void setPos(const Point& p) = 0;
	virtual void setVel(const Point& p) = 0;
	virtual void setAcc(const Point& p) = 0;
	virtual void setName(string s) = 0;

	virtual void draw(void) = 0;
	virtual void move(void) = 0;

	virtual void setState(string s) = 0;
	virtual string getState(void) const = 0;
	virtual void changeState(void) = 0;
	virtual void incTick(void) = 0;
	

	//virtual void changeState(void) = 0;
	//virtual void collisionDetection(const Entity* e) = 0;
	//virtual void collisionDetection(const Map& m) = 0;
};
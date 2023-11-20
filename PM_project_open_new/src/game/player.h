#pragma once
#include "entity.h"
#include "game_const.h"
#include "../util/object.h"
#include "map.h"

class Player : Entity
{
public:
	// state: "None", "Transparent", "MapChanging", "Killed"

	Lines hitBox;

	vector<Image> images;

	vector<bool> collisionState{ false, false, false, false }; // 상 하 좌 우
	vector<bool> keyboardState{ false, false, false, false, false }; // 상 하 좌 우 스페이스

	string dir;

	Player();
	Player(Point pos);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);

	virtual void setName(string s);
	virtual void setState(string s);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void);

	void setKeyboardState(int i, bool b);
	void updateKeyboardState(void);
	void collisionHandling(Map mp);

};

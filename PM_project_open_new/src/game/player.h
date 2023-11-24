#pragma once
#include "entity.h"
#include "game_const.h"
#include "../util/object.h"
#include "map.h"
#include "bubble.h"

class Player : Entity
{
public:
	// state: "None", "Collision", "Transparent", "MapChanging", "Killed"
	string bubbleState; // "BubbleAvailable", "BubbleUnavailable", "MakeBubble"
	int bubbleTick;

	int width;
	int height;
	Lines hitBox;

	vector<Image> images;

	bool enemyCollisionState;
	vector<bool> mapCollisionState{ false, false, false, false }; // 상 하 좌 우
	vector<bool> keyboardState{ false, false, false, false, false }; // 상 하 좌 우 스페이스

	string dir;

	Bubble bubble;

	Player();
	Player(Point pos);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);

	virtual void setName(string s);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void);

	void setKeyboardState(int i, bool b);
	void updateKeyboardState(void);
	void collisionHandling(const Map &mp);

	virtual void setState(string s);
	virtual string getState(void);
	virtual void changeState(void);
	virtual void incTick(void);

	void setBubbleState(string s);
	string getBubbleState(void);

	void setBubble(Bubble b);
	Bubble shootBubble(const Map& mp);

};

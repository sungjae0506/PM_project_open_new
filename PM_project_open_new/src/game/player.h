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
	string bubbleState; // "BubbleAvailable", "BubbleUnavailable", "ShootBubble"
	int bubbleTick;

	string pushState; // "None", "PushWall"
	int pushTick;

	int width;
	int height;
	Lines hitBox;

	vector<Image> images; //[��1, ��2, ��1, ��2, ����, �����̽���, ����]

	int HP;

	bool enemyCollisionState;
	vector<bool> mapCollisionState{ false, false, false, false }; // �� �� �� ��
	vector<bool> keyboardState{ false, false, false, false, false }; // �� �� �� �� �����̽�

	string dir;

	Bubble bubble;
	bool onBubble = false;

	bool pushWall;
	Point pushWallDir;

	Player();
	Player(Point pos);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);

	virtual void setName(string s);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void) const;
	Point getVel(void);

	void setKeyboardState(int i, bool b);
	void updateKeyboardState(void);

	void collisionHandling(const Map &mp);
	bool collisionDetection(const Bubble& b);
	bool collisionDetection(const Enemy& e);
	bool bubbleJumpDetection(const Bubble& b);
	void bubblePushHandling(Bubble& b);

	virtual void setState(string s);
	virtual string getState(void) const;
	virtual void changeState(void);
	virtual void incTick(void);

	void setBubbleState(string s);
	string getBubbleState(void);

	void setPushState(string s);
	string getPushState(void);

	void setBubble(Bubble b);
	Bubble shootBubble(const Map& mp);

};

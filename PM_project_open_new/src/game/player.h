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

	vector<Image> images; //[좌1, 좌2, 우1, 우2, 점프, 스페이스바, 정지]

	bool enemyCollisionState;
	vector<bool> mapCollisionState{ false, false, false, false }; // 상 하 좌 우
	vector<bool> keyboardState{ false, false, false, false, false }; // 상 하 좌 우 스페이스

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

	Point getPos(void);
	Point getVel(void);

	void setKeyboardState(int i, bool b);
	void updateKeyboardState(void);

	void collisionHandling(const Map &mp);
	bool collisionDetection(const Bubble& b);
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

#pragma once
#include "entity.h"
#include "game_const.h"
#include "../util/object.h"
#include "map.h"
#include "projectile.h"

class Enemy : Entity
{
public:
	// state: "None", "Collision", "Transparent", "MapChanging", "Killed"
	string projectileState; // "ProjectileAvailable", "ProjectileUnavailable", "MakeProjectile"
	int projectileTick;

	int width;
	int height;
	Lines hitBox;

	vector<Image> images; //[좌1, 좌2, 우1, 우2, 점프, 스페이스바, 정지]

	bool bubbleCollisionState = false;
	bool bubblePop = false;
	bool bubbleTimeout = false;
	vector<bool> mapCollisionState{ false, false, false, false }; // 상 하 좌 우
	vector<bool> keyboardState{ false, false, false, false, false }; // 상 하 좌 우 스페이스

	string dir;

	Projectile projectile;

	Enemy();
	Enemy(Point pos);

	virtual void setPos(const Point& p);
	virtual void setVel(const Point& p);
	virtual void setAcc(const Point& p);

	virtual void setName(string s);
	string getName(void);

	virtual void draw(void);
	virtual void move(void);

	Point getPos(void) const;
	Point getVel(void);

	void setKeyboardState(int i, bool b);
	void updateKeyboardState(void);

	void collisionHandling(const Map& mp);

	virtual void setState(string s);
	virtual string getState(void) const;
	virtual void changeState(void);
	virtual void incTick(void);

	void setProjectileState(string s);
	string getProjectileState(void);

	void setProjectile(Projectile p);
	Projectile shootProjectile(const Map& mp);
};

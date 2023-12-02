#include "enemy.h"

Enemy::Enemy()
{
	width = 16;
	height = 16;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // 상
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // 하
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // 좌
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // 우
	dir = "RIGHT";
	setState("None");
	setProjectileState("ProjectileAvailable");
}
Enemy::Enemy(Point _pos)
{
	pos = _pos;
	width = 16;
	height = 16;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // 상
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // 하
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // 좌
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // 우
	dir = "RIGHT";
	setState("None");
	setProjectileState("ProjectileAvailable");
}

void Enemy::setPos(const Point& p) {
	pos = p;
}
void Enemy::setVel(const Point& p)
{
	vel = p;
}
void Enemy::setAcc(const Point& p)
{
	acc = p;
}

void Enemy::setName(string s)
{
	name = s;
}

string Enemy::getName(void)
{
	return name;
}

void Enemy::setImages(vector<Image> _images)
{
	images = _images;
}


void Enemy::draw(void)
{
	//if (getState() != "Killed")
	//	(Image("image/bubble_bobble_enemy.png", Range(-8, -8, 8, 8)) + pos).draw();

	//if (getState() != "Killed")
	//	(images[0] + pos).draw();
	string st = getState();
	if (st == "None")
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (dir == "LEFT")
		{
			if (vel.y > EPSILON && (name == "enemy1" || name == "enemy2"))
			{
				(images[2] + pos).draw();
			}
			else
			{
				(images[1] + pos).draw();
			}
		}
		else if (dir == "RIGHT")
		{
			if (vel.y > EPSILON && (name == "enemy1" || name == "enemy2"))
			{
				(images[2].horizontalFlip() + pos).draw();
			}
			else
			{
				(images[1].horizontalFlip() + pos).draw();
			}
		}
		else
		{
			(images[0] + pos).draw();
		}
	}
	else if (st == "InBubble")
	{
		(images[0] + pos).draw();
	}
	glDisable(GL_BLEND);

	// test
	//auto tmp = (hitBox + pos);
	//tmp.print();
	
	//printf("%lf %lf\n", pos.x, pos.y);

	//(Image("image/snu.png", Range(-10, -10, 10, 10)) + pos).draw();

	/*if (keyboardState[4]) {
		images[5].draw();
	}

	else {
		int start, end;
		bool walk = false;
		start = internalTick;

		if (keyboardState[0] || keyboardState[2] || keyboardState[3]) {

			end = internalTick;

			if ((end - start) > 3) {
				walk != walk;
			}

			if (dir == "LEFT") {
				images[walk ? 0 : 1].draw();
			}
			else if (dir == "RIGHT") {
				images[walk ? 2 : 3].draw();
			}
			else if (keyboardState[0]) {
				images[4].draw();
			}

			start = internalTick;
		}
		else {
			images[6].draw();
		}
	}*/
}
void Enemy::move(void)
{
	if (vel.x < -EPSILON)
		dir = "LEFT";
	if (vel.x > EPSILON)
		dir = "RIGHT";
	if (getState() == "Killed")
	{
		pos(0, 0);
		vel(0, 0);
	}
	if (getState() == "InBubble")
	{
		vel(0, 0);
	}
	if (getState() == "None")
	{
		pos += vel / idlePerSecond;
		vel += acc / idlePerSecond;
		if (vel.y < -playerFallingVelLimit)
			vel.y = -playerFallingVelLimit;
		if (pos.y < 0.0)
			pos.y = 320.0;
	}
}

Point Enemy::getPos(void) const
{
	return pos;
}

Point Enemy::getVel(void)
{
	return vel;
}


void Enemy::setKeyboardState(int i, bool b)
{
	keyboardState[i] = b;
}

void Enemy::updateKeyboardState(void)
{
	
	if (keyboardState[2] == false && keyboardState[3] == true)
	{
		dir = "RIGHT";
		vel = Point(playerHorizontalVel, vel.y);
	}
	else if (keyboardState[2] == true && keyboardState[3] == false)
	{
		dir = "LEFT";
		vel = Point(-playerHorizontalVel, vel.y);
	}
	else
	{
		vel = Point(0.0, vel.y);
	}

	if (keyboardState[0] == true && mapCollisionState[1] == true && vel.y < EPSILON)
	{
		vel = Point(vel.x, playerJumpVel);
	}
}

void Enemy::collisionHandling(const Map& mp)
{
	if (mapTransparent)
		return;

	bool isCol = true;
	Lines platform = mp.platform;
	Lines wall = mp.wall;

	auto res1 = (hitBox + pos).collisionDetection(platform);
	auto res2 = (hitBox + pos).collisionDetection(wall);

	for (int i = 0; i < 4; ++i)
		mapCollisionState[i] = false;

	for (int i = 2; i < 4; ++i)
	{
		isCol = false;
		for (auto& j : res1[i])
			if (j.first == Sliding)
				isCol = true;
		if (isCol)
			mapCollisionState[i] = true;

		isCol = true;
		if (res2[i].size() == 0)
			isCol = false;
		for (auto& j : res2[i])
			if (j.first != Sliding)
				isCol = false;
		if (isCol)
			mapCollisionState[i] = true;
	}

	for (int i = 2; i < 4; ++i)
	{
		if (vel * hitBox.line[i].norm < EPSILON || mapCollisionState[i] == false)
			continue;

		for (auto& j : res1[i])
		{
			if (hitBox.line[i].norm * j.second.norm < -1.0 + EPSILON)
			{
				pos += (hitBox + pos).line[i].norm * ((hitBox + pos).line[i].norm * (((j.second.point0 + j.second.point1) / 2.0) - (((hitBox + pos).line[i].point0 + (hitBox + pos).line[i].point1) / 2.0)));
				vel -= hitBox.line[i].norm * (hitBox.line[i].norm * vel);
				break;
			}
		}

		for (auto& j : res2[i])
		{
			if (hitBox.line[i].norm * j.second.norm < -1.0 + EPSILON)
			{
				pos += (hitBox + pos).line[i].norm * ((hitBox + pos).line[i].norm * (((j.second.point0 + j.second.point1) / 2.0) - (((hitBox + pos).line[i].point0 + (hitBox + pos).line[i].point1) / 2.0)));
				vel -= hitBox.line[i].norm * (hitBox.line[i].norm * vel);
				break;
			}
		}
	}

	res1 = (hitBox + pos).collisionDetection(platform);

	for (int i = 0; i < 2; ++i) // 수정함. (i : 1 -> 0)
	{
		isCol = true;
		if (res1[i].size() == 0)
			isCol = false;
		for (auto& j : res1[i])
			if (j.first != Sliding)
				isCol = false;
		if (isCol)
			mapCollisionState[i] = true;

		isCol = true;
		if (res2[i].size() == 0)
			isCol = false;
		for (auto& j : res2[i])
			if (j.first != Sliding)
				isCol = false;
		if (isCol)
			mapCollisionState[i] = true;
	}

	for (int i = 1; i < 2; ++i)
	{
		if (vel * hitBox.line[i].norm < EPSILON || mapCollisionState[i] == false)
			continue;

		for (auto& j : res1[i])
		{
			if (hitBox.line[i].norm * j.second.norm < -1.0 + EPSILON)
			{
				pos += (hitBox + pos).line[i].norm * ((hitBox + pos).line[i].norm * (((j.second.point0 + j.second.point1) / 2.0) - (((hitBox + pos).line[i].point0 + (hitBox + pos).line[i].point1) / 2.0)));
				vel -= hitBox.line[i].norm * (hitBox.line[i].norm * vel);
				break;
			}
		}
	}


}

void Enemy::setState(string s)
{
	state = s;
	internalTick = 0;
}


string Enemy::getState(void) const
{
	return state;
}

void Enemy::changeState(void)
{
	if (getState() == "None")
	{
		if (bubbleCollisionState)
		{
			setState("InBubble");
		}
	}
	else if (getState() == "InBubble")
	{
		if (bubblePop)
		{
			printf("kiilled");
			setState("Killed");
		}
		else if (bubbleTimeout)
		{
			setState("None");
		}
	}

	if (getProjectileState() == "ProjectileAvailable")
	{
		if (keyboardState[4] == true)
			setProjectileState("ShootProjectile");
	}
	else if (getProjectileState() == "ShootProjectile")
	{
		setProjectileState("ProjectileUnavailable");
	}
	else if (getProjectileState() == "ProjectileUnavailable")
	{
		if (projectileTick >= 30 || keyboardState[4] == false)
		{
			setProjectileState("ProjectileAvailable");
		}
	}

}

void Enemy::incTick(void)
{
	++mainTick;
	if (state != "Stop")
		++internalTick;
	++projectileTick;
}

void Enemy::setProjectileState(string s)
{
	projectileState = s;
	projectileTick = 0;
}
string Enemy::getProjectileState(void)
{
	return projectileState;
}

void Enemy::setProjectile(Projectile b)
{
	//bubble = b;
}

Projectile Enemy::shootProjectile(const Map& mp)
{
	Line closestLine;
	double minDist = 1e9, tempDist;


	if (dir == "LEFT")
	{
		closestLine = mp.wall.line[0];
		minDist = dist(mp.wall.line[0], pos);

		for (auto& i : mp.platform.line)
		{
			tempDist = dist(i, pos);
			if (i.norm * Point(1, 0) > EPSILON && tempDist > width / 2 - COLLISION_EPSILON && tempDist < minDist)
			{
				if (!((i.point0.y < pos.y - height / 2 + COLLISION_EPSILON && i.point1.y < pos.y - height / 2 + COLLISION_EPSILON) || (i.point0.y > pos.y + height / 2 - COLLISION_EPSILON && i.point1.y > pos.y + height / 2 - COLLISION_EPSILON)))
				{
					closestLine = i;
					minDist = tempDist;
				}
			}
		}

		if (minDist > (width / 2 + projectile.r * 2) + COLLISION_EPSILON) ///////////////////////////////////////////
		{
			projectile.setState("Horizontal");
			projectile.setPos(pos + Point(-width / 2 - projectile.r - 1.5 * COLLISION_EPSILON, 0));
			projectile.setVel(Point(-bubbleHorizontalVel, 0));
		}
	}
	else if (dir == "RIGHT")
	{
		closestLine = mp.wall.line[1];
		minDist = dist(mp.wall.line[1], pos);

		for (auto& i : mp.platform.line)
		{
			tempDist = dist(i, pos);
			if (i.norm * Point(-1, 0) > EPSILON && tempDist > width / 2 - COLLISION_EPSILON && tempDist < minDist)
			{
				if (!((i.point0.y < pos.y - height / 2 + COLLISION_EPSILON && i.point1.y < pos.y - height / 2 + COLLISION_EPSILON) || (i.point0.y > pos.y + height / 2 - COLLISION_EPSILON && i.point1.y > pos.y + height / 2 - COLLISION_EPSILON)))
				{
					closestLine = i;
					minDist = tempDist;
				}
			}
		}

		if (minDist > (width / 2 + projectile.r * 2) + COLLISION_EPSILON)
		{
			projectile.setState("Horizontal");
			projectile.setPos(pos + Point(width / 2 + projectile.r + 1.5 * COLLISION_EPSILON, 0));
			projectile.setVel(Point(bubbleHorizontalVel, 0));

		}
	}
	return projectile;
}

int Enemy::getMainTick(void)
{
	return mainTick;
}
#include "player.h"

Player::Player()
{
	width = 16;
	height = 20;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // ╩С
	hitBox.addLine(Line(Point(-width / 2 , -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // го
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // аб
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // ©Л
	dir = "RIGHT";
	setState("None");
	setBubbleState("BubbleAvailable");
}
Player::Player(Point _pos)
{
	pos = _pos;
	width = 16;
	height = 20;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // ╩С
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // го
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // аб
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // ©Л
	dir = "RIGHT";
	setState("None");
	setBubbleState("BubbleAvailable");
}

void Player::setPos(const Point& p) {
	pos = p;
}
void Player::setVel(const Point& p)
{
	vel = p;
}
void Player::setAcc(const Point& p)
{
	acc = p;
}

void Player::setName(string s)
{
	name = s;
}



void Player::draw(int& internalTick)
{
	// test
	auto tmp = (hitBox + pos);
	tmp.print();

	//(Image("image/snu.png", Range(-10, -10, 10, 10)) + pos).draw();
	
	if (keyboardState[4]) {
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
	}
}
void Player::move(void)
{
	pos += vel / idlePerSecond;
	vel += acc / idlePerSecond;
	if (vel.y < -playerFallingVelLimit)
		vel.y = -playerFallingVelLimit;
	if (pos.y < 0.0)
		pos.y = 320.0;
}

Point Player::getPos(void)
{
	return pos;
}

void Player::setKeyboardState(int i, bool b)
{
	keyboardState[i] = b;
}

void Player::updateKeyboardState(void)
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

void Player::collisionHandling(const Map &mp)
{
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

		for (auto &j : res2[i])
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

	for (int i = 1; i < 2; ++i)
	{
		isCol = true;
		if (res1[i].size() == 0)
			isCol = false;
		for (auto& j : res1[i])
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

	//printf("%d %d %d %d\n", (int)collisionState[0], (int)collisionState[1], (int)collisionState[2], (int)collisionState[3]);
}

void Player::setState(string s)
{
	state = s;
	internalTick = 0;
}


string Player::getState(void)
{
	return state;
}

void Player::changeState(void)
{


	if (getBubbleState() == "BubbleAvailable")
	{
		if (keyboardState[4] == true)
			setBubbleState("ShootBubble");
	}
	else if (getBubbleState() == "ShootBubble")
	{
		setBubbleState("BubbleUnavailable");
	}
	else if (getBubbleState() == "BubbleUnavailable")
	{
		if (bubbleTick >= 30 || keyboardState[4] == false)
		{
			setBubbleState("BubbleAvailable");
		}
	}
}

void Player::incTick(void)
{
	++mainTick;
	if (state != "Stop")
		++internalTick;
	++bubbleTick;
}

void Player::setBubbleState(string s)
{
	bubbleState = s;
	bubbleTick = 0;
}
string Player::getBubbleState(void)
{
	return bubbleState;
}

void Player::setBubble(Bubble b)
{
	//bubble = b;
}

Bubble Player::shootBubble(const Map &mp)
{
	// bubble test

	bubble.mtl.setAmbient(0, 1, 0, 0.5);
	bubble.mtl.setDiffuse(0, 1, 0, 0.5);
	bubble.mtl.setEmission(0, 1, 0, 0.5);
	bubble.mtl.setSpecular(0, 1, 0, 0.5);
	bubble.mtl.setShininess(10);

	//////////////

	if (dir == "LEFT")
	{
		//if (pos.x < )


		bubble.setPos(pos + Point(-width / 2 - bubble.r1 - 1.5 * COLLISION_EPSILON, 0));
		bubble.setVel(Point(-bubbleHorizontalVel, 0));
	}
	else if (dir == "RIGHT")
	{
		bubble.setPos(pos + Point(width / 2 + bubble.r1 + 1.5 * COLLISION_EPSILON, 0));
		bubble.setVel(Point(bubbleHorizontalVel, 0));
	}
	return bubble;
}
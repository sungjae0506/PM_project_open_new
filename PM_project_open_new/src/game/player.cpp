#include "player.h"

Player::Player()
{
	hitBox.addLine(Line(Point(-10, 10), Point(10, 10), Point(0, 1)));  // ╩С
	hitBox.addLine(Line(Point(-10, -10), Point(10, -10), Point(0, -1))); // го
	hitBox.addLine(Line(Point(-10, -10), Point(-10, 10), Point(-1, 0))); // аб
	hitBox.addLine(Line(Point(10, -10), Point(10, 10), Point(1, 0)));  // ©Л
}
Player::Player(Point _pos)
{
	pos = _pos;
	hitBox.addLine(Line(Point(-10, 10),  Point(10, 10),  Point(0, 1)));  // ╩С
	hitBox.addLine(Line(Point(-10, -10), Point(10, -10), Point(0, -1))); // го
	hitBox.addLine(Line(Point(-10, -10), Point(-10, 10), Point(-1, 0))); // аб
	hitBox.addLine(Line(Point(10, -10),  Point(10, 10),  Point(1, 0)));  // ©Л
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
void Player::setState(string s)
{
	state = s;
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

	if (keyboardState[0] == true && collisionState[1] == true && vel.y < EPSILON)
	{
		vel = Point(vel.x, playerJumpVel);
	}
}

void Player::collisionHandling(Map mp)
{
	bool isCol = true;
	Lines platform = mp.platform;
	Lines wall = mp.wall;
	auto res1 = (hitBox + pos).collisionDetection(platform);
	auto res2 = (hitBox + pos).collisionDetection(wall);

	/**for (int i = 2; i < 4; ++i)
	{
		for (auto& j : res1[i])
		{
			if (j.first == None)
			{
				cout << "None ";
			}
			else if (j.first == Sliding)
			{
				cout << "Sl";
			}
			
		}
		cout << endl;
	}
	cout << endl;*/

	for (int i = 0; i < 4; ++i)
		collisionState[i] = false;

	for (int i = 1; i < 4; ++i)
	{
		isCol = true;
		if (res1[i].size() == 0)
			isCol = false;
		for (auto& j : res1[i])
			if (j.first != Sliding)
				isCol = false;
		if (isCol)
			collisionState[i] = true;

		if (res2[i].size() == 0)
			isCol = false;
		for (auto& j : res2[i])
			if (j.first != Sliding)
				isCol = false;
		if (isCol)
			collisionState[i] = true;
	}

	for (int i = 1; i < 4; ++i)
	{
		if (vel * hitBox.line[i].norm < EPSILON || collisionState[i] == false)
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
}
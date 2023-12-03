#include "player.h"
#include "../asset/sound_loader.h"

Player::Player()
{
	width = 16;
	height = 16;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // 상
	hitBox.addLine(Line(Point(-width / 2 , -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // 하
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // 좌
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // 우
	HP = playerInitialHP;
	dir = "RIGHT";
	setState("None");
	setBubbleState("BubbleAvailable");
	setPushState("None");
}
Player::Player(Point _pos)
{
	pos = _pos;
	width = 16;
	height = 16;
	hitBox.addLine(Line(Point(-width / 2, height / 2), Point(width / 2, height / 2), Point(0, 1)));  // 상
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(width / 2, -height / 2), Point(0, -1))); // 하
	hitBox.addLine(Line(Point(-width / 2, -height / 2), Point(-width / 2, height / 2), Point(-1, 0))); // 좌
	hitBox.addLine(Line(Point(width / 2, -height / 2), Point(width / 2, height / 2), Point(1, 0)));  // 우
	HP = playerInitialHP;
	dir = "RIGHT";
	setState("None");
	setBubbleState("BubbleAvailable");
	setPushState("None");
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

void Player:: setImages(vector<Image> _images)
{
	images = _images;
}



void Player::draw(void)
{
	string st = getState();
	if (st == "None" || st == "EnemyCollision")
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (dir == "LEFT")
		{
			if (vel.y > EPSILON)
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
			if (vel.y > EPSILON)
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
	else if (st == "Transparent")
	{
		if ((internalTick / 20) % 2 == 0)
		{
			if (dir == "LEFT")
			{
				if (vel.y > EPSILON)
				{
					(images[2] + pos).draw();
				}
				else
				{
					(images[1] + pos).draw();
				}
			}
			else
			{
				if (vel.y > EPSILON)
				{
					(images[2].horizontalFlip() + pos).draw();
				}
				else
				{
					(images[1].horizontalFlip() + pos).draw();
				}
			}
		}
	}
	glDisable(GL_BLEND);
	// test
	//auto tmp = (hitBox + pos);
	//tmp.print();
	
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
void Player::move(void)
{
	if (getState() == "Killed")
	{
		pos(0, 0);
		vel(0, 0);
		acc(0, 0);
		return;
	}

	pos += vel / idlePerSecond;
	vel += acc / idlePerSecond;
	if (vel.y < -playerFallingVelLimit)
		vel.y = -playerFallingVelLimit;
	if (pos.y < 0.0)
		pos.y = 320.0;

	if (getPushState() == "PushWall")
	{
		pos += pushWallDir * (pushWallDist / pushWallTick);
	}
}

Point Player::getPos(void) const
{
	return pos;
}

Point Player::getVel(void)
{
	return vel;
}

void Player::setKeyboardState(int i, bool b)
{
	keyboardState[i] = b;
}


SoundContainer jumpSound;
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

	if (keyboardState[0] == true && (mapCollisionState[1] == true || onBubble) && vel.y < EPSILON)
	{
		vel = Point(vel.x, playerJumpVel);
		jumpSound.addsound("sound/jump.wav");
		jumpSound.playsound();
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

bool Player::collisionDetection(const Bubble& b)
{
	string st = b.getState();
	if (st == "Vertical" || st == "ContainEnemy")
	{
		auto res = (hitBox + pos).collisionDetection((b.hitBox2 + b.getPos()));
		for (auto i : res)
			if (i != None)
				return true;
	}
	return false;
}

bool Player::collisionDetection(const Enemy& e)
{
	string st = e.getState();
	if (st == "None")
	{
		auto res = (hitBox + pos).collisionDetection(e.hitBox + e.getPos());
		for (auto& i : res)
			if (i.size() != 0)
				return true;
	}
	return false;
}

bool Player::bubbleJumpDetection(const Bubble& b)
{
	return ((hitBox.line[1] + pos).collisionDetection(b.platform + b.getPos()) == Sliding);
}

void Player::bubblePushHandling(Bubble& b)
{
	Point deltaVel, delta;
	deltaVel = b.getVel() - vel;
	if (abs(deltaVel.y) < 50.0 && (b.getState() == "Vertical" || b.getState() == "ContaionEnemy"))
	{
		//printf("can push!");
		auto res = (hitBox + pos).collisionDetection(b.wall + b.getPos());
		if (dir == "LEFT" && res[2].size() != 0)
		{
			if (res[2][0].first == Sliding && (pos.y - 5.0 - COLLISION_EPSILON * 0.1 <= b.getPos().y&& b.getPos().y <= pos.y + 5.0 + COLLISION_EPSILON * 0.1))
			{
				
				delta = (deltaVel * Point(-1, 0)) * Point(-1, 0) / idlePerSecond;
				pos += delta * 0.235;
				b.setPos(b.getPos() - delta * 0.735);
			}
		}
		if (dir == "RIGHT" && res[3].size() != 0)
		{
			if (res[3][0].first == Sliding && (pos.y - 5.0 - COLLISION_EPSILON * 0.1 <= b.getPos().y && b.getPos().y <= pos.y + 5.0 + COLLISION_EPSILON * 0.1))
			{
				delta = (deltaVel * Point(1, 0)) * Point(1, 0) / idlePerSecond;
				pos += delta * 0.235;
				b.setPos(b.getPos() - delta * 0.735);
			}
		}
	}
}

void Player::setState(string s)
{
	state = s;
	internalTick = 0;
}


string Player::getState(void) const
{
	return state;
}

void Player::changeState(void)
{
	if (getState() == "None")
	{
		if (enemyCollisionState)
		{
			setState("EnemyCollision");
		}
	}
	else if (getState() == "EnemyCollision")
	{
		if (HP != 0)
		{
			setState("Transparent");
		}
		else
		{
			setState("Killed");
		}
	}
	else if (getState() == "Transparent")
	{
		if (internalTick >= 300)
		{
			setState("None");
		}
	}


	if (getBubbleState() == "BubbleAvailable")
	{
		if (keyboardState[4] == true && getState() == "None")
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

	if (getPushState() == "None")
	{
		if (pushWall && !(pushWallDir.x < -EPSILON && mapCollisionState[2]) && !(pushWallDir.x > EPSILON && mapCollisionState[3]))
		{
			setPushState("PushWall");
		}
	}
	else if (getPushState() == "PushWall")
	{
		if (pushTick >= pushWallTick || (pushWallDir.x < -EPSILON && mapCollisionState[2]) || (pushWallDir.x > EPSILON && mapCollisionState[3]))
		{
			setPushState("None");
		}
		if (pushWall)
		{
			setPushState("PushWall");
		}
	}
}

void Player::incTick(void)
{
	++mainTick;
	if (state != "Stop")
		++internalTick;
	++bubbleTick;
	++pushTick;
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

void Player::setPushState(string s)
{
	pushState = s;
	pushTick = 0;
}

string Player::getPushState(void)
{
	return pushState;
}

void Player::setBubble(Bubble b)
{
	//bubble = b;
}

Bubble Player::shootBubble(const Map &mp)
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
				if (!((i.point0.y < pos.y - height / 2 + COLLISION_EPSILON && i.point1.y < pos.y - height / 2 + COLLISION_EPSILON) || (i.point0.y > pos.y + height / 2 - COLLISION_EPSILON  && i.point1.y > pos.y + height / 2 - COLLISION_EPSILON)))
				{
					closestLine = i;
					minDist = tempDist;
				}
			}
		}

		if (minDist < (width / 2 + bubble.r2 * 2) + COLLISION_EPSILON)
		{
			bubble.setState("Pop");
			bubble.setPos(pos + (bubble.r2 - minDist) * closestLine.norm);
			bubble.setVel(Point(0, 0));
			//pos += Point(4, 0);

			pushWall = true;
			pushWallDir = Point(1, 0);
		}
		else
		{
			bubble.setState("Horizontal");
			bubble.setPos(pos + Point(-width / 2 - bubble.r1 - 1.5 * COLLISION_EPSILON, 0));
			bubble.setVel(Point(-bubbleHorizontalVel, 0));
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

		if (minDist < (width / 2 + bubble.r2 * 2) + COLLISION_EPSILON)
		{
			bubble.setState("Pop");
			bubble.setPos(pos + (bubble.r2 - minDist) * closestLine.norm);
			bubble.setVel(Point(0, 0));
			//pos += Point(-4, 0);
			
			pushWall = true;
			pushWallDir = Point(-1, 0);
		}
		else
		{
			bubble.setState("Horizontal");
			bubble.setPos(pos + Point(width / 2 + bubble.r1 + 1.5 * COLLISION_EPSILON, 0));
			bubble.setVel(Point(bubbleHorizontalVel, 0));
			
		}
	}
	return bubble;
}
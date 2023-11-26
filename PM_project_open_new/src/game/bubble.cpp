#include "bubble.h"

Bubble::Bubble()
{
	hitBox1.center(0.0, 0.0);
	hitBox2.center(0.0, 0.0);
	hitBox1.radius = r1;
	hitBox2.radius = r2;

	platform = Line(Point(-r2, r2 + COLLISION_EPSILON), Point(r2, r2 + COLLISION_EPSILON), Point(0, 1));

	wall.addLine(Line(Point(-r2 - COLLISION_EPSILON, -r2 / 2), Point(-r2 - COLLISION_EPSILON, r2 / 2), Point(-1, 0)));
	wall.addLine(Line(Point(r2 + COLLISION_EPSILON, -r2 / 2), Point(r2 + COLLISION_EPSILON, r2 / 2), Point(1, 0)));

	mainTick = 0;
	internalTick = 0;
	mapCollisionState = false;
	state = "Horizontal";
}
Bubble::Bubble(Point _pos, Point _dir)
{
	pos = _pos;

	hitBox1.center(0.0, 0.0);
	hitBox2.center(0.0, 0.0);
	hitBox1.radius = r1;
	hitBox2.radius = r2;

	platform.point0 = Point(-r2, r2 + COLLISION_EPSILON);
	platform.point1 = Point(r2, r2 + COLLISION_EPSILON);
	platform.norm = Point(0, 1);

	mainTick = 0;
	internalTick = 0;
	mapCollisionState = false;
	state = "Horizontal";
}

void Bubble::setPos(const Point& p) {
	pos = p;
}
void Bubble::setVel(const Point& p)
{
	vel = p;
}
void Bubble::setAcc(const Point& p)
{
	acc = p;
}

void Bubble::setName(string s)
{
	name = s;
}

void Bubble::setImages(vector<Image>& images)
{

}

void Bubble::draw(void)
{
	string st = getState();
	if (st == "Killed")
		return;

	if (st == "Pop")
	{
		Image("image/pop.png", Range(-10, -10, 10, 10) + pos).draw();
		return;
	}

	double size;
	if (st == "Horizontal")
	{
		size = hitBox1.radius * (internalTick / 60.0 + 0.5);
	}
	else
	{
		size = hitBox2.radius;
	}

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.0);
	glutSolidSphere(size, 20, 20);
	glPopMatrix();
}

void Bubble::move(void)
{
	string st = getState();
	if (st == "Killed")
	{
		pos(0, 0);
		return;
	}
	if (st == "Vertical")
	{
		vel = airCurrentVel;
	}
	if (st != "Pop")
	{
		pos += vel / idlePerSecond;
		vel += acc / idlePerSecond;
	}
}

Point Bubble::getPos(void) const
{
	return pos;
}

Point Bubble::getVel(void) const
{
	return vel;
}

void Bubble::setState(string s)
{
	state = s;
	internalTick = 0;
}

string Bubble::getState(void) const
{
	return state;
}

void Bubble::changeState(void)
{
	string st = getState();
	if (st == "Horizontal")
	{
		if (mapCollisionState || internalTick >= 30)
		{
			setState("Vertical");
		}
		else if (enemyCollisionState)
		{
			setState("ContainEnemy");
		}
	}
	else if (st == "Vertical")
	{
		if (playerCollisionState || internalTick >= 3000)
		{
			setState("Pop");
		}
	}
	else if (st == "Pop")
	{
		if (internalTick >= 20)
		{
			setState("Killed");
		}
	}
	else if (st == "ContainEnemy")
	{
		if (internalTick >= 5000)
		{
			setState("MakeEnemy");
		}
		else if (playerCollisionState)
		{
			setState("KillEnemy");
		}
	}
	else if (st == "MakeEnemy")
	{
		setState("Pop");
	}
	else if (st == "KillEnemy")
	{
		setState("Pop");
	}
}

void Bubble::incTick(void)
{
	++mainTick;
	if (state != "Stop")
		++internalTick;
}

void Bubble::collisionHandling(const Map &mp)
{
	//cout << getState() << endl;
	if (getState() == "Horizontal")
	{
		auto res1 = mp.wall.collisionDetection(hitBox1 + pos);
		auto res2 = mp.platform.collisionDetection(hitBox1 + pos);

		mapCollisionState = false;

		for (int i = 0; i < res1.size(); ++i)
		{
			
			if ((res1[i] == Sliding || res1[i] == Crossing || res1[i] == In) && mp.wall.line[i].norm * vel < -EPSILON)
			{
				
				mapCollisionState = true;
				pos += mp.wall.line[i].norm * (r2 - (mp.wall.line[i].norm * (pos - mp.wall.line[i].point0)));
				return;
			}
		}

		for (int i = 0; i < res2.size(); ++i)
		{

			if ((res2[i] == Sliding || res2[i] == Crossing || res2[i] == In) && mp.platform.line[i].norm * vel < -EPSILON)
			{

				mapCollisionState = true;
				pos += mp.platform.line[i].norm * (r2 - (mp.platform.line[i].norm * (pos - mp.platform.line[i].point0)));
				return;
			}
		}
	}
}

bool Bubble::collisionDetection(const Bubble& b)
{
	return ((hitBox2 + pos).collisionDetection(b.hitBox2 + b.pos) != None);
}

void Bubble::collisionHandling(Bubble& b)
{
	auto dir = b.pos - pos;
	double dist = abs(b.pos - pos);

	if (abs(dir) > COLLISION_EPSILON && dist <= (2 * r2) * 0.8)
	{
		auto delta = (bubbleCollisionConst * dir / dist) / dist / dist;
		pos -= delta;
		b.pos += delta;
		
		vel -= delta * idlePerSecond * 0.985;
		b.vel += delta * idlePerSecond * 0.985;
	}
}

void Bubble::airCurrentHandling(const Map& mp)
{
	string st = getState();
	if (st == "Vertical" || st == "ContainEnemy")
	{
		if (!airCurrentRange.contain(pos))
		{
			int px = (int)(pos.x / 10), py = (int)(pos.y / 10), i, j;
			airCurrentRange = Range(-10, -10, 10, 10) + Point(px * 10 + 5, py * 10 + 5);
			i = 31 - py;
			j = px;
			if (i < 0)
				i = 0;
			if (i >= 32)
				i = 31;
			if (j < 0)
				j = 0;
			if (j >= 32)
				j = 31;
			switch (mp.airCurrentVector[i][j])
			{
			case 'D':
				airCurrentVel(0, -bubbleVerticalVel);
				break;
			case 'L':
				airCurrentVel(-bubbleVerticalVel, 0);
				break;
			case 'R':
				airCurrentVel(bubbleVerticalVel, 0);
				break;
			default:
				airCurrentVel(0, bubbleVerticalVel);
				break;
			}
		}
	}
}
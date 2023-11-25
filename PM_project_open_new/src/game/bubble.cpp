#include "bubble.h"

Bubble::Bubble()
{
	hitBox1.center(0.0, 0.0);
	hitBox2.center(0.0, 0.0);
	hitBox1.radius = r1;
	hitBox2.radius = r2;

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
		vel(0, bubbleVerticalVel);
	}
	if (st != "Pop" && st != "Killed")
	{
		pos += vel / idlePerSecond;
		vel += acc / idlePerSecond;
	}
}

Point Bubble::getPos(void) const
{
	return pos;
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
		Lines wall = mp.wall;

		auto res = wall.collisionDetection(hitBox2 + pos);

		mapCollisionState = false;

		for (int i = 0; i < res.size(); ++i)
		{
			
			if (res[i] == Sliding || res[i] == Crossing || res[i] == In)
			{
				
				mapCollisionState = true;
				pos += wall.line[i].norm * (r2 - (wall.line[i].norm * (pos - wall.line[i].point0)));
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
	}
}

void Bubble::airCurrentHandling(const Map& mp)
{
	string st = getState();
	if (st == "Vertical" || st == "ContainEnemy")
	{
		int i, j;
		char c;
		i = (int)(pos.y / 10);
		j = 31 - (int)(pos.x / 10);
		if (i < 0)
			i = 0;
		if (i >= 32)
			i = 31;
		if (j < 0)
			j = 0;
		if (j >= 32)
			j = 31;
		c = mp.airCurrentVector[i][j];
		switch (c)
		{
		case 'D':
			vel(0, -bubbleVerticalVel);
			break;
		}
	}
}
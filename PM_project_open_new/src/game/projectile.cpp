#include "projectile.h"

Projectile::Projectile()
{
	hitBox.center(0.0, 0.0);
	hitBox.radius = r;

	mainTick = 0;
	internalTick = 0;
	mapCollisionState = false;
	state = "None";
}
Projectile::Projectile(Point _pos, Point _dir)
{
	pos = _pos;

	hitBox.center(0.0, 0.0);
	hitBox.radius = r;

	mainTick = 0;
	internalTick = 0;
	mapCollisionState = false;
	state = "None";
}

void Projectile::setPos(const Point& p) {
	pos = p;
}
void Projectile::setVel(const Point& p)
{
	vel = p;
}
void Projectile::setAcc(const Point& p)
{
	acc = p;
}

void Projectile::setName(string s)
{
	name = s;
}

void Projectile::setImages(vector<Image>& images)
{

}

void Projectile::draw(void)
{
	string st = getState();
	if (st == "Killed")
		return;

	double size = r;

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.0);
	glutSolidSphere(size, 20, 20);
	glPopMatrix();
}

void Projectile::move(void)
{
	string st = getState();
	if (st == "Killed")
	{
		pos(0, 0);
		return;
	}
	pos += vel / idlePerSecond;
	vel += acc / idlePerSecond;
}

Point Projectile::getPos(void) const
{
	return pos;
}

Point Projectile::getVel(void) const
{
	return vel;
}

void Projectile::setState(string s)
{
	state = s;
	internalTick = 0;
}

string Projectile::getState(void) const
{
	return state;
}

void Projectile::changeState(void)
{
	string st = getState();
	if (st == "None")
	{
		if (mapCollisionState)
		{
			setState("Killed");
		}
	}
}

void Projectile::incTick(void)
{
	++mainTick;
	if (state != "Stop")
		++internalTick;
}

void Projectile::collisionHandling(const Map& mp)
{
	if (getState() == "Horizontal")
	{
		auto res1 = mp.wall.collisionDetection(hitBox + pos);
		auto res2 = mp.platform.collisionDetection(hitBox + pos);

		mapCollisionState = false;

		for (int i = 0; i < res1.size(); ++i)
		{

			if ((res1[i] == Sliding || res1[i] == Crossing || res1[i] == In) && mp.wall.line[i].norm * vel < -EPSILON)
			{

				mapCollisionState = true;
				pos(0, 0);
				vel(0, 0);
				return;
			}
		}

		for (int i = 0; i < res2.size(); ++i)
		{

			if ((res2[i] == Sliding || res2[i] == Crossing || res2[i] == In) && mp.platform.line[i].norm * vel < -EPSILON)
			{

				mapCollisionState = true;
				pos(0, 0);
				vel(0, 0);
				return;
			}
		}
	}
}
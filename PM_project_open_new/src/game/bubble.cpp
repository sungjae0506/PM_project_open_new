#include "bubble.h"

Bubble::Bubble()
{
	hitBox.center(0.0, 0.0);
	hitBox.radius = r1;
	mainTick = 0;
	internalTick = 0;
	mapCollisionState = false;
	state = "Horizontal";
}
Bubble::Bubble(Point _pos, Point _dir)
{
	pos = _pos;
	hitBox.center(0.0, 0.0);
	hitBox.radius = r1;
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

void Bubble::draw(void)
{
	/*float emission[4] = {mtl.getEmission()[0], mtl.getEmission()[1] , mtl.getEmission()[2] , mtl.getEmission()[3]};
	float ambient[4] = { mtl.getAmbient()[0], mtl.getAmbient()[1] , mtl.getAmbient()[2] , mtl.getAmbient()[3] };
	float diffuse[4] = { mtl.getDiffuse()[0], mtl.getDiffuse()[1] , mtl.getDiffuse()[2] , mtl.getDiffuse()[3] };
	float specular[4] = { mtl.getSpecular()[0], mtl.getSpecular()[1] , mtl.getSpecular()[2] , mtl.getSpecular()[3] };
	float shininess[1] = { mtl.getShininess() };

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.0);
	printf("%lf %lf %lf\n", pos.x, pos.y, r1);
	cout << emission[0] << " " << emission[1] << " " << emission[2] << " " << emission[3] << endl;
	if (state == "Horizontal")
	{
		glutSolidSphere(r1, 100.0, 100.0);
	}
	glPopMatrix();*/

	double size = 10.0;
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(pos.x - size / 2, pos.y - size / 2);
	glVertex2f(pos.x + size / 2, pos.y - size / 2);
	glVertex2f(pos.x + size / 2, pos.y + size / 2);
	glVertex2f(pos.x - size / 2, pos.y + size / 2);
	glEnd();
}
void Bubble::move(void)
{
	if (getState() == "Vertical")
	{
		vel(0, bubbleVerticalVel);
	}

	pos += vel / idlePerSecond;
	vel += acc / idlePerSecond;
}

Point Bubble::getPos(void)
{
	return pos;
}

void Bubble::setState(string s)
{
	state = s;
	internalTick = 0;
}

string Bubble::getState(void)
{
	return state;
}

void Bubble::changeState(void)
{
	if (getState() == "Horizontal")
	{
		if (mapCollisionState || internalTick >= 20)
		{
			setState("Vertical");
		}
	}
	else if (getState() == "Vertical")
	{

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

		auto res = wall.collisionDetection(hitBox + pos);

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
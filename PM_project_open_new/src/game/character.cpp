#include "character.h"

Character::Character()
{
}

Character::Character(const Character& c)
{
	players = c.players;
	enemies = c.enemies;
}

void Character::readCharacter(string path)
{
	int np, ne;
	double _x, _y;
	fstream f(path);
	string s;

	f >> np;
	for (int i = 0; i < np; ++i)
	{
		f >> s;
		f >> _x >> _y;
		Player tempP;
		tempP.setPos(Point(_x, _y));
		tempP.setVel(Point(0.0, 0.0));
		tempP.setAcc(gravity);
		tempP.setName(s);
		tempP.setState("None");
		players.push_back(tempP);
	}
}
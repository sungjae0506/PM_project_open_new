/*

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

*/

/*
void GameManager::addMap(string path)
{
	Map temp;

	temp.readMap(path);
	maps.push_back(temp);
}

void GameManager::addCharacter(string path)
{
	Character temp;
	temp.readCharacter(path);
	characters.push_back(temp);
}
*/

/*
void Map::readMap(string file)
{
	fstream f(file);
	string s;
	int h, w;

	Range r(0, 0, 320, 320);

	//////////////////////////////////
	tile.resize(2);
	background.resize(1);
	f >> s;
	tile[0](s, Range(0, 0, 10, 10));
	f >> s;
	tile[1](s, Range(0, 0, 20, 20));
	f >> s;
	//background[0](s, Range(0, 0, 320, 320));
	//////////////////////////////////

	f >> h >> w;
	tileVector.resize(h);
	for (int i = 0; i < h; ++i)
		tileVector[i].resize(w);

	bubbleCurrentVector.resize(h);
	for (int i = 0; i < h; ++i)
		bubbleCurrentVector[i].resize(w);

	for (int i = 0; i < h; ++i)
	{
		f >> s;
		for (int j = 0; j < w; ++j)
			if (s[j] == '#')
				tileVector[i][j] = 1;
	}
	//////////////////////////////////
	for (int i = 0; i < h; ++i)
	{
		f >> s;
		for (int j = 0; j < w; ++j)
			bubbleCurrentVector[i][j] = s[j];
	}
	//////////////////////////////////
	platform = vectorToLines(tileVector, r);
	wall.addLine(Line(Point(r.point0.x + 20, r.point0.y), Point(r.point0.x + 20, r.point1.y), Point(1, 0)));
	wall.addLine(Line(Point(r.point1.x - 20, r.point0.y), Point(r.point1.x - 20, r.point1.y), Point(-1, 0)));
}
*/
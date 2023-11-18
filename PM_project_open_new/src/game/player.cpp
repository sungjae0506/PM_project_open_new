#include "player.h"

Player::Player()
{
}
Player::Player(Point _pos)
{
	pos = _pos;
	hitBox.addLine(Line(Point(-10, 10),  Point(10, 10),  Point(0, 1)));  // ��
	hitBox.addLine(Line(Point(-10, -10), Point(10, -10), Point(0, -1))); // ��
	hitBox.addLine(Line(Point(-10, -10), Point(-10, 10), Point(-1, 0))); // ��
	hitBox.addLine(Line(Point(10, -10),  Point(10, 10),  Point(1, 0)));  // ��
}
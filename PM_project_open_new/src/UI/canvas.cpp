#include "canvas.h"

Canvas::Canvas()
{
}

Canvas::Canvas(const Range& r, const Range& c)
{
	range = r;
	coord = c;
}

Canvas& Canvas::operator() (const Range& r, const Range& c)
{
	range = r;
	coord = c;
	return *this;
}

Canvas& Canvas::addDrawFunc(void (*drawFunc)(Point))
{
	drawFuncs.push_back(drawFunc);
	return *this;
}

Canvas& Canvas::addKeyboardFunc(void (*keyboardFunc)(KeyboardEvent, string, Point))
{
	keyboardFuncs.push_back(keyboardFunc);
	return *this;
}

Canvas& Canvas::addMouseFunc(void (*mouseFunc)(MouseEvent, string, Point))
{
	mouseFuncs.push_back(mouseFunc);
	return *this;
}

Canvas& Canvas::addIdleFunc(void (*idleFunc)(IdleEvent))
{
	idleFuncs.push_back(idleFunc);
	return *this;
}

void Canvas::keyboardEvent(KeyboardEvent e, string key, Point p)
{
	Point mousePos = Transform(range, coord)(p);
	for (auto func : keyboardFuncs)
		func(e, key, mousePos);
}

void Canvas::mouseEvent(MouseEvent e, string button, Point p)
{
	Point mousePos = Transform(range, coord)(p);
	for (auto func : mouseFuncs)
		func(e, button, mousePos);
}

void Canvas::idleEvent(IdleEvent e)
{
	for (auto func : idleFuncs)
		func(e);
}

void Canvas::draw(Point mousePos)
{
	glPushMatrix();
	glTranslatef(range.point0.x, range.point0.y, 0.0);
	glScalef((range.point1.x - range.point0.x) / (coord.point1.x - coord.point0.x), (range.point1.y - range.point0.y) / (coord.point1.y - coord.point0.y), 1.0);
	glTranslatef(-coord.point0.x, -coord.point0.y, 0.0);
	for (auto func : drawFuncs)
		func(mousePos);
	glPopMatrix();
}
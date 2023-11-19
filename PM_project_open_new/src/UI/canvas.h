#pragma once
#include "../util/range.h"
#include "event.h"
#include "../util/object.h"
#include <string>

class Canvas
{
public:
	Range range, coord;

	vector<void(*)(KeyboardEvent, string, Point)> keyboardFuncs;
	vector<void(*)(MouseEvent, string, Point)> mouseFuncs;
	vector<void(*)(IdleEvent)> idleFuncs;
	vector<void(*)(Point)> drawFuncs;

	Canvas();
	Canvas(const Range &r, const Range &c);
	Canvas& operator() (const Range& r, const Range& c);

	Canvas& addKeyboardFunc(void (*keyboardFunc)(KeyboardEvent, string, Point));
	Canvas& addMouseFunc(void (*mouseFunc)(MouseEvent, string, Point));
	Canvas& addIdleFunc(void (*idleFunc)(IdleEvent));
	Canvas& addDrawFunc(void (*drawFunc)(Point));

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void mouseEvent(MouseEvent e, string button, Point p);
	void idleEvent(IdleEvent e);
	void draw(Point mousePos);
};
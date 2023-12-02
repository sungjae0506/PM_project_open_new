#pragma once
#include "text.h"
#include "event.h"

class InputBox
{
public:
	Range range;
	string defaultContent;
	string defaultColor;
	string content;
	Text inputBoxText;
	bool clicked = true;
	vector<void (*)(string)> inputBoxFuncs;
	void (*styleFunc) (InputBox*) = NULL;
	int cursor = 0;
	int timeCnt = 0;

	InputBox(string str, string cColor, string bColor, double sz, bool _clicked, const Range& r);
	InputBox& operator() (string str, string cColor, string bColor, double sz, bool _clicked, const Range& r);

	InputBox& addInputBoxFunc(void (*func)(string));
	InputBox& addStyleFunc(void(*)(InputBox* i));

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void mouseEvent(MouseEvent e, string button, Point p);
	void idleEvent(IdleEvent e);
	void draw(Point pos);
};
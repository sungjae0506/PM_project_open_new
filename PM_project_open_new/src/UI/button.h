#pragma once
#include "../util/range.h"
#include "../asset/image.h"
#include "text.h"
#include "event.h"

class Button
{
public:
	Range range;
	Image buttonImage;
	Text buttonText;
	vector<void(*)(void)> buttonFuncs;
	void(*styleFunc)(Button*) = NULL;


	enum ButtonState{None, OnButton, Clicked} buttonState = None;
	
	Button();
	Button(string imagePath, string text, string charColor, double fontSize, Range r);
	Button& operator()(string imagePath, string text, string charColor, double fontSize, Range r);

	void mouseEvent(MouseEvent e, string button, Point p);
	void draw(bool isMouseOn = false);

	Button& addButtonFunc(void(*func)());

	Button& addStyleFunc(void(*func)(Button*));
};
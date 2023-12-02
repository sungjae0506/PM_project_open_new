#include "button.h"
#include <iostream>

Button::Button() 
{
}

Button::Button(string imagePath, string text, string charColor, double fontSize, Range r)
{
	range = r;

	buttonImage(imagePath, range);

	vector<double> textConst = Text::getConst();
	double lineSpacing = textConst[0];
	double letterSpacing = textConst[1];
	double aspectRatio = textConst[2];

	Point center = (range.point0 + range.point1) / 2.0;
	Point half_x = Point(fontSize * 0.5 / aspectRatio * (text.length() * (letterSpacing / 100.0) - ((letterSpacing - 100.0) / 100.0)), fontSize * 0.5);
	Point half_y = Point(fontSize * 0.5 / aspectRatio * (text.length() * (letterSpacing / 100.0) - ((letterSpacing - 100.0) / 100.0)), fontSize * 0.8);
	
	buttonText(text, charColor, "", fontSize, Range(center - half_x, center + half_y));
}

Button& Button::operator()(string imagePath, string text, string charColor, double fontSize, Range r)
{
	buttonImage(imagePath, range);
	buttonText(text, charColor, "", fontSize, range);
	return *this;
}

void Button::draw(bool isMouseOn)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (isMouseOn)
	{
		if (buttonState != Clicked)
			buttonState = OnButton;
	}
	else 
	{
		buttonState = None;
	}

	if (styleFunc)
	{
		styleFunc(this);
		return;
	}
	switch (buttonState)
	{
	case None:
		buttonImage.draw();
		buttonText.draw();
		break;
	case OnButton:
	case Clicked:
		buttonImage.draw();
		buttonText.draw();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(0.0, 0.0, 0.0, 0.2);
		glBegin(GL_QUADS);
		glVertex2f(range.point0.x, range.point0.y);
		glVertex2f(range.point1.x, range.point0.y);
		glVertex2f(range.point1.x, range.point1.y);
		glVertex2f(range.point0.x, range.point1.y);
		glEnd();

		glDisable(GL_BLEND);
		break;
	}
}

void Button::mouseEvent(MouseEvent e, string button, Point p)
{
	if (e == MouseDown)
	{
		for (auto& func : buttonFuncs)
			func();
		buttonState = Clicked;
	}
	else
	{
		buttonState = None;
	}
}

Button& Button::addButtonFunc(void(*func)())
{
	buttonFuncs.push_back(func);
	return *this;
}

Button& Button::addStyleFunc(void(*func)(Button*))
{
	styleFunc = func;
	return *this;
}
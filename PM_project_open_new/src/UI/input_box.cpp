#include "input_box.h"

InputBox::InputBox(string str, string cColor, string bColor, double sz, bool _clicked, const Range& r)
{
	defaultContent = str;
	content = "";
	range = r;
	clicked = _clicked;
	inputBoxText(str, cColor, bColor, sz, r);

	vector<int> tempC = stringToRGBi(cColor);
	vector<int> tempB = stringToRGBi(bColor);
	vector<int> tempRes(3, 0);
	for (int i = 0; i < 3; ++i)
		tempRes[i] = (tempC[i] / 4) + (tempB[i] * 3 / 4);
	defaultColor = RGBiToString(tempRes);
}
InputBox& InputBox::operator() (string str, string cColor, string bColor, double sz, bool _clicked, const Range& r)
{
	defaultContent = str;
	content = "";
	range = r;
	clicked = _clicked;
	inputBoxText(str, cColor, bColor, sz, r);

	vector<int> tempC = stringToRGBi(cColor);
	vector<int> tempB = stringToRGBi(bColor);
	vector<int> tempRes(3, 0);
	for (int i = 0; i < 3; ++i)
		tempRes[i] = (tempC[i] / 4) + (tempB[i] * 3 / 4);
	defaultColor = RGBiToString(tempRes);
}

InputBox& InputBox::addInputBoxFunc(void (*func)(string))
{
	inputBoxFuncs.push_back(func);
	return *this;
}
InputBox& InputBox::addStyleFunc(void(*func)(InputBox*))
{
	styleFunc = func;
	return *this;
}

void InputBox::keyboardEvent(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown && clicked)
	{
		if (key.c_str()[0] == 8)
		{
			if (cursor != 0)
			{
				content.erase(--cursor, 1);
			}
		}
		else if (key.size() == 1)
		{
			content.insert(cursor++, key);
		}
		
		if (key == "LEFT" && cursor != 0)
		{
			--cursor;
		}
		if (key == "RIGHT" && cursor != content.size())
		{
			++cursor;
		}
	}
}
void InputBox::mouseEvent(MouseEvent e, string button, Point p)
{
	if (e == MouseDown)
	{
		clicked = range.contain(p);
		timeCnt = 0;
		if (clicked)
		{
			vector<double> temp = inputBoxText.getConst();
			double cursorDelta = (inputBoxText.fontSize / temp[2] * (temp[1] / 100.0));
			cursor = max(min((int)((p.x - range.point0.x) / cursorDelta + 0.5), (int)(content.size())), 0);
		}
	}
}
void InputBox::idleEvent(IdleEvent e)
{
	if (e == IdleBegin)
	{
		content = "";
		timeCnt = 0;
	}
	if (e == IdleRunning)
	{
		for (auto& func : inputBoxFuncs)
			func(content);
		++timeCnt;
	}
}
void InputBox::draw(Point pos)
{
	if (styleFunc)
	{
		styleFunc(this);
		return;
	}
	if (content == "")
	{
		inputBoxText.content = defaultContent;
		string temp = inputBoxText.charColor;
		inputBoxText.charColor = defaultColor;
		inputBoxText.draw();
		inputBoxText.charColor = temp;
	}
	else
	{
		inputBoxText.content = content;
		inputBoxText.draw();
	}
	if (clicked)
	{
		vector<double> temp = inputBoxText.getConst();
		double cursorDelta = (inputBoxText.fontSize / temp[2] * (temp[1] / 100.0));

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 1, 1);
		glVertex2f(range.point0.x, range.point0.y);
		glVertex2f(range.point1.x, range.point0.y);
		glVertex2f(range.point1.x, range.point1.y);
		glVertex2f(range.point0.x, range.point1.y);
		glEnd();

		if (timeCnt / 100 % 2 == 0 && inputBoxText.fontSize * 0.2 < range.point1.x && content.size() != 0)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex2f(range.point0.x + cursorDelta * cursor - inputBoxText.fontSize * 0.025, range.point0.y + inputBoxText.fontSize * 0.05);
			glVertex2f(range.point0.x + cursorDelta * cursor + inputBoxText.fontSize * 0.025, range.point0.y + inputBoxText.fontSize * 0.05);
			glVertex2f(range.point0.x + cursorDelta * cursor + inputBoxText.fontSize * 0.025, range.point1.y - inputBoxText.fontSize * 0.05);
			glVertex2f(range.point0.x + cursorDelta * cursor - inputBoxText.fontSize * 0.025, range.point1.y - inputBoxText.fontSize * 0.05);
			glEnd();
		}
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex2f(range.point0.x, range.point0.y);
		glVertex2f(range.point1.x, range.point0.y);
		glVertex2f(range.point1.x, range.point1.y);
		glVertex2f(range.point0.x, range.point1.y);
		glEnd();
	}
}
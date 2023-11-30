#include "page.h"

Page::Page()
{
}

Page::Page(string name, const Range r)
{
	pageName = name;
	range = r;
}

Page& Page::operator() (string name, const Range r)
{
	pageName = name;
	range = r;
	return *this;
}

void Page::keyboardEvent(KeyboardEvent e, string key, Point p)
{
	for (auto func : keyboardFuncs)
		func(e, key, p);
	for (auto& i : canvases)
		i.keyboardEvent(e, key, p);
}

void Page::mouseEvent(MouseEvent e, string button, Point p)
{
	for (auto func : mouseFuncs)
		func(e, button, p);
	for (auto& i : canvases)
		if (i.range.contain(p))
			i.mouseEvent(e, button, p);
	for (auto& i : buttons)
		if (i.range.contain(p))
			i.mouseEvent(e, button, p);
}

void Page::idleEvent(IdleEvent e)
{
	if (e == IdleBegin || e == IdleRunning)
	{
		for (auto func : idleFuncs)
			func(e);
		for (auto& i : canvases)
			i.idleEvent(e);
	}
	else if (e == IdleEnd)
	{
		for (auto& i : canvases)
			i.idleEvent(e);
		for (auto func : idleFuncs)
			func(e);
	}
}

void Page::resizeEvent(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
}

void Page::draw(Point mousePos)
{
	Range scissor;
	if (background != "")
	{
		Image(background, range).draw();
	}
	for (auto& i : canvases)
	{
		scissor = Transform(range, Range(0, 0, windowWidth, windowHeight))(i.range);
		glScissor(scissor.point0.x, scissor.point0.y, scissor.point1.x - scissor.point0.x, scissor.point1.y - scissor.point0.y);
		glEnable(GL_SCISSOR_TEST);
		i.draw(mousePos);
		glDisable(GL_SCISSOR_TEST);
	}
	for (auto& i : images)
	{
		i.draw();
	}
	for (auto& i : texts)
	{
		scissor = Transform(range, Range(0, 0, windowWidth, windowHeight))(i.range);
		glScissor(scissor.point0.x, scissor.point0.y, scissor.point1.x - scissor.point0.x, scissor.point1.y - scissor.point0.y);
		glEnable(GL_SCISSOR_TEST);
		i.draw();
		glDisable(GL_SCISSOR_TEST);
	}
	for (auto& i : buttons)
	{
		if (i.range.contain(mousePos))
			i.draw(true);
		else
			i.draw();
	}
	for (auto func : drawFuncs)
		func(mousePos);
}

Page& Page::addDrawFunc(void (*drawFunc)(Point))
{
	drawFuncs.push_back(drawFunc);
	return *this;
}

Page& Page::addKeyboardFunc(void (*keyboardFunc)(KeyboardEvent, string, Point))
{
	keyboardFuncs.push_back(keyboardFunc);
	return *this;
}

Page& Page::addMouseFunc(void (*mouseFunc)(MouseEvent, string, Point))
{
	mouseFuncs.push_back(mouseFunc);
	return *this;
}

Page& Page::addIdleFunc(void (*idleFunc)(IdleEvent))
{
	idleFuncs.push_back(idleFunc);
	return *this;
}

Page& Page::addCanvas(const Canvas& c)
{
	canvases.push_back(c);
	return *this;
}

Page& Page::addCanvas(vector<Canvas> cs)
{
	for (auto& c : cs)
		canvases.push_back(c);
	return *this;
}

Page& Page::addImage(const Image& i)
{
	images.push_back(i);
	return *this;
}

Page& Page::addImage(vector<Image> is)
{
	for (auto& i : is)
		images.push_back(i);
	return *this;
}

Page& Page::addText(const Text& t)
{
	texts.push_back(t);
	return *this;
}

Page& Page::addText(vector<Text> ts)
{
	for (auto& t : ts)
		texts.push_back(t);
	return *this;
}

Page& Page::addButton(const Button& b)
{
	buttons.push_back(b);
	return *this;
}

Page& Page::addButton(vector<Button> bs)
{
	for (auto& b : bs)
		buttons.push_back(b);
	return *this;
}

Page& Page::addBackground(string s)
{
	background = s;
	return *this;
}
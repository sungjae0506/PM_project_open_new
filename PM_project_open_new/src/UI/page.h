#pragma once
#include <string>
#include <vector>
#include "event.h"
#include "../util/range.h"
#include "../util/object.h"
#include "canvas.h"
#include "../asset/image.h"
#include "../asset/sound_loader.h"
#include "text.h"
#include "button.h"
#include "input_box.h"
using namespace std;

class Page
{
public:
	string pageName;
	Range range;
	Point mousePos;

	vector<void(*)(KeyboardEvent, string, Point)> keyboardFuncs;
	vector<void(*)(MouseEvent, string, Point)> mouseFuncs;
	vector<void(*)(IdleEvent)> idleFuncs;
	vector<void(*)(Point)> drawFuncs;
	vector<void(*)(IdleEvent, int)> soundFuncs;

	vector<Canvas> canvases;
	vector<Image> images;
	vector<Text> texts;
	vector<Button> buttons;
	vector<InputBox> inputBoxes;
	string background;

	int windowWidth;
	int windowHeight;

	Page();
	Page(string name, const Range r);
	Page& operator() (string name, const Range r);

	void keyboardEvent(KeyboardEvent e, string key, Point p);
	void mouseEvent(MouseEvent e, string button, Point p);
	void idleEvent(IdleEvent e);
	void resizeEvent(int w, int h);
	void draw(Point mousePos = Point(0, 0));

	Page& addKeyboardFunc(void (*keyboardFunc)(KeyboardEvent, string, Point));
	Page& addMouseFunc(void (*mouseFunc)(MouseEvent, string, Point));
	Page& addIdleFunc(void (*idleFunc)(IdleEvent));
	Page& addDrawFunc(void (*drawFunc)(Point));

	Page& addCanvas(const Canvas &c);
	Page& addCanvas(vector<Canvas> cs);

	Page& addImage(const Image &i);
	Page& addImage(vector<Image> is);

	Page& addText(const Text& t);
	Page& addText(vector<Text> ts);

	Page& addButton(const Button& t);
	Page& addButton(vector<Button> ts);

	Page& addInputBox(const InputBox& ib);
	Page& addInputBox(vector<InputBox> ibs);

	Page& addBackground(string s);

	//Page& addSound(SoundContainer s, int num);
};
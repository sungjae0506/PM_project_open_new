#pragma once
#include <string>
#include <array>
#include "GL/freeglut.h"
#include "page.h"
#include "event.h"
#include "../util/range.h"
#include "../asset/image.h"
using namespace std;

void windowResize(int w, int h);
void windowDisplay();
void windowIdle();

void windowKeyboard(unsigned char key, int x, int y);
void windowKeyboardUp(unsigned char key, int x, int y);
void windowSpecial(int key, int x, int y);
void windowSpecialUp(int key, int x, int y);

void windowMouse(int button, int state, int x, int y);
void windowMotion(int x, int y);
void windowPassiveMotion(int x, int y);

class Window
{
private:
	string windowName;
public:
	Window();
	Window(string name, int* argc, char** argv, int x, int y, int w, int h);
	Window& operator() (string name, int* argc, char** argv, int x, int y, int w, int h);

	Window& addPage(const Page& p);
	Window& addPages(vector<Page> p);

	void setPage(Page p);
	void setPage(string pageName);
	void mainLoop(string pageName);

	Point getMousePos(void);
};
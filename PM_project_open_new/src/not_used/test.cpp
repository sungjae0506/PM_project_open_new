/*
#include <iostream>
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <ctime>
#include <Windows.h>
#include "../asset/image.h"
#include "../game/map.h"
#include "../game/player.h"
#include "../UI/window.h"
#include "../UI/canvas.h"

using namespace std;
#define WIDTH 600
#define HEIGHT 600

Window window;

Map game_map;

void drawGameMap()
{
	game_map.platform.print();
}

void mouseTest(MouseEvent e, string button, Point p)
{
	//printf("%lf %lf\n", p.x, p.y);
	//cout << button << endl;
}

void keyboardTest(KeyboardEvent e, string key, Point p)
{
	cout << key;
	if (e == KeyboardUp)
		cout << " UP\n";
	else
		cout << " DOWN\n";
}

void moveToGamePage()
{
	window.setPage("gamePage");
}

void moveToMainPage()
{
	window.setPage("mainPage");
}

string mousePosToStr(void)
{
	Point mousePos = window.getMousePos();
	return "(" + to_string((int)mousePos.x) + ", " + to_string((int)mousePos.y) + ")";
}

int main(int argc, char** argv) {

	game_map.readMap("map.txt");

	window("main window", &argc, argv, 300, 300, WIDTH, HEIGHT);

	window
		.addPages
		({
			Page("mainPage", Range(0, 0, 320, 320))
			.addImage
			(
				Image("image/snu.png", Range(0, 0, 100, 100))
			)
			.addCanvas
			({
				Canvas(Range(100, 100, 320, 320), Range(0, 20, 320, 280))
				.addDrawFunc
				(
					drawGameMap
				)
				.addMouseFunc
				(
					mouseTest
				)
				.addKeyboardFunc
				(
					keyboardTest
				)

			}).addText
			({
				Text("ABCD\nHan\nSJ!", "#000000", "#FF00FF", 32.0, Range(0, 200, 100, 320)),
			})
			.addButton
			(
				Button("image/button.png", "Button", "#000000", 20.0, Range(200, 20, 280, 60))
				.addButtonFunc
				(
					moveToGamePage
				)
			),
			Page("gamePage", Range(0, 0, 320, 320))
			.addText
			({
				Text("It's game page!", "#FFFFFF", "", 16.0, Range(100, 40, 280, 120)),
				Text("", "#FFFFFF", "00FFFF", 10.0, Range(10, 290, 310, 310))
				.addTextFunc
				(
					mousePosToStr
				)
			})
			.addButton
			(
				Button("image/button.png", "Back", "#FFFFFF", 32.0, Range(20, 200, 120, 250)).
				addButtonFunc
				(
					moveToMainPage
				)
			)
			});

	window.mainLoop("mainPage");

	return 0;
}
*/
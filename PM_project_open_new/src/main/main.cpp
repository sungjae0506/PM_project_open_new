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

#include "callback.h"

using namespace std;
#define WIDTH 1600
#define HEIGHT 900

Window window;
Page startingPage("startingPage", Range(0, 0, 1600, 900));

Page storyPage("storyPage", Range(0, 0, 1600, 900));
Page helpPage("helpPage", Range(0, 0, 1600, 900));
Page scoreboardPage("scoreboardPage", Range(0, 0, 1600, 900));
Page customPage("customPage", Range(0, 0, 1600, 900));

Page selectionPage("selectionPage", Range(0, 0, 1600, 900));

Page gamePage("gamePage", Range(0, 0, 1600, 900));

Page gameOverPage("gameOverPage", Range(0, 0, 1600, 900));
Page gameWinPage("gameWinPage", Range(0, 0, 1600, 900));




int main(int argc, char** argv)
{

	window("Bubble Bobble", &argc, argv, 50, 50, WIDTH, HEIGHT);

	startingPage.
	addBackground
	(
		"image/bubble_bobble_starting.png"
	)
	.addButton
	({
		Button("image/button2.png", "Start", "#FF0000", 36.0, Range(450, 200, 750, 300))
		.addButtonFunc
		(
			[]() -> void { window.setPage("storyPage"); }
		),
		Button("image/button2.png", "Help", "#00FF00", 36.0, Range(850, 200, 1150, 300))
		.addButtonFunc
		(
			[]() -> void { window.setPage("helpPage"); }
		),
		Button("image/button2.png", "Scoreboard", "#0000FF", 36.0, Range(450, 50, 750, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("scoreboardPage"); }
		),
		Button("image/button2.png", "Custom", "#FFFF00", 36.0, Range(850, 50, 1150, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("customPage"); }
		)
	})
	.addKeyboardFunc
	(
		startingPageKeyboard
	);

	storyPage
	.addText
	(
		Text("wow!", "#16FFFF", "", 32.0, Range(0, 0, 320, 40))
	)
	.addCanvas
	(
		Canvas(Range(0, 0, 1600, 900), Range(0, 0, 1600, 900))
		.addDrawFunc
		(
			storyPageDraw
		)
		.addKeyboardFunc
		(
			storyPageKeyboard
		)
		.addIdleFunc
		(
			storyPageIdle
		)
	);

	selectionPage
	.addText
	(
		Text("wow!", "#FFFFFF", "", 32.0, Range(0, 0, 320, 40))
	);

	gamePage
	.addIdleFunc
	(
		gamePageIdle
	)
	.addCanvas
	(
		Canvas(Range(250, 0, 1350, 900), Range(0, 20, 320, 280))
		.addDrawFunc
		(
			gameManagerDraw
		)
		.addIdleFunc
		(
			gameManagerIdle
		)
		.addKeyboardFunc
		(
			gameManagerKeyboard
		)
	)
	.addText
	(
		Text("wow!", "#16FFFF", "", 32.0, Range(0, 0, 320, 40))
	);

	window
	.addPage
	({
		startingPage,
		storyPage,
		selectionPage,
		gamePage
	});

	window.mainLoop("startingPage");

	return 0;
}

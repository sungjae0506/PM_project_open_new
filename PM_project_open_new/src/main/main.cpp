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

extern string player1;
extern string player2;

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
	)
	.addButton
	({
		Button("image/bubble_bobble_player.png", "", "#FF0000", 36.0, Range(450, 200, 650, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("P1"); }
		),
		Button("image/bubble_bobble_enemy.png", "", "#00FF00", 36.0, Range(700, 200, 900, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("P2"); }
		),
		Button("image/snu.png", "", "#0000FF", 36.0, Range(950, 200, 1150, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("P3"); }
		),
		Button("image/button2.png", "Single", "#0000FF", 36.0, Range(450, 50, 650, 150))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("Single"); }
		),
		Button("image/button2.png", "Multi", "#FFFF00", 36.0, Range(700, 50, 900, 150))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("Multi"); }
		),
		Button("image/button2.png", "Next", "#FF0000", 36.0, Range(950, 50, 1150, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("gamePage"); }
		)
	})
	.addKeyboardFunc
	(
		selectionPageKeyboard
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

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
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Help", "#00FF00", 36.0, Range(850, 200, 1150, 300))
		.addButtonFunc
		(
			[]() -> void { window.setPage("helpPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Scoreboard", "#0000FF", 36.0, Range(450, 50, 750, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("scoreboardPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Custom", "#FFFF00", 36.0, Range(850, 50, 1150, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("customPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		)
	})
	.addKeyboardFunc
	(
		startingPageKeyboard
	);


	helpPage
	.addBackground
	(
		"image/bubble_bobble_help.png"
	)
	.addText
	(
		Text("wow!", "#16FFFF", "", 32.0, Range(0, 0, 320, 40))
	)
	.addButton
	(
		Button("image/button2.png", "Back", "#FF0000", 36.0, Range(30, 750, 130, 850))
		.addButtonFunc
		(
			[]() -> void { window.setPage("startingPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		)
	);

	scoreboardPage
	.addBackground
	(
		"image/bubble_bobble_scoreboard_background.png"
	)
	.addButton
	(
		Button("image/button2.png", "Back", "#FF0000", 36.0, Range(30, 750, 130, 850))
		.addButtonFunc
		(
			[]() -> void { window.setPage("startingPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		)
	)
	.addCanvas
	(
		Canvas(Range(200, 150, 1400, 750), Range(200, 150, 1400, 750))
		.addDrawFunc
		(
			scoreBoardDraw
		)
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
		Text("Select 1P", "#FFFFFF", "", 48.0, Range(660, 450, 940, 500))
		.addTextFunc
		(
			selectionPageText
		)
	)
	.addCanvas
	(
		Canvas(Range(0, 0, 1600, 900), Range(0, 0, 1600, 900))
		.addDrawFunc
		(
			selectionPageDraw
		)
	)
	.addButton
	({
		Button("image/player/player1.png", " ", "#FF0000", 36.0, Range(450, 200, 650, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("player1"); }
		),
		Button("image/player/player2.png", " ", "#00FF00", 36.0, Range(700, 200, 900, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("player2"); }
		),
		Button("image/player/player3.png", " ", "#0000FF", 36.0, Range(950, 200, 1150, 400))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("player3"); }
		),
		Button("image/button2.png", "1P", "#0000FF", 36.0, Range(450, 50, 650, 150))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("1P"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "2P", "#FFFF00", 36.0, Range(700, 50, 900, 150))
		.addButtonFunc
		(
			[]() -> void { selectionPageButton("2P"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Next", "#FF0000", 36.0, Range(950, 50, 1150, 150))
		.addButtonFunc
		(
			[]() -> void { window.setPage("gamePage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		)
	})
	.addKeyboardFunc
	(
		selectionPageKeyboard
	)
	.addIdleFunc
	(
		selectionPageIdle
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

	gameOverPage
	.addBackground
	(
		"image/Page/gameOverPage.png"
	)
	.addCanvas
	(
		Canvas(Range(0, 0, 1600, 900), Range(0, 0, 1600, 900))
		.addKeyboardFunc
		(
			gameOverPageKeyboard
		)
	);

	gameWinPage
	.addBackground
	(
		"image/Page/gameWinPage.png"
	)
	.addCanvas
	(
		Canvas(Range(0, 0, 1600, 900), Range(0, 0, 1600, 900))
		.addKeyboardFunc
		(
			gameWinPageKeyboard
		)
	);

	window
	.addPage
	({
		startingPage,
		helpPage,
		scoreboardPage,
		storyPage,
		selectionPage,
		gamePage,
		gameOverPage,
		gameWinPage
	});

	window.mainLoop("startingPage");

	return 0;
}

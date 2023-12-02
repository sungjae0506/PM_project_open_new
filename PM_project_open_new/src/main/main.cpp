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

	/*fstream f(path);
	jsonData = json::parse(f);*/

	scoreboardPage
	.addBackground
	(
		"image/bubble_bobble_scoreboard_background.png"
	)
	.addCanvas
	({
		Canvas(Range(450, 50, 1050, 850), Range(0, 0, 600, 800))
		.addDrawFunc
		(
			[](Point pos) ->
			void {
				Text("Score Board", "#000000", "", 72.0, Range(100, 710, 600, 800)).draw();
				Text("1", "#FFD700", "", 72.0, Range(0, 576, 50, 648)).draw();
				Text("2", "#C0C0C0", "", 72.0, Range(0, 432, 50, 504)).draw();
				Text("3", "#C49C48", "", 72.0, Range(0, 288, 50, 360)).draw();
				Text("4", "#000000", "", 72.0, Range(0, 144, 50, 216)).draw();
				Text("5", "#000000", "", 72.0, Range(0,   0, 50,  72)).draw();
				Text("", "#000000", "", 45.0, Range(100, 0, 600, 648))
				.addTextFunc
				(
					scoreboardPageText
				)
				.draw();
			}
		),
		Canvas(Range(1050, 50, 1150, 850), Range(0, 0, 100, 800))
		.addDrawFunc
		(
			scoreboardPageDraw
		)
	})
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
	.addIdleFunc
	(
		scoreboardPageIdle
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
	.addText
	(
		Text("wow!", "#16FFFF", "", 32.0, Range(0, 0, 320, 40))
	);

	gameWinPage
	.addText
	(
		Text("wow!", "#16FFFF", "", 32.0, Range(0, 0, 320, 40))
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

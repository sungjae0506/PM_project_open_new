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
Page nameInputPage("nameInputPage", Range(0, 0, 1600, 900));

Page mapEditorPage("mapEditorPage", Range(0, 0, 1600, 900));
Page mapSelectionPage("mapSelectionPage", Range(0, 0, 1600, 900));

int main(int argc, char** argv)
{

	window("Bubble Bobble", &argc, argv, 50, 50, WIDTH, HEIGHT);

	startingPage.
	addBackground
	(
		"image/Page/bubble_bobble_starting.png"
	)
	.addButton
	({
		Button("image/button2.png", "Start", "#591010", 36.0, Range(487, 300, 787, 400))
		.addButtonFunc
		(
			[]() -> void { window.setPage("storyPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Help", "#591010", 36.0, Range(813, 300, 1113, 400))
		.addButtonFunc
		(
			[]() -> void { window.setPage("helpPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Scoreboard", "#591010", 36.0, Range(450, 150, 750, 250))
		.addButtonFunc
		(
			[]() -> void { window.setPage("scoreboardPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Custom", "#591010", 36.0, Range(850, 150, 1150, 250)) // �ӽ� ����
		.addButtonFunc
		(
			[]() -> void { window.setPage("mapEditorPage"); }
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
		"image/Page/bubble_bobble_help.png"
	)
	.addButton
	(
		Button("image/button2.png", "Back", "#000000", 20.0, Range(30, 800, 130, 870))
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
		"image/Page/bubble_bobble_scoreboard_background.png"
	)
	.addCanvas
	({
		Canvas(Range(450, 0, 1050, 800), Range(0, 0, 600, 800))
		.addDrawFunc
		(
			[](Point pos) ->
			void {
				Image("image/gold_medal.png",Range(0, 580, 70, 650)).draw();
				Image("image/silver_medal.png", Range(0, 440, 70, 510)).draw();
				Image("image/bronze_medal.png", Range(0, 300, 70, 370)).draw();
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
		Canvas(Range(1050, 00, 1150, 800), Range(0, 0, 100, 800))
		.addDrawFunc
		(
			scoreboardPageDraw
		)
	})
	.addButton
	(
		Button("image/button2.png", "Back", "#000000", 20.0, Range(30, 800, 130, 870))
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
	.addBackground
	(
		"image/Page/bubble_bobble_select_background.png"
	)
	.addText
	(
		Text("Select 1P", "#000000", "", 48.0, Range(660, 450, 940, 500))
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
		),
		Button("image/button2.png", "Back", "#000000", 20.0, Range(30, 800, 130, 870))
		.addButtonFunc
		(
			[]() -> void { window.setPage("startingPage"); }
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
		Canvas(Range(288, 0, 1312, 832), Range(0, 20, 320, 280))
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
	({
		Text("HIGHSCORE", "#FF0000", "", 48.0, Range(300, 842, 600, 890)),
		Text("000000", "#FFFFFF", "", 48.0, Range(600, 842, 850, 890))
		.addTextFunc
		(
			[]() -> string { return gameManagerText("Highscore"); }
		),
		Text("SCORE", "#00FF00", "", 48.0, Range(920, 842, 1100, 890)),
		Text("000000", "#FFFFFF", "", 48.0, Range(1100, 842, 1300, 890))
		.addTextFunc
		(
			[]() -> string { return gameManagerText("Score"); }
		)
	});

	gameOverPage
	.addBackground
	(
		"image/Page/bubble_bobble_gameOver_background.png"
	)
	.addKeyboardFunc
	(
		gameOverPageKeyboard
	)
	.addIdleFunc
	(
		gameOverPageIdle
	);

	gameWinPage
	.addBackground
	(
		"image/Page/bubble_bobble_gameWin_background.png"
	)
	.addKeyboardFunc
	(
		gameWinPageKeyboard
	)
	.addIdleFunc
	(
		gameWinPageIdle
	);

	nameInputPage
	.addBackground
	(
		"image/Page/bubble_bobble_nameinput_background.png" // ���� �ʿ�
	)
	.addInputBox
	(
		InputBox("Name", "#000000", "#FFFFFF", 72.0, true, Range(400, 200, 900, 272))
		.addInputBoxFunc
		(
			nameInputPageInputBox
		)
	)
	.addButton
	(
		Button("image/button2.png", "Enter", "#591010", 36.0, Range(950, 200, 1200, 300))
		.addButtonFunc
		(
			nameInputPageButton
		)
		.addStyleFunc
		(
			buttonStyle
		)
	)
	.addKeyboardFunc
	(
		nameInputPageKeyboard
	);

	mapEditorPage
	.addCanvas({
		Canvas(Range(0, 0, 700, 300), Range(0, 0, 700, 300))
		.addDrawFunc
		(
			mapEditorPageDraw1
		)
		.addKeyboardFunc
		(
			mapEditorPageKeyboard1
		),
		Canvas(Range(750, 50, 1550, 850), Range(0, 0, 320, 320))
		})
	.addText
	({
		Text("     Map name:\n  # of stages:\nWorking stage:", "#FFFFFF\n", "", 30.0, Range(50, 600, 320, 850)),

		Text("Layer:", "#FFFFFF\n", "", 30.0, Range(50, 560, 200, 590)),

		Text("Mode:", "#FFFFFF\n", "", 30.0, Range(50, 410, 150, 440))

		})
	.addButton
	({
		Button("image/button2.png", "Back", "#000000", 20.0, Range(10, 815, 85, 890))
		.addButtonFunc
		(
			[]() -> void { window.setPage("startingPage"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Save", "#591010", 36.0, Range(350, 600, 500, 700))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("Save"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Play", "#591010", 36.0, Range(550, 600, 700, 700))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("Play"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),

		Button("image/button2.png", "Theme/Tile", "#591010", 24.0, Range(50, 450, 240, 550))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("LayerTheme"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Character", "#591010", 24.0, Range(280, 450, 470, 550))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("LayerCharacter"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Current", "#591010", 24.0, Range(510, 450, 700, 550))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("LayerCurrent"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),

		Button("image/button2.png", "Theme/Tile", "#591010", 24.0, Range(50, 300, 240, 400))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("ModeTheme"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Character", "#591010", 24.0, Range(280, 300, 470, 400))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("ModeCharacter"); }
		)
		.addStyleFunc
		(
			buttonStyle
		),
		Button("image/button2.png", "Current", "#591010", 24.0, Range(510, 300, 700, 400))
		.addButtonFunc
		(
			[]() -> void { mapEditorPageButton("ModeCurrent"); }
		)
		.addStyleFunc
		(
			buttonStyle
		)
		})
	.addInputBox
	({
		InputBox("Map name", "#000000", "#FFFFFF", 30.0, false, Range(350, 820, 700, 850)),
		InputBox("# of stages", "#000000", "#FFFFFF", 30.0, false, Range(350, 772, 700, 802)),
		InputBox("Working stage", "#000000", "#FFFFFF", 30.0, false, Range(350, 722, 700, 754))
	});


	window
	.addPage
	({
		startingPage,
		helpPage,
		scoreboardPage,
		storyPage,
		customPage,
		selectionPage,
		gamePage,
		gameOverPage,
		gameWinPage,
		nameInputPage,
		mapEditorPage
	});

	

	window.mainLoop("startingPage");

	return 0;
}

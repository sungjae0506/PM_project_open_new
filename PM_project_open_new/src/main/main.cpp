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
Page selectingPage("selectingPage", Range(0, 0, 1600, 900));
Page gamePage("gamePage", Range(0, 0, 1600, 900));
Page gameOverPage("gameOverPage", Range(0, 0, 1600, 900));
Page gameWinPage("gameWinPage", Range(0, 0, 1600, 900));
Page scoreboardPage("scoreboardPage", Range(0, 0, 1600, 900));




int main(int argc, char** argv)
{


	window("Bubble Bobble", &argc, argv, 50, 50, WIDTH, HEIGHT);

	

	gamePage
	.addBackground
	(
		"image/snu.png"
	)
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
		gamePage
	});

	window.mainLoop("gamePage");

	return 0;
}

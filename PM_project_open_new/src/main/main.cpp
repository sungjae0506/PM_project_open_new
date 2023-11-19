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
Page gamePage("gamePage", Range(0, 0, 1600, 900));

int main(int argc, char** argv) 
{
	window("Bubble Bobble", &argc, argv, 50, 50, WIDTH, HEIGHT);
	
	gamePage
	.addCanvas
	(
		Canvas(Range(250, 0, 1350, 900), Range(0, 20, 320, 280))
		.addDrawFunc
		(
			gameMapDraw
		)
	)
	.addText
	(
		Text("wow!", "#FFFFFF", "", 32.0, Range(0, 0, 320, 40))
	);

	window
	.addPage
	({
		gamePage
	});

	window.mainLoop("gamePage");

	return 0;
}
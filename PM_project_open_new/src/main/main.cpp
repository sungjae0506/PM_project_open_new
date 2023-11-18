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
Page gamePage("gamePage", Range(0, 0, 320, 320));

int main(int argc, char** argv) 
{
	window("Bubble Bobble", &argc, argv, 300, 300, WIDTH, HEIGHT);
	
	gamePage.
	addCanvas
	(
		Canvas(Range(0, 0, 320, 320), Range(0, 0, 320, 320))
	);

	window
	.addPage
	({
		gamePage
	});

	window.mainLoop("gamePage");

	return 0;
}
#include "callback.h"

#pragma once
#include "../util/object.h"
#include "../UI/event.h"
#include "../game/game_manager.h"
#include "../UI/window.h"
#include "../asset/image_manager.h"

GameManager gameManager;
static ImageManager imageManager("image_data.json");
extern Window window;

void startingPageKeyboard(KeyboardEvent e, string key, Point pos)
{
	if (e == KeyboardDown)
	{
		if (key == " ")
		{
			window.setPage("storyPage");
		}
		if (key == "h" || key == "H")
		{
			window.setPage("helpPage");
		}
		if (key == "s" || key == "S")
		{
			window.setPage("scoreboardPage");
		}
		if (key == "c" || key == "C")
		{
			window.setPage("customPage");
		}
	}
}

int storyPageTick = 0;
vector<Image> storyPageImages;

void storyPageDraw(Point pos)
{
	double mask = 0.0;
	Range range(0, 0, 1600, 900);
	
	storyPageImages[storyPageTick / 300].draw();
	switch (storyPageTick % 300 / 100)
	{
	case 0:
		mask = (100 - storyPageTick % 100) / 100.0;
		break;
	case 1:
		mask = 0.0;
		break;
	case 2:
		mask = (storyPageTick % 100) / 100.0;
		break;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.0, 0.0, 0.0, mask);
	glBegin(GL_QUADS);
	glVertex2f(range.point0.x, range.point0.y);
	glVertex2f(range.point1.x, range.point0.y);
	glVertex2f(range.point1.x, range.point1.y);
	glVertex2f(range.point0.x, range.point1.y);
	glEnd();

	glDisable(GL_BLEND);

}
void storyPageKeyboard(KeyboardEvent e, string key, Point pos)
{
	if (e == KeyboardDown)
	{
		if (key == " ")
		{
			window.setPage("selectionPage");
		}
	}
}

void storyPageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		storyPageTick = 0;
		storyPageImages = imageManager.getImages("story");
	}
	else if (e == IdleRunning)
	{
		++storyPageTick;
	}

	if (storyPageTick >= storyPageImages.size() * 300)
	{
		window.setPage("selectionPage");
		return;
	}
}

int selectionMode = 1;
vector<int> selectionState;


void selectionPageDraw(Point pos)
{
	for (int i = 0; i < 3; ++i)
	{
		if (selectionState[i] == 1)
		{
			glColor3f(1.0, 0.0, 0.0);
		}
		if (selectionState[i] == 2)
		{
			glColor3f(0.0, 0.0, 1.0);
		}
		if (selectionState[i])
		{
			glLineWidth(5.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(450.0 + i * 250, 200.0);
			glVertex2f(450.0 + i * 250, 400.0);
			glVertex2f(650.0 + i * 250, 400.0);
			glVertex2f(650.0 + i * 250, 200.0);
			glEnd();
		}
		
	}
}

void selectionPageButton(string bt)
{
	
	if (bt == "1P")
	{
		selectionMode = 1;
	}
	if (bt == "2P")
	{
		selectionMode = 2;
	}
	if (bt == "player1")
	{
		for (auto& i : selectionState)
			if (i >= selectionMode)
				i = 0;
		selectionState[0] = (selectionMode - 1) * (2 - selectionState[0]) + (2 - selectionMode);
	}
	if (bt == "player2")
	{
		for (auto& i : selectionState)
			if (i >= selectionMode)
				i = 0;
		selectionState[1] = (selectionMode - 1) * (2 - selectionState[1]) + (2 - selectionMode);
	}
	if (bt == "player3")
	{
		for (auto& i : selectionState)
			if (i >= selectionMode)
				i = 0;
		selectionState[2] = (selectionMode - 1) * (2 - selectionState[2]) + (2 - selectionMode);
	}
	for (auto& i : selectionState)
		i %= (selectionMode + 1);
}

void selectionPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		if (key == " ")
		{
			window.setPage("gamePage");
		}
	}
}

void selectionPageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		selectionState.clear();
		selectionState.resize(3);
		selectionState[0] = 1;
		selectionMode = 1;
	}
}





void gamePageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{

		gameManager.clear();

		gameManager.readMap("stage1.json");
		gameManager.readMap("stage2.json");

		gameManager.begin(2);
		printf("ok");
	}
}

void gameManagerDraw(Point mousePos)
{
	gameManager.draw(mousePos);
}

void gameManagerIdle(IdleEvent e)
{
	gameManager.idleEvent(e);
}

void gameManagerKeyboard(KeyboardEvent e, string key, Point p)
{
	gameManager.keyboardEvent(e, key, p);
}






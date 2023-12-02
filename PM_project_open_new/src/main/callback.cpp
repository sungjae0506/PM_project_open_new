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

void buttonStyle(Button* b)
{
	switch (b->buttonState)
	{
	case b->None:
		(b->buttonImage).draw();
		(b->buttonText).draw();
		break;
	case b->OnButton:
	case b->Clicked:
		Image("image/button2_pushed.png", b->buttonImage.range).draw(); //일반화..?는 일단 제끼고 구현만 해놓음 ㅋㅋㅋㅋㅋㅋ ㅇㅋ
		(b->buttonText + Point(0, -10)).draw();
		break;
	}
}

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

void scoreboardPageDraw(Point pos)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 800.0);
	glVertex2f(700.0, 800.0);
	glVertex2f(700.0, 0.0);
	glEnd();

	/*
	Text("Score Board", "#000000", "", 72.0, Range(100, 710, 600, 800)).draw();
	Text("1", "#FFD700", "", 72.0, Range(0, 576, 50, 648)).draw();
	Text("2", "#C0C0C0", "", 72.0, Range(0, 432, 50, 504)).draw();
	Text("3", "#16FFFF", "", 72.0, Range(0, 288, 50, 360)).draw();
	Text("4", "#16FFFF", "", 72.0, Range(0, 144, 50, 216)).draw();
	Text("5", "#16FFFF", "", 72.0, Range(0,   0, 50,  72)).draw();
	Text("", "#16FFFF", "", 45.0, Range(150, 0, 600, 648))
	.addTextFunc
	(
		scoreboardPageText
	)
	.draw();*/
}

string scoreboardPageText(void)
{
	return "yumin : 10000\n\nhsj   : 10000\n\nhsj   : 10000\n\nhsj   : 10000\n\nhsj   : 10000\n\n";
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
		for (auto& i : selectionState)
			if (i == 2)
				i = 0;
	}
	if (bt == "2P")
	{
		selectionMode = 2;
	}
	if (bt == "player1")
	{
		if (selectionMode == 1)
		{
			for (auto& i : selectionState)
				i = 0;
			selectionState[0] = 1;
		}
		else
		{
			if (selectionState[0] == 0)
			{
				for (auto& i : selectionState)
					if (i == 2)
						i = 0;
				selectionState[0] = 2;
			}
			else if (selectionState[0] == 2)
			{
				selectionState[0] = 0;
			}
		}
	}
	if (bt == "player2")
	{
		if (selectionMode == 1)
		{
			for (auto& i : selectionState)
				i = 0;
			selectionState[1] = 1;
		}
		else
		{
			if (selectionState[1] == 0)
			{
				for (auto& i : selectionState)
					if (i == 2)
						i = 0;
				selectionState[1] = 2;
			}
			else if (selectionState[1] == 2)
			{
				selectionState[1] = 0;
			}
		}
	}
	if (bt == "player3")
	{
		if (selectionMode == 1)
		{
			for (auto& i : selectionState)
				i = 0;
			selectionState[2] = 1;
		}
		else
		{
			if (selectionState[2] == 0)
			{
				for (auto& i : selectionState)
					if (i == 2)
						i = 0;
				selectionState[2] = 2;
			}
			else if (selectionState[2] == 2)
			{
				selectionState[2] = 0;
			}
		}
	}
}

void selectionPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		if (key == " ")
		{
			window.setPage("gamePage");
		}
		if (key == "1")
		{
			selectionPageButton("1P");
		}
		if (key == "2")
		{
			selectionPageButton("2P");
		}
		if (key == "LEFT")
		{
			if (selectionMode == 1)
			{
				int cur = -1;
				for (int i = 0; i < 3; ++i)
				{
					if (selectionState[i] == 1)
					{
						selectionState[i] = 0;
						cur = i;
					}
				}
				selectionState[(cur + 2) % 3] = 1;
			}
			else
			{
				int cur = -1;
				for (int i = 0; i < 3; ++i)
				{
					if (selectionState[i] == 2)
					{
						selectionState[i] = 0;
						cur = i;
					}
				}
				if (cur == -1)
				{
					for (int i = 0; i < 3; ++i)
					{
						if (selectionState[i] == 0)
						{
							selectionState[i] = 2;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < 3; ++i)
					{
						if (selectionState[i] == 0 && i != cur)
						{
							selectionState[i] = 2;
							break;
						}
					}
				}
			}
		}
		if (key == "RIGHT")
		{
			if (selectionMode == 1)
			{
				int cur = -1;
				for (int i = 0; i < 3; ++i)
				{
					if (selectionState[i] == 1)
					{
						selectionState[i] = 0;
						cur = i;
					}
				}
				selectionState[(cur + 1) % 3] = 1;
			}
			else
			{
				int cur = -1;
				for (int i = 0; i < 3; ++i)
				{
					if (selectionState[i] == 2)
					{
						selectionState[i] = 0;
						cur = i;
					}
				}
				if (cur == -1)
				{
					for (int i = 0; i < 3; ++i)
					{
						if (selectionState[i] == 0)
						{
							selectionState[i] = 2;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < 3; ++i)
					{
						if (selectionState[i] == 0 && i != cur)
						{
							selectionState[i] = 2;
							break;
						}
					}
				}
			}
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

string selectionPageText(void)
{
	if (selectionMode == 1)
		return "Select 1P";
	else
		return "Select 2P";
}





void gamePageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{

		gameManager.clear();

		gameManager.readMap("stage1.json");
		gameManager.readMap("stage2.json");

		int playerNum = 0;
		for (auto& i : selectionState)
		{
			if (i != 0)
				++playerNum;
		}
		gameManager.begin(playerNum);
		for (int i = 0; i < playerNum; ++i)
		{
			for (int j = 0; j < selectionState.size(); ++j)
			{
				if (selectionState[j] == (i + 1))
				{
					switch (j)
					{
					case 0:
						gameManager.players[i].setImages(imageManager.getImages("player1"));
						break;
					case 1:
						gameManager.players[i].setImages(imageManager.getImages("player2"));
						break;
					case 2:
						gameManager.players[i].setImages(imageManager.getImages("player3"));
						break;
					}
				}
			}
		}
		

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
	string st = gameManager.getState();

	if (e == IdleRunning)
	{
		if (st == "GameEnding")
		{
			window.setPage("gameWinPage");
		}
		else if (st == "GameOver")
		{
			printf("gaov");
			window.setPage("gameOverPage");
		}
	}
}

void gameManagerKeyboard(KeyboardEvent e, string key, Point p)
{
	gameManager.keyboardEvent(e, key, p);
}






void gameOverPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		window.setPage("startingPage");
	}
}

void gameWinPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		window.setPage("scoreboardPage");
	}
}





void scoreBoardDraw(Point pos)
{

}
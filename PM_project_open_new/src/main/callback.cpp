#pragma once
#pragma warning(disable:4996)
#include "callback.h"
#include <vector>
#include "../util/object.h"
#include "../UI/event.h"
#include "../game/game_manager.h"
#include "../UI/window.h"
#include "../asset/image_manager.h"
using namespace std;

GameManager gameManager;
static ImageManager imageManager("image_data.json");
extern Window window;
int tick;

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
		Image("image/button2_pushed.png", b->buttonImage.range).draw();
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

json scoreboardData;

void scoreboardPageDraw(Point pos)
{
	vector<vector<string>> arr;
	json temp;
	arr.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		temp = scoreboardData["data"][i]["character"];
		for (auto& j : temp)
		{
			arr[i].push_back(j.get<string>());
		}
	}
	
	Point cursor;

	for (int i = 0; i < 5; ++i)
	{
		cursor(0, 648 - 144 * i);
		for (auto& j : arr[i])
		{
			auto image = imageManager.getImages(j)[0];
			image.range(0, -48, 48, 0);
			(image + cursor).draw();
			cursor += Point(50, 0);
		}
	}
}

string scoreboardPageText(void)
{
	vector<pair<string, int>> arr;
	arr.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		arr[i].first = scoreboardData["data"][i]["name"].get<string>();
		arr[i].second = scoreboardData["data"][i]["score"].get<int>();
	}
	char c_str[30];
	string str;
	for (int i = 0; i < 5; ++i)
	{
		sprintf(c_str, "%-10s %06d\n\n", arr[i].first.c_str(), arr[i].second);
		str += c_str;
	}
	return str;
}

void scoreboardPageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		fstream f("scoreboard.json");
		scoreboardData = json::parse(f);
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
		fstream f("scoreboard.json");
		scoreboardData = json::parse(f);

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
		if (scoreboardData["data"][4]["score"].get<int>() < gameManager.score)
			window.setPage("nameInputPage");
		else
			window.setPage("scoreboardPage");
	}
}

void gameOverPageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		tick = 0;
	}
	if (e == IdleRunning)
	{
		if (++tick >= 1000)
		{
			if (scoreboardData["data"][4]["score"].get<int>() < gameManager.score)
				window.setPage("nameInputPage");
			else
				window.setPage("scoreboardPage");
		}
	}
}

void gameWinPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		if (scoreboardData["data"][4]["score"].get<int>() < gameManager.score)
			window.setPage("nameInputPage");
		else
			window.setPage("scoreboardPage");
			
	}
}

void gameWinPageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		tick = 0;
	}
	if (e == IdleRunning)
	{
		if (++tick >= 1000)
		{
			if (scoreboardData["data"][4]["score"].get<int>() < gameManager.score)
				window.setPage("nameInputPage");
			else
				window.setPage("scoreboardPage");
		}
	}
}

string gameManagerText(string mode)
{
	char c_str[30];
	
	if (mode == "Highscore")
	{
		sprintf(c_str, "%06d", max(gameManager.score, scoreboardData["data"][0]["score"].get<int>()));
	}
	else if (mode == "Score")
	{
		sprintf(c_str, "%06d", gameManager.score);
	}
	return string(c_str);
}

string playerName;

void nameInputPageInputBox(string str)
{
	playerName = str;
}

void nameInputPageButton(void)
{
	json dumpData;
	dumpData = scoreboardData;
	int rank = 0;
	for (int i = 0; i < 5; ++i)
	{
		if (gameManager.score > scoreboardData["data"][i]["score"].get<int>())
		{
			rank = i;
			break;
		}
	}
	for (int i = 4; i > rank; --i)
	{
		dumpData["data"][i] = dumpData["data"][i - 1];
	}
	dumpData["data"][rank]["name"] = playerName;
	dumpData["data"][rank]["score"] = gameManager.score;

	json arr = json::array();

	for (int i = 1; i <= 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (selectionState[j] == i)
			{
				switch (j)
				{
				case 0:
					arr.push_back("player1");
					break;
				case 1:
					arr.push_back("player2");
					break;
				case 2:
					arr.push_back("player3");
					break;
				}
			}
		}
	}

	dumpData["data"][rank]["character"] = arr;
	

	fstream f("scoreboard.json", ios::out | ios::trunc);
	f << dumpData.dump(2);

	window.setPage("scoreboardPage");
}

void nameInputPageKeyboard(KeyboardEvent e, string key, Point p)
{
	if (e == KeyboardDown)
	{
		cout << (int)key.c_str()[0] << endl;
		if (key.c_str()[0] == 13)
		{
			nameInputPageButton();
		}
	}
}

void mapEditorPageDraw1(Point pos)
{

}

void mapEditorPageKeyboard1(KeyboardEvent e, string key, Point p)
{

}

void mapEditorPageButton(string bt)
{

}
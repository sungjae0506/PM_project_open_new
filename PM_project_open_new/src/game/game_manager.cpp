#include "game_manager.h"

void GameManager::clear()
{
	playerNum = 0;

	maps.clear();
	characters.clear();

	players.clear();
	bubbles.clear();
	enemies.clear();

	mainTick = 0;
	internalTick = 0;
}

void GameManager::changeState() // state machine 구현 예정
{
	if (state == "MapStarting")
	{
		if (internalTick >= 100)
		{
			state = "MapRunning";
			internalTick = 0;
		}
	}

	if (state == "MapChanging")
	{
		if (internalTick >= 100)
		{
			state = "MapRunning";
			internalTick = 0;
		}
	}

}

// ////////////////////////////////////////////////////////////// 

void GameManager::addMap(string path)
{
	Map temp;
	
	temp.readMap(path);
	maps.push_back(temp);
}

void GameManager::addCharacter(string path)
{
	Character temp;
	temp.readCharacter(path);
	characters.push_back(temp);
}

void GameManager::load(int n)
{
	playerNum = n;
	mainTick = 0;
	internalTick = 0;
	currentStage = 0;
	currentMap = maps[0];

	if (n == 1)
	{
		players.resize(1);
		players[0].setPos(player1Start);
		players[0].setAcc(gravity);
	}
	if (n == 2)
	{
		players.resize(2);
		players[0].setPos(player1Start);
		players[0].setAcc(gravity);
		players[1].setPos(player2Start);
		players[1].setAcc(gravity);
	}

	state = "MapStarting";
}

// //////////////////////////////////////////////////////////////


void GameManager::move()
{
	for (auto& i : players)
	{
		i.move();
		i.collisionHandling(currentMap);
	}

}

void GameManager::drawEntity(int& internalTick)
{
	for (auto& i : players)
		i.draw(internalTick);
}

void GameManager::drawMap()
{
	//currentMap.draw();
	currentMap.platform.print();
}

void GameManager::drawMap(double stage)
{

}

void GameManager::keyboardEvent(KeyboardEvent e, string key, Point p)
{
	bool setState;
	if (e == KeyboardDown)
		setState = true;
	else
		setState = false;

	if (playerNum == 1 || playerNum == 2)
	{
		if (key == "w")
			players[0].setKeyboardState(0, setState);
		if (key == "s")
			players[0].setKeyboardState(1, setState);
		if (key == "a")
			players[0].setKeyboardState(2, setState);
		if (key == "d")
			players[0].setKeyboardState(3, setState);
		if (key == " ")
			players[0].setKeyboardState(4, setState);
		players[0].updateKeyboardState();
	}
	if (playerNum == 2)
	{
		if (key == "UP")
			players[1].setKeyboardState(0, setState);
		if (key == "DOWN")
			players[1].setKeyboardState(1, setState);
		if (key == "LEFT")
			players[1].setKeyboardState(2, setState);
		if (key == "RIGHT")
			players[1].setKeyboardState(3, setState);
		if (key.c_str()[0] == 13)
			players[1].setKeyboardState(4, setState);
		players[1].updateKeyboardState();
	}
	
}

void GameManager::idleEvent(IdleEvent e)
{
	//cout << state << endl;
	if (state == "MapStarting")
	{
		if (playerNum == 1)
		{
			players[0].setPos(((1.0 - internalTick / 100.0) * player1Start) + ((internalTick / 100.0) * characters[0].players[0].getPos()));
		}
		if (playerNum == 2)
		{
			players[0].setPos(((1.0 - internalTick / 100.0) * player1Start) + ((internalTick / 100.0) * characters[0].players[0].getPos()));
			players[1].setPos(((1.0 - internalTick / 100.0) * player2Start) + ((internalTick / 100.0) * characters[0].players[1].getPos()));
		}
	}
	if (state == "MapRunning")
	{
		players[0].updateKeyboardState();
		if (playerNum == 2)
			players[1].updateKeyboardState();

		move();
	}
	if (state == "MapChanging")
	{

	}

	changeState();
	++mainTick;
	if (state != "Stop")
		++internalTick;
}

void GameManager::draw(Point mousePos)
{
	if (state == "MapStarting" || state == "MapRunning")
	{
		drawMap();
		drawEntity(internalTick);
	}
	if (state == "MapChanging")
	{
		
	}
}
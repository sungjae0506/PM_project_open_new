#include "game_manager.h"

void GameManager::clear()
{
	playerNum = 0;

	maps.clear();
	characters.clear();

	players.clear();
	bubbles.clear();
	enemies.clear();

	while (!bubbleResourceQueue.empty())
		bubbleResourceQueue.pop();
	bubblePopVector.clear();
	while (!bubblePopQueue.empty())
		bubblePopQueue.pop();
	bubbleAdjVector.clear();

	mainTick = 0;
	internalTick = 0;
}

void GameManager::setState(string s)
{
	internalTick = 0;
	state = s;
}

string GameManager::getState(void)
{
	return state;
}

void GameManager::changeState() // state machine 구현 예정
{
	if (getState() == "MapStarting")
	{
		if (internalTick >= 100)
		{
			setState("MapRunning");
		}
	}
	else if (getState() == "MapRunning")
	{

	}
	else if (getState() == "MapChanging")
	{
		if (internalTick >= 100)
		{
			setState("MapRunning");
		}
	}

}

void GameManager::incTick(void)
{
	++mainTick;
	if (getState() != "Stop")
		++internalTick;
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

	bubbles.resize(bubbleMax);
	for (int i = 0; i < bubbleMax; ++i)
		bubbles[i].setState("Killed");
	for (int i = 0; i < bubbleMax; ++i)
		bubbleResourceQueue.push(i);
	bubblePopVector.resize(bubbleMax);
	bubbleAdjVector.resize(bubbleMax);
	for (int i = 0; i < bubbleMax; ++i)
	{
		bubbleAdjVector[i].resize(bubbleMax);
		for (int j = 0; j < bubbleMax; ++j)
			bubbleAdjVector[i][j] = false;
	}

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

	setState("MapStarting");
}

// //////////////////////////////////////////////////////////////


void GameManager::move()
{
	int temp;

	for (int i = 0; i < bubbleMax; ++i)
		bubblePopVector[i] = false;
	while (!bubblePopQueue.empty())
		bubblePopQueue.pop();
	for (int i = 0; i < bubbleMax; ++i)
		if (bubbles[i].getState() == "Killed")
			bubbleResourceQueue.push(i);

	for (auto& i : players)
	{
		
		i.updateKeyboardState();
		i.move();
		i.collisionHandling(currentMap); 
		i.onBubble = false;
		for (int j = 0; j < bubbles.size(); ++j)
		{
			if (i.collisionDetection(bubbles[j]))
			{
				bubblePopVector[j] = true;
			}
			if (i.bubbleJumpDetection(bubbles[j]))
			{
				i.onBubble = true;
			}
		}
	}
	for (auto& i : bubbles)
	{
		i.airCurrentHandling(currentMap);
		i.move();
		i.collisionHandling(currentMap);
		i.playerCollisionState = false;
	}
	
	for (int i = 0; i < bubbleMax - 1; ++i)
	{
		for (int j = i + 1; j < bubbleMax; ++j)
		{
			bubbleAdjVector[i][j] = bubbleAdjVector[j][i] = bubbles[i].collisionDetection(bubbles[j]);
		}
	}
	for (int i = 0; i < bubbleMax - 1; ++i)
	{
		for (int j = i + 1; j < bubbleMax; ++j)
		{
			if (bubbleAdjVector[i][j])
			{
				bubbles[i].collisionHandling(bubbles[j]);
			}
		}
	}
	for (int i = 0; i < bubbleMax; ++i)
	{
		if (bubblePopVector[i])
		{
			bubblePopQueue.push(i);
		}
	}
	while (!bubblePopQueue.empty())
	{
		temp = bubblePopQueue.front();
		bubblePopQueue.pop();
		bubblePopVector[temp] = true;
		bubbles[temp].playerCollisionState = true;
		for (int i = 0; i < bubbleMax; ++i)
		{
			if (bubbleAdjVector[temp][i] && bubblePopVector[i] == false)
			{
				bubblePopQueue.push(i);
			}
		}
	}
	
	for (auto& i : enemies)
	{
		//i.move();
		//i.collisionHandling(currentMap);
	}
	//cout << players[0].getBubbleState() << " " << bubbles.size() << endl;

	for (auto& i : players)
	{
		i.pushWall = false;
		if (i.getBubbleState() == "ShootBubble")
		{	
			printf("%d %d\n", bubbles.size(), bubbleResourceQueue.front());
			if (!bubbleResourceQueue.empty())
			{
				
				bubbles[bubbleResourceQueue.front()] = (i.shootBubble(currentMap));
				bubbleResourceQueue.pop();
			}
		}
	}

	for (auto &i: players)
		i.incTick();
	for (auto& i : bubbles)
		i.incTick();
	//for (auto& i : enemies)
	//	i.incTick();

	for (auto& i : players)
		i.changeState();
	for (auto& i : bubbles)
		i.changeState();
	//for (auto& i : enemies)
	//	i.changeState();
}

void GameManager::drawEntity(void)
{
	for (auto& i : players)
		i.draw();

	for (auto& i : bubbles)
		i.draw();

}

void GameManager::drawMap()
{
	currentMap.draw();
	//currentMap.platform.print();
	//currentMap.wall.print();
	
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

int testClock, testTick, prevClock, prevTick;

void GameManager::idleEvent(IdleEvent e)
{
	testClock = clock() / 1000;
	testTick = mainTick;

	if (testClock != prevClock)
	{
		printf("%d Tick\n", testTick - prevTick);
		prevClock = testClock;
		prevTick = testTick;
	}

	if (getState() == "MapStarting")
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
	if (getState() == "MapRunning")
	{
		move();
	}
	if (getState() == "MapChanging")
	{

	}

	incTick();
	changeState();
}

void GameManager::draw(Point mousePos)
{
	if (state == "MapStarting" || state == "MapRunning")
	{
		drawMap();
		drawEntity();
	}
	if (state == "MapChanging")
	{
		drawEntity();
	}
}
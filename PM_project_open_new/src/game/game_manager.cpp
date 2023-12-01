#include "game_manager.h"

static ImageManager imageManager("image_data.json");

void GameManager::clear()
{
	playerNum = 0;

	maps.clear();
	players.clear();
	bubbles.clear();
	enemies.clear();
	enemyAI.clear();

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
	string st = getState();
	if (st == "MapLoading")
	{
		setState("MapChanging");
	}
	else if (st == "MapChanging")
	{
		if (internalTick >= (int)(idlePerSecond * mapChangingTime))
		{
			setState("MapRunning");
		}
	}
	else if (st == "MapRunning")
	{
		if (enemyCnt == 0)
		{
			if (currentStage == maps.size())
			{
				setState("GameEnding");
			}
			else
			{
				setState("MapLoading");
			}
		}
		if (playerCnt == 0)
		{
			setState("GameOver");
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

void GameManager::begin(int n)
{
	playerNum = n;
	mainTick = 0;
	internalTick = 0;
	currentStage = 0;

	enemies.clear();
	enemyAI.clear();

	bubbles.resize(bubbleMax);
	for (int i = 0; i < bubbleMax; ++i)
	{
		bubbles[i] = Bubble();
		bubbles[i].setState("Killed");
	}

	while (!bubbleResourceQueue.empty())
		bubbleResourceQueue.pop();
	for (int i = 0; i < bubbleMax; ++i)
		bubbleResourceQueue.push(i);

	bubblePopVector.resize(bubbleMax);
	for (int i = 0; i < bubbleMax; ++i)
		bubblePopVector[i] = false;

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

	setState("MapLoading");
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
	for (auto& i : enemies)
	{
		i.bubbleCollisionState = false;
		i.bubblePop = false;
		i.bubbleTimeout = false;
	}

	for (auto& i : players)
	{
		
		i.updateKeyboardState();
		i.move();
		for (auto& j : bubbles)
		{
			i.bubblePushHandling(j);
		}
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
		i.enemyCollisionState = false;
		for (auto& j : enemies)
		{
			if (i.collisionDetection(j))
			{
				i.enemyCollisionState = true;
			}
		}
	}
	for (auto& i : bubbles)
	{
		i.bubbleCurrentHandling(currentMap);
		i.move();
		i.collisionHandling(currentMap);
		i.enemyCollisionState = false;
		i.playerCollisionState = false;
		for (auto& j : enemies)
		{
			i.collisionHandling(j);
		}
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
	
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemyAI[i].pathfinding(enemies[i], players, currentMap);
		enemies[i].move();
		enemies[i].collisionHandling(currentMap);
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

	for (auto& i : players)
	{
		if (i.getState() == "EnemyCollision")
		{
			--i.HP;
		}
	}

	playerCnt = 0;
	for (auto& i: players)
	{
		if (i.getState() != "Killed")
			++playerCnt;
	}

	enemyCnt = 0;
	for (auto& i : enemies)
	{
		if (i.getState() != "Killed")
			++enemyCnt;
	}

	for (auto &i: players)
		i.incTick();
	for (auto& i : bubbles)
		i.incTick();
	for (auto& i : enemies)
		i.incTick();

	for (auto& i : players)
		i.changeState();
	for (auto& i : bubbles)
		i.changeState();
	for (auto& i : enemies)
		i.changeState();
}

void GameManager::drawEntity(void)
{
	for (auto& i : players)
		i.draw();
	for (auto& i : bubbles)
		i.draw();
	for (auto& i : enemies)
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
	if (stage <= 1.0)
	{
		maps[0].draw();
		return;
	}
	int prevStage = (int)(stage) - 1;
	glPushMatrix();
	glTranslatef(0, 320.0 * ((stage - 1) - prevStage), 0);
	maps[prevStage].draw();
	glTranslatef(0, -320.0, 0);
	maps[prevStage + 1].draw();
	glPopMatrix();
}

void GameManager::drawHeart(void)
{
	if (playerNum == 1)
	{
		for (int i = 0; i < players[0].HP; ++i)
			(heartImage[0] + Point(10 * i, 20)).draw();
	}
	if (playerNum == 2)
	{
		for (int i = 0; i < players[0].HP; ++i)
			(heartImage[0] + Point(10 * i, 20)).draw();
		for (int i = 1; i <= players[1].HP; ++i)
			(heartImage[1] + Point(320 - 10 * i, 20)).draw();
	}
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
		//players[0].updateKeyboardState();
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
		//players[1].updateKeyboardState();
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

	string st = getState();

	if (st == "MapLoading")
	{
		++currentStage;
		currentMap = maps[currentStage - 1];

		for (auto& i : players)
		{
			for (int j = 0; j < 5; ++j)
				i.keyboardState[j] = 0;
			i.setVel(Point(0, 0));
		}

		prevSetting.clear();

		if (playerNum == 1)
		{
			prevSetting.addPlayerPos(players[0].getPos());
		}
		else if (playerNum == 2)
		{
			prevSetting.addPlayerPos(players[0].getPos());
			prevSetting.addPlayerPos(players[1].getPos());
		}
	
		for (int i = 0; i < bubbleMax; ++i)
		{
			bubbles[i] = Bubble();
			bubbles[i].setState("Killed");
		}
		while (!bubbleResourceQueue.empty())
			bubbleResourceQueue.pop();
		for (int i = 0; i < bubbleMax; ++i)
			bubbleResourceQueue.push(i);
		for (int i = 0; i < bubbleMax; ++i)
			bubblePopVector[i] = false;
		for (int i = 0; i < bubbleMax; ++i)
			for (int j = 0; j < bubbleMax; ++j)
				bubbleAdjVector[i][j] = false;

		enemies.clear();
		enemyAI.clear();
		for (int i = 0; i < initialSettings[currentStage - 1].enemyPos.size(); ++i)
		{
			auto tempEnemy = Enemy();
			tempEnemy.setPos(Point(initialSettings[currentStage - 1].enemyPos[i].x, 320.0));
			prevSetting.addEnemyPos(tempEnemy.getPos());
			tempEnemy.setName(initialSettings[currentStage - 1].enemyName[i]);

			// 이미지도 추가 필요
			
			auto tempEnemyAI = EnemyAI();
			if (tempEnemy.getName() == "enemy1")
			{
				tempEnemyAI.setMode("MODE1");
			}
			if (tempEnemy.getName() == "enemy2")
			{
				tempEnemyAI.setMode("MODE2");
			}
			if (tempEnemy.getName() == "enemy3")
			{
				tempEnemyAI.setMode("MODE3");
			}
			if (tempEnemy.getName() == "enemy4")
			{
				tempEnemyAI.setMode("MODE4");
			}
			tempEnemyAI.enemyInit(tempEnemy);
			enemies.push_back(tempEnemy);
			enemyAI.push_back(tempEnemyAI);
			
		}
		enemyCnt = enemies.size();

		heartImage = imageManager.getImages("heart");
	}
	else if (getState() == "MapChanging")
	{
		for (int i = 0; i < players.size(); ++i)
		{
			players[i].setPos(((1.0 - (internalTick + 1) / (idlePerSecond * mapChangingTime)) * prevSetting.playerPos[i]) + (((internalTick + 1) / (idlePerSecond * mapChangingTime)) * initialSettings[currentStage - 1].playerPos[i]));
		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[i].setPos(((1.0 - (internalTick + 1) / (idlePerSecond * mapChangingTime)) * prevSetting.enemyPos[i]) + (((internalTick + 1) / (idlePerSecond * mapChangingTime)) * initialSettings[currentStage - 1].enemyPos[i]));
		}

	}
	else if (getState() == "MapRunning")
	{
		move();
	}
	
	incTick();
	changeState();
}

void GameManager::draw(Point mousePos)
{
	if (state == "MapRunning")
	{
		drawMap();
		drawEntity();
		drawHeart();
	}
	if (state == "MapLoading")
	{
		drawMap();
		drawEntity();
		drawHeart();
	}
	if (state == "MapChanging")
	{
		drawMap((currentStage - 1) + internalTick / (idlePerSecond * mapChangingTime));
		drawEntity();
		drawHeart();
	}
}

void GameManager::readMap(string path)
{
	fstream f(path);
	json jsonData = json::parse(f);
	InitialSetting tempInitialSetting;
	Map tempMap;

	vector<vector<bool>> tempTile;
	vector<vector<char>> tempBubbleCurrent;
	string tempString;

	auto themeData = jsonData["theme"];
	auto playerData = jsonData["player"];
	auto enemyData = jsonData["enemy"];
	auto tileData = jsonData["tile"];
	auto bubbleCurrentData = jsonData["bubble_current"];

	
	for (auto i : playerData)
	{
		tempInitialSetting.addPlayerPos(Point(i["pos"][0].get<double>(), i["pos"][1].get<double>()));
	}
	for (auto i : enemyData)
	{
		tempInitialSetting.addEnemyPos(Point(i["pos"][0].get<double>(), i["pos"][1].get<double>()));
		tempInitialSetting.addEnemyName(i["name"].get<string>());
	}

	tempTile.resize(32);
	for (int i = 0; i < 32; ++i)
		tempTile[i].resize(32);

	for (int i = 0; i < 32; ++i)
	{
		tempString = tileData[i].get<string>();
		for (int j = 0; j < 32; ++j)
			tempTile[i][j] = (tempString[j] == '#');
	}

	tempBubbleCurrent.resize(32);
	for (int i = 0; i < 32; ++i)
		tempBubbleCurrent[i].resize(32);

	for (int i = 0; i < 32; ++i)
	{
		tempString = bubbleCurrentData[i].get<string>();
		for (int j = 0; j < 32; ++j)
			tempBubbleCurrent[i][j] = tempString[j];
	}

	tempMap.tileVector = tempTile;
	tempMap.bubbleCurrentVector = tempBubbleCurrent;
	tempMap.setTile(imageManager.getImages(themeData["tile"].get<string>()));
	tempMap.setBackground(imageManager.getImages(themeData["background"].get<string>()));
	
	Range r(0, 0, 320, 320);
	tempMap.platform = vectorToLines(tempTile, r);
	tempMap.wall.addLine(Line(Point(r.point0.x + 20, r.point0.y), Point(r.point0.x + 20, r.point1.y), Point(1, 0)));
	tempMap.wall.addLine(Line(Point(r.point1.x - 20, r.point0.y), Point(r.point1.x - 20, r.point1.y), Point(-1, 0)));
	tempMap.wall.addLine(Line(Point(r.point0.x + 20, r.point1.y), Point(r.point1.x - 20, r.point1.y), Point(0, -1)));

	initialSettings.push_back(tempInitialSetting);

	maps.push_back(tempMap);

}
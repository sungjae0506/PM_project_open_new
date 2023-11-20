#pragma once
#include "../util/object.h"
#include "../UI/event.h"
#include "../game/game_manager.h"

GameManager gameManager;

void gamePageIdle(IdleEvent e)
{
	if (e == IdleBegin)
	{
		
		gameManager.clear();
		
		gameManager.addMap("map.txt");
		
		gameManager.addCharacter("character.txt");
		
		gameManager.load(1);
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
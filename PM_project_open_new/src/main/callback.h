#pragma once
#include "../util/object.h"
#include "../UI/event.h"
#include "../game/game_manager.h"
#include "../UI/window.h"
#include "../asset/image_manager.h"

void startingPageKeyboard(KeyboardEvent e, string key, Point pos);

void storyPageDraw(Point pos);
void storyPageKeyboard(KeyboardEvent e, string key, Point pos);
void storyPageIdle(IdleEvent e);

void selectionPageDraw(Point pos);
void selectionPageButton(string bt);
void selectionPageKeyboard(KeyboardEvent e, string key, Point p);
void selectionPageIdle(IdleEvent e);

void gamePageIdle(IdleEvent e);
void gameManagerDraw(Point mousePos);
void gameManagerIdle(IdleEvent e);
void gameManagerKeyboard(KeyboardEvent e, string key, Point p);

void scoreBoardDraw(Point pos);
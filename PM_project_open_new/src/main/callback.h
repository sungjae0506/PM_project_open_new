#pragma once
#include "../util/object.h"
#include "../UI/event.h"
#include "../game/game_manager.h"
#include "../UI/window.h"
#include "../asset/image_manager.h"
#include "../asset/sound_loader.h"

void buttonStyle(Button* b);

void startingPageKeyboard(KeyboardEvent e, string key, Point pos);

void storyPageDraw(Point pos);
void storyPageKeyboard(KeyboardEvent e, string key, Point pos);
void storyPageIdle(IdleEvent e);

void scoreboardPageDraw(Point pos);
string scoreboardPageText(void);
void scoreboardPageIdle(IdleEvent e);

void selectionPageDraw(Point pos);
void selectionPageButton(string bt);
void selectionPageKeyboard(KeyboardEvent e, string key, Point p);
void selectionPageIdle(IdleEvent e);
string selectionPageText(void);

void gamePageIdle(IdleEvent e);
void gameManagerDraw(Point mousePos);
void gameManagerIdle(IdleEvent e);
void gameManagerKeyboard(KeyboardEvent e, string key, Point p);
string gameManagerText(string mode);

void gameOverPageKeyboard(KeyboardEvent e, string key, Point p);
void gameOverPageIdle(IdleEvent e);
void gameWinPageKeyboard(KeyboardEvent e, string key, Point p);
void gameWinPageIdle(IdleEvent e);

void nameInputPageInputBox(string str);
void nameInputPageButton(void);
void nameInputPageKeyboard(KeyboardEvent e, string key, Point p);

void mapEditorPageCanvasDraw1(Point pos);
void mapEditorPageCanvasMouse1(MouseEvent e, string button, Point p);
void mapEditorPageCanvasDraw2(Point pos);
void mapEditorPageCanvasMouse2(MouseEvent e, string button, Point p);
void mapEditorPageButton(string bt);
void mapEditorPageIdle(IdleEvent e);
void mapEditorPageInputBox1(string str);
void mapEditorPageInputBox2(string str);
void mapEditorPageInputBox3(string str);

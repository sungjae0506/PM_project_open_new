#pragma once
#include "../util/object.h"

const double idlePerSecond = 200.0;


const double playerHorizontalVel = 80.0;
const double playerJumpVel = 240.0;
const double playerFallingVelLimit = 120.0;

const double bubbleHorizontalVel = 480.0;
const double bubbleVerticalVel = 40.0;
const double bubbleCollisionConst = 10.0;

const double pushWallDist = 4.0;
const int pushWallTick = 10;


const Point player1Start(80.0, 160.0);
const Point player2Start(240.0, 160.0);

const Point gravity(0.0, -620.0);
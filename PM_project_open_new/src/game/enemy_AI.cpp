#include "enemy_AI.h"

EnemyAI::EnemyAI(string _mode)
{
	mode = _mode;
}

void EnemyAI::enemyInit(Enemy& e)
{
	if (mode == "MODE1")
	{
		e.setAcc(gravity);
	}
	if (mode == "MODE2")
	{
		e.setAcc(gravity);
	}
	else if (mode == "MODE3" || mode == "MODE4")
	{
		e.setAcc(Point(0, 0));
	}
}

void EnemyAI::pathfinding(Enemy& e, const vector<Player>& p, const Map &mp)
{
	if (mode == "MODE1")
	{
		if (e.mapCollisionState[1])
		{
			auto res = (e.hitBox + e.getPos()).collisionDetection(mp.platform);
			for (auto& i : res[1])
			{
				if (i.first == Sliding)
				{
					double minX = min(i.second.point0.x, i.second.point1.x);
					double maxX = max(i.second.point0.x, i.second.point1.x);
					
					if (abs(e.getVel()) < EPSILON)
					{
						if (e.getPos().x < 160.0)
						{
							e.setVel(Point(playerHorizontalVel, 0));
						}
						else
						{
							e.setVel(Point(-playerHorizontalVel, 0));
						}
					}

					if (e.getPos().x < minX + 10.0)
					{
						e.setVel(Point(playerHorizontalVel, 0));
					}
					else if (e.getPos().x > maxX - 10.0)
					{
						e.setVel(Point(-playerHorizontalVel, 0));
					}
				}
			}
		}
	}
}
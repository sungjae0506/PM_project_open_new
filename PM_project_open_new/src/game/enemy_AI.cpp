#include "enemy_AI.h"

EnemyAI::EnemyAI()
{
}

EnemyAI::EnemyAI(string _mode)
{
	mode = _mode;
}

void EnemyAI::setMode(string _mode)
{
	mode = _mode;
}

void EnemyAI::enemyInit(Enemy& e)
{
	if (mode == "MODE1"|| mode == "MODE2")
	{
		e.setAcc(gravity);
	}
	else if (mode == "MODE3")
	{
		e.setAcc(Point(0, 0));
	}
	else if (mode == "MODE4")
	{
		e.setAcc(Point(0, 0));
		e.mapTransparent = true;
	}
}

void EnemyAI::pathfinding(Enemy& e, const vector<Player>& p, const Map &mp)
{
	int tick = e.getMainTick();

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
		/*if (false) // ¶Ù¾î´Ù´Ô
		{
			if (e.mapCollisionState[0])
			{
				e.setVel(Point(e.getVel().x, -playerHorizontalVel));
			}
			if (e.mapCollisionState[1])
			{
				e.setVel(Point(e.getVel().x, playerHorizontalVel));
			}
			if (e.mapCollisionState[2])
			{
				e.setVel(Point(playerHorizontalVel, e.getVel().y));
			}
			if (e.mapCollisionState[3])
			{
				e.setVel(Point(-playerHorizontalVel, e.getVel().y));
			}
		}*/
	}
	else if (mode == "MODE3")
	{
		if (abs(e.getVel()) < EPSILON)
		{
			if (e.getPos().x < 160.0)
			{
				e.setVel(Point(playerHorizontalVel, playerHorizontalVel));
			}
			else
			{
				e.setVel(Point(-playerHorizontalVel, playerHorizontalVel));
			}
		}
		if (e.mapCollisionState[0])
		{
			e.setVel(Point(e.getVel().x, -0.75 * playerHorizontalVel));
		}
		if (e.mapCollisionState[1])
		{
			e.setVel(Point(e.getVel().x, 0.75 * playerHorizontalVel));
		}
		if (e.mapCollisionState[2])
		{
			e.setVel(Point(0.75 * playerHorizontalVel, e.getVel().y));
		}
		if (e.mapCollisionState[3])
		{
			e.setVel(Point(-0.75 * playerHorizontalVel, e.getVel().y));
		}
	}
	else if (mode == "MODE4")
	{
		double mp = -1, mn = 1e9;
		if (tick % (int)(4.0 * idlePerSecond) == (int)(2.0 * idlePerSecond))
		{
			for (int i = 0; i < p.size(); ++i)
			{
				if (abs(e.getPos() - p[i].getPos()) < mn && p[i].getState() != "Killed")
				{
					mn = abs(e.getPos() - p[i].getPos());
					mp = i;
				}
			}
			targetVel = (p[mp].getPos() - e.getPos());
			targetVel /= abs(targetVel);
			if (abs(p[mp].getPos() - e.getPos()) > 16.0)
			{
				targetVel *= min(playerHorizontalVel, max(0.0, (abs(p[mp].getPos() - e.getPos()) - 15.0) / 2.0));
			}
			
		}
		if ((int)(2.0 * idlePerSecond) <= tick % (int)(4.0 * idlePerSecond))
		{	
			e.setVel(targetVel);
		}
		else
		{
			e.setVel(Point(0, 0));
		}
	}
}
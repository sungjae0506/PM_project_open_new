#include "map.h"

Point indexToPoint(int i, int j, int h, int w, const Range& r)
{
	return Point(r.point0.x + (j * (r.point1.x - r.point0.x) / w), r.point1.y - (i * (r.point1.y - r.point0.y)) / h);
}

Lines vectorToLines(vector<vector<bool>>& arr, const Range &r)
{
	Lines lines;
	int h = arr.size();
	int w = arr[0].size();
	int prev;

	for (int i = 0; i < h - 1; ++i)
	{
		prev = -1;
		for (int j = 0; j < w; ++j)
		{
			if (!(arr[i][j] == 0 && arr[i + 1][j] == 1)) // norm이 위쪽
			{
				if (j > prev + 1)
					lines.addLine(Line(indexToPoint(i + 1, prev + 1, h, w, r), indexToPoint(i + 1, j, h, w, r), Point(0, 1)));
				prev = j;
			}
		}
		if (w > prev + 1)
			lines.addLine(Line(indexToPoint(i + 1, prev + 1, h, w, r), indexToPoint(i + 1, w, h, w, r), Point(0, 1)));
		prev = -1;
		for (int j = 0; j < w; ++j)
		{
			if (!(arr[i][j] == 1 && arr[i + 1][j] == 0)) // norm이 아래쪽
			{
				if (j > prev + 1)
					lines.addLine(Line(indexToPoint(i + 1, prev + 1, h, w, r), indexToPoint(i + 1, j, h, w, r), Point(0, -1)));
				prev = j;
			}
		}
		if (w > prev + 1)
			lines.addLine(Line(indexToPoint(i + 1, prev + 1, h, w, r), indexToPoint(i + 1, w, h, w, r), Point(0, -1)));
	}

	for (int j = 0; j < w - 1; ++j)
	{
		prev = -1;
		for (int i = 0; i < h; ++i)
		{
			if (!(arr[i][j] == 0 && arr[i][j + 1] == 1)) // norm이 왼쪽
			{
				if (i > prev + 1)
					lines.addLine(Line(indexToPoint(prev + 1, j + 1, h, w, r), indexToPoint(i, j + 1, h, w, r), Point(-1, 0)));
				prev = i;
			}
		}
		if (h > prev + 1)
			lines.addLine(Line(indexToPoint(prev + 1, j + 1, h, w, r), indexToPoint(h, j + 1, h, w, r), Point(-1, 0)));
		prev = -1;
		for (int i = 0; i < h; ++i)
		{
			if (!(arr[i][j] == 1 && arr[i][j + 1] == 0)) // norm이 오른쪽
			{
				if (i > prev + 1)
					lines.addLine(Line(indexToPoint(prev + 1, j + 1, h, w, r), indexToPoint(i, j + 1, h, w, r), Point(1, 0)));
				prev = i;
			}
		}
		if (h > prev + 1)
			lines.addLine(Line(indexToPoint(prev + 1, j + 1, h, w, r), indexToPoint(h, j + 1, h, w, r), Point(1, 0)));
	}

	return lines;
}

Map::Map()
{
}

Map::Map(const Map& map)
{
	tileVector.resize(map.tileVector.size());
	for (int i = 0; i < map.tileVector.size(); ++i)
		tileVector[i] = map.tileVector[i];

	bubbleCurrentVector.resize(map.bubbleCurrentVector.size());
	for (int i = 0; i < map.bubbleCurrentVector.size(); ++i)
		bubbleCurrentVector[i] = map.bubbleCurrentVector[i];

	tile.resize(2);

	tile[0] = map.tile[0];
	tile[1] = map.tile[1];
	
	background.resize(1);
	background[0] = map.background[0];

	
	
	platform = map.platform;
	wall = map.wall;
}

void Map::setTile(const vector<Image>& i)
{
	tile = i;
}

void Map::setBackground(const vector<Image>& i)
{
	background = i;
}

void Map::draw()
{
	background[0].draw();

	for (size_t i = 0; i < tileVector.size(); ++i)
	{
		for (size_t j = 0; j < tileVector[0].size(); ++j)
		{
			Point p = indexToPoint(i + 1, j, tileVector.size(), tileVector[0].size(), Range(0, 0, 320, 320));
			
			if (tileVector[i][j] == 1)
			{
				if (i % 2 == 1 && (j == 0 || j == tileVector[i].size() - 2))
				{
					(tile[1] + p).draw();
				}
				if (2 <= j && j < tileVector[i].size() - 2)
				{
					(tile[0] + p).draw();
				}
			}
		}
	}
}
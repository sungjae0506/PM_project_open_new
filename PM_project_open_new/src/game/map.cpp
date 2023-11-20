#include "map.h"

Point indexToPoint(int i, int j, int h, int w, const Range& r)
{
	return Point(r.point0.x + (j * (r.point1.x - r.point0.x) / w), r.point1.y - (i * (r.point1.y - r.point0.y)) / h);
}

Lines vectorToLines(vector<vector<int>>& arr, const Range &r)
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

	tile1 = map.tile1;
	tile2 = map.tile2;
	
	platform = map.platform;
	wall = map.wall;
}

void Map::readMap(string file)
{
	fstream f(file);
	string s;
	int h, w;

	Range r(0, 0, 320, 320);
	
	//////////////////////////////////
	f >> s;
	tile1(s, Range(0, 0, 10, 10));
	f >> s;
	tile2(s, Range(0, 0, 20, 20));
	f >> s;
	background(s, Range(0, 0, 320, 320));
	//////////////////////////////////

	f >> h >> w;
	tileVector.resize(h);
	for (int i = 0; i < h; ++i)
		tileVector[i].resize(w);
	for (int i = 0; i < h; ++i)
	{
		f >> s;
		for (int j = 0; j < w; ++j)
			if (s[j] == '#')
				tileVector[i][j] = 1;
	}
	platform = vectorToLines(tileVector, r);
	wall.addLine(Line(Point(r.point0.x, r.point0.y), Point(r.point0.x, r.point1.y * 1.5), Point(1, 0)));
	wall.addLine(Line(Point(r.point1.x, r.point0.y), Point(r.point1.x, r.point1.y * 1.5), Point(-1, 0)));
}

void Map::setTexture(Image _tile1, Image _tile2)
{
	tile1 = _tile1;
	tile2 = _tile2;
}

void Map::draw()
{
	for (size_t i = 0; i < tileVector.size(); ++i)
	{
		for (size_t j = 0; j < tileVector[0].size(); ++j)
		{
			Point p = indexToPoint(i + 1, j, tileVector.size(), tileVector[0].size(), Range(0, 0, 320, 320));
			
			if (tileVector[i][j] == 1)
			{
				if (i % 2 == 1 && (j == 0 || j == tileVector[i].size() - 2))
				{
					(tile2 + p).draw();
				}
				if (2 <= j && j < tileVector[i].size() - 2)
				{
					(tile1 + p).draw();
				}
			}
		}
	}
}
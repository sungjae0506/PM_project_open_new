#include "map.h"
#include "../util/object.h"

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
			if (!(arr[i][j] == 0 && arr[i + 1][j] == 1)) // norm�� ����
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
			if (!(arr[i][j] == 1 && arr[i + 1][j] == 0)) // norm�� �Ʒ���
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
			if (!(arr[i][j] == 0 && arr[i][j + 1] == 1)) // norm�� ����
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
			if (!(arr[i][j] == 1 && arr[i][j + 1] == 0)) // norm�� ������
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

void Map::readMap(string file)
{
	fstream f(file);
	string s;
	int h, w;
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
	platform = vectorToLines(tileVector, Range(0, 0, 320, 320));
}

void Map::setTexture(Image _tile1, Image _tile2) {
	tile1 = _tile1; tile2 = _tile2;
}

void Map::draw() {
	for (size_t i = 0; i < tileVector.size(); ++i) {
		for (size_t j = 0; j < tileVector[i].size(); ++j) {

			Point p = indexToPoint(i, j, tileVector.size(), tileVector[i].size(), Range(0, 0, 320, 320));

			if (tileVector[i][j] == 1) {

				if (j == 0 || j == tileVector[i].size() - 1) {

					(tile2 + p).draw();
				}
				else {
					(tile1 + p).draw();
				}
			}
		}
	}
}
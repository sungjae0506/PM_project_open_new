#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../game/map.h"
#include "../util/object.h"
#include "../asset/image.h"
using namespace std;


Point indexToPoint(int i, int j, int h, int w, const Range& r);
Lines vectorToLines(vector<vector<int>>& arr, const Range& r);

class Map
{
public:
	vector<vector<int>> tileVector;
	Lines platform;
	Lines wall;
	Image tile1, tile2;
	Map();
	void readMap(string file);
	void setTexture(Image _tile1, Image _tile2);
	void draw();

	// �̹��� Ŭ���� ��� ����
	// �̹��� �ε�:     Image snu("image/snu.png", Range(0, 0, 320, 320)); 
	// Range(x1, y1, x2, y2)�� (x1 <= x <= x2) && (y1 <= y <= y2) ������ �ǹ�.
	// �̹��� �׸���:   snu.draw();
	// �̹��� �����̵�: snu + Point(80, 80);
	// �����̵� �� �׸���: (snu + Point(80, 80)).draw()

};
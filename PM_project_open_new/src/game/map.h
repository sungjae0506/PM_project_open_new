#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../util/object.h"
#include "../asset/image.h"

using namespace std;


Point indexToPoint(int i, int j, int h, int w, const Range& r);
Lines vectorToLines(vector<vector<bool>>& arr, const Range& r);

class Map
{
public:
	vector<vector<bool>> tileVector;
	vector<vector<char>> bubbleCurrentVector;
	
	vector<Image> tile;
	vector<Image> background;
	Lines platform;
	Lines wall;

	Map();
	Map(const Map& map);

	void setTile(const vector<Image>& i);
	void setBackground(const vector<Image>& i);
	void draw();

	// 이미지 클래스 사용 예시
	// 이미지 로딩:     Image snu("image/snu.png", Range(0, 0, 320, 320)); 
	// Range(x1, y1, x2, y2)는 (x1 <= x <= x2) && (y1 <= y <= y2) 영역을 의미.
	// 이미지 그리기:   snu.draw();
	// 이미지 평행이동: snu + Point(80, 80);
	// 평행이동 후 그리기: (snu + Point(80, 80)).draw()
};
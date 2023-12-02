#pragma once
#include <string>
#include <vector>
#include "../asset/texture_loader.h"
#include "../util/range.h"
#include "../asset/font_loader.h"

vector<double> stringToRGBf(string str);
vector<int> stringToRGBi(string str);

class Text
{
public:
	string content;
	string charColor;
	string backgroundColor;
	double fontSize;
	Range range;
	string(*textFunc)(void);
	Point cursor;

	Text();
	Text(string str, string cColor, string bColor, double sz, const Range& r);
	Text& operator() (string str, string cColor, string bColor, double sz, const Range& r);
	Text operator+(const Point& p);

	Text& addTextFunc(string(*func)(void));

	void drawChar(char c);
	void draw();

	static vector<double> getConst(void);
};

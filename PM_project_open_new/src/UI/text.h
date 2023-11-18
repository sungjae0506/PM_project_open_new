#pragma once
#include <string>
#include <vector>
#include "../asset/texture_loader.h"
#include "../util/range.h"

vector<double> stringToRGB(string str);

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

	Text& addTextFunc(string(*func)(void));

	void drawChar(char c);
	void draw();

	static vector<double> getConst(void);
};

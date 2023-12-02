#include "text.h"
const string fontWhite = "image/font_white.png";
const string fontBlack = "image/font_black.png";

const double lineSpacing = 160.0;
const double letterSpacing = 100.0;
const double aspectRatio = 1.6;

static TextureLoader textLoader;
static FontLoader fontLoader;

vector<double> stringToRGBf(string str)
{
	if (str[0] == '#')
	{
		int hex = 0;
		int red = 0, green = 0, blue = 0;
		for (int i = 1; i <= 6; ++i)
		{
			hex *= 16;
			if ('0' <= str[i] && str[i] <= '9')
				hex += str[i] - '0';
			else
				hex += str[i] - 'A' + 10;
		}
		red = hex / 65536;
		green = (hex % 65536) / 256;
		blue = hex % 256;
		return vector<double>{red / 255.0, green / 255.0, blue / 255.0};
	}
	else
		return vector<double>{0, 0, 0};
}

vector<int> stringToRGBi(string str)
{
	if (str[0] == '#')
	{
		int hex = 0;
		int red = 0, green = 0, blue = 0;
		for (int i = 1; i <= 6; ++i)
		{
			hex *= 16;
			if ('0' <= str[i] && str[i] <= '9')
				hex += str[i] - '0';
			else
				hex += str[i] - 'A' + 10;
		}
		red = hex / 65536;
		green = (hex % 65536) / 256;
		blue = hex % 256;
		return vector<int>{(int)red, (int)green, (int)blue};
	}
	else
		return vector<int>{0, 0, 0};
}

Text::Text()
{
}
Text::Text(string str, string cColor, string bColor, double sz, const Range& r)
{
	content = str;
	charColor = cColor;
	backgroundColor = bColor;
	fontSize = sz;
	range = r;
	textLoader.load(fontWhite);
	textLoader.load(fontBlack);
	fontLoader.load(fontWhite);
	textFunc = NULL;
	
}
Text& Text::operator()(string str, string cColor, string bColor, double sz, const Range& r)
{
	content = str;
	charColor = cColor;
	backgroundColor = bColor;
	fontSize = sz;
	range = r;
	textLoader.load(fontWhite);
	textLoader.load(fontBlack);
	textFunc = NULL;
	return *this;
}
Text Text::operator+(const Point& p)
{
	Text temp = *this;
	temp.range += p;
	return temp;
}
Text& Text::addTextFunc(string(*func)(void))
{
	textFunc = func;
	return *this;
}
void Text::drawChar(char c)
{
	double leftMargin = 0.017;
	double rightMargin = 0.010;

	//double upCharMargin = 0.017;
	double upCharMargin = 0.012;
	//double downCharMargin = 0.010;
	double downCharMargin = 0.02;

	double x0 = (((int)(c) % 16) / 16.0) * (1.0 - leftMargin - rightMargin) + leftMargin;
	double y0 = (7 - ((int)(c) / 16)) / 6.0;
	double x1 = x0 + ((1.0 - leftMargin - rightMargin) / 16.0);
	double y1 = y0 + (1.0 / 6.0);

	y0 += downCharMargin;
	y1 -= upCharMargin;

	/////////////////////////////////

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glTexCoord2f(x0, y0); glVertex2f(cursor.x, cursor.y);
	glTexCoord2f(x1, y0); glVertex2f(cursor.x + fontSize / aspectRatio, cursor.y);
	glTexCoord2f(x1, y1); glVertex2f(cursor.x + fontSize / aspectRatio, cursor.y + fontSize);
	glTexCoord2f(x0, y1); glVertex2f(cursor.x, cursor.y + fontSize);

	glEnd();
	glDisable(GL_TEXTURE_2D);



	/*glBegin(GL_LINE_LOOP);
	glVertex2f(cursor.x, cursor.y);
	glVertex2f(cursor.x + fontSize / aspectRatio, cursor.y);
	glVertex2f(cursor.x + fontSize / aspectRatio, cursor.y + fontSize);
	glVertex2f(cursor.x, cursor.y + fontSize);
	glEnd();*/

}
void Text::draw()
{
	if (textFunc != NULL)
		content = textFunc();

	if (backgroundColor != "")
	{
		double red, green, blue;
		vector<double> res = stringToRGBf(backgroundColor);
		red = res[0];
		green = res[1];
		blue = res[2];
		glBegin(GL_QUADS);
		glColor3f(red, green, blue);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(range.point0.x, range.point0.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(range.point1.x, range.point0.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(range.point1.x, range.point1.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(range.point0.x, range.point1.y);
		glEnd();
	}

	

	int red, green, blue, bitMask;
	vector<int> res = stringToRGBi(charColor);
	red = res[0];
	green = res[1];
	blue = res[2];
	bitMask = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	fontLoader.bind(fontWhite, 24);
	cursor = Point(range.point0.x, range.point1.y - fontSize);
	for (auto c : content)
	{
		if (32 <= c && c <= 127)
		{
			drawChar(c);
			cursor += Point(fontSize / aspectRatio * letterSpacing / 100.0, 0.0);	
		}
		if (c == 10)
		{
			cursor = Point(range.point0.x, cursor.y - (fontSize * lineSpacing / 100.0));
		}
	}

	glBlendFunc(GL_ONE, GL_ONE);

	for (int i = 0; i < 24; ++i)
	{
		if (bitMask & (1 << i))
		{
			fontLoader.bind(fontWhite, i);
			cursor = Point(range.point0.x, range.point1.y - fontSize);
			for (auto c : content)
			{
				if (32 <= c && c <= 127)
				{
					drawChar(c);
					cursor += Point(fontSize / aspectRatio * letterSpacing / 100.0, 0.0);
				}
				if (c == 10)
				{
					cursor = Point(range.point0.x, cursor.y - (fontSize * lineSpacing / 100.0));
				}
			}
		}
	}
	glDisable(GL_BLEND);
}

vector<double> Text::getConst(void)
{
	return vector<double>{lineSpacing, letterSpacing, aspectRatio};
}
#include "color4f.h"

Color4f::Color4f()
{

}

Color4f::Color4f(float _r, float _g, float _b, float _a)
{
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
	color[3] = _a;
}

void Color4f::setColor(float _r, float _g, float _b, float _a)
{
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
	color[3] = _a;
}

float Color4f::operator[](const int i) const
{
	return color[i];
}
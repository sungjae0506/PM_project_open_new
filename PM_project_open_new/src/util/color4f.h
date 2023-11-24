#pragma once

class Color4f
{
private:
	float color[4];

public:

	Color4f();
	Color4f(float _r, float _g, float _b, float _a);
	void setColor(float _r, float _g, float _b, float _a);

	float operator[](const int i) const;

};
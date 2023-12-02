#pragma once
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <string>
#include "../util/range.h"

class Image
{
public:
	string file;
	Range range;
	Image();
	Image(string file, const Range &r);
	Image& operator() (string file, const Range &r);
	Image operator+ (const Point& p);

	Image horizontalFlip(void);
	Image verticalFlip(void);

	void draw();
};
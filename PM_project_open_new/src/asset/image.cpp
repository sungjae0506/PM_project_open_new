#include "image.h"
#include "texture_loader.h"
#include <iostream>
using namespace std;

static TextureLoader imageLoader;

Image::Image() 
{
}

Image::Image(string _file, const Range &r)
{
	file = _file;
	range = r;
	imageLoader.load(file);
}

Image& Image::operator() (string _file, const Range &r)
{
	file = _file;
	range = r;
	imageLoader.load(file);
	return *this;
}

Image Image::operator+ (const Point& p)
{
	return Image(file, Range(range.point0 + p, range.point1 + p));
}

void Image::draw()
{
	imageLoader.bind(file);

	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(range.point0.x, range.point0.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(range.point1.x, range.point0.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(range.point1.x, range.point1.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(range.point0.x, range.point1.y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
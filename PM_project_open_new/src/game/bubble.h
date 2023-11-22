#pragma once
#include <vector>
#include "../asset/image.h"

class Bubble
{
public:
	vector<Image> images;
	Bubble();

	void setImages(vector<Image>& images);
	void draw(int& internalTick);

};
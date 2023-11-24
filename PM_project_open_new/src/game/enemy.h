#pragma once
#include <vector>
#include "../asset/image.h"

class Enemy
{
public:
	vector<Image> images;
	Enemy();

	void setImages(vector<Image>& images);
	//void draw(bool isBubbleTouched, int& internalTick);
	void draw(void);

};
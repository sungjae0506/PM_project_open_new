#pragma once

#include <GL/freeglut.h>
#include <FreeImage.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "texture_loader.h"

using namespace std;

class FontLoader
{
public:
	unordered_map<string, TextureData> dataTable;
	unordered_map<string, int> idxTable;
	vector<vector<GLuint>> IDTable;
	GLuint ID[25];

	FontLoader();

	FIBITMAP* createBitMap(string fileName);
	void load(string fileName);
	void bind(string fileName, int color); // RED : 0 ~ 7, GREEN : 8 ~ 15, BLUE : 16 ~ 23, BLACK : 24
};